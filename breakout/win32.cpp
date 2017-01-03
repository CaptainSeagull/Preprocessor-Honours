#include <windows.h>
#include <dsound.h>
#include <gl/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>
#include <assert.h>
#include <stdint.h>

static bool global_running = true;
static bool global_init_game = true;
static HDC global_dc = 0;

#define SCREEN_WIDTH (640)
#define SCREEN_HEIGHT (480)

static bool wini32_init_gl(HWND wnd) {
    bool res = false;

    PIXELFORMATDESCRIPTOR desired_pixel_format = {};
    desired_pixel_format.nSize = sizeof(desired_pixel_format);
    desired_pixel_format.nVersion = 1;
    desired_pixel_format.iPixelType = PFD_TYPE_RGBA;
    desired_pixel_format.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    desired_pixel_format.cColorBits = 24; // TODO(Jonny): Should this be 32... even though MSDN says EXCLUDING alpha??
    desired_pixel_format.cAlphaBits = 8;

    int suggested_pixel_format_index = ChoosePixelFormat(global_dc, &desired_pixel_format);
    PIXELFORMATDESCRIPTOR suggested_pixel_format = {};
    DescribePixelFormat(global_dc, suggested_pixel_format_index, sizeof(suggested_pixel_format), &suggested_pixel_format);
    SetPixelFormat(global_dc, suggested_pixel_format_index, &suggested_pixel_format);

    HGLRC glrc = wglCreateContext(global_dc);
    if(glrc) {
        if(wglMakeCurrent(global_dc, glrc)) { res = true; }
    }

    return(res);
}

static LRESULT CALLBACK Win32WinProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    LRESULT res = 0;
    switch(msg) {
        case WM_CLOSE: { global_running = false;                         } break;
        default:       { res = DefWindowProcA(wnd, msg, wparam, lparam); } break;
    }

    return(res);
};

static LARGE_INTEGER Win32GetWallClock(void) {
    LARGE_INTEGER res;
    QueryPerformanceCounter(&res);

    return(res);
}

static float Win32GetSecondsElapsed(LARGE_INTEGER start, LARGE_INTEGER end, int64_t perf_counter_frequency) {
    return((float)(end.QuadPart - start.QuadPart) / (float)perf_counter_frequency);
}

struct Texture {
    int unsigned id;
    int width;
    int height;
};

Texture load_texture_from_disk(char const *fname) {
    Texture res = {};

    // Create texture.
    int channels = 0;
    unsigned char *data = stbi_load(fname, &res.width, &res.height, &channels, 4);
    if(channels != 4) { fprintf(stderr, "Can only load png files with 4 channels"); }
    else {
        // Generate, and bind, texture ID.
        glGenTextures(1, &res.id);
        glBindTexture(GL_TEXTURE_2D, res.id);

        // Generate texture.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, res.width, res.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        // Set texture parameters.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Now unbind the texture.
        glBindTexture(GL_TEXTURE_2D, NULL);
    }

    return(res);
}

void delete_texture(Texture t) { glDeleteTextures(1, &t.id); }

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PreviousInstance, LPSTR CommandLine, int ShowCode) {
    LARGE_INTEGER perf_counter_frequency_res;
    QueryPerformanceFrequency(&perf_counter_frequency_res);
    int64_t perf_counter_frequency = perf_counter_frequency_res.QuadPart;

    WNDCLASS wnd_class = {};
    wnd_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wnd_class.hInstance = Instance;
    wnd_class.lpszClassName = TEXT("Frozen_Game");
    wnd_class.lpfnWndProc = &Win32WinProc;

    int monitor_refresh_hz = 60;
    int game_update_hz = monitor_refresh_hz;
    float target_seconds_per_frame = 1.0f / (float)game_update_hz;
    float target_ms = (1.0f / monitor_refresh_hz) * 1000.0f;

    timeBeginPeriod(1);

    if(!RegisterClassA(&wnd_class)) { fprintf(stderr, "Failed to register window class (somehow??)"); }
    else {
        HWND wnd = CreateWindowExA(0, wnd_class.lpszClassName, TEXT("Breakout"), (WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_POPUP),
                                   CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, 0, 0, Instance, 0);
        if(wnd == INVALID_HANDLE_VALUE) { fprintf(stderr, "Failed to create a wnd."); }
        else {
            global_dc = GetDC(wnd);
            if(!global_dc) { fprintf(stderr, "Failed to get a DC for the window."); }
            else {
                if(!wini32_init_gl(wnd)) { fprintf(stderr, "Failed to load OpenGL"); }
                else {
                    // Enable opengl stuff.
                    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    glOrtho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, -1.0f);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    glPushMatrix();
                    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Default to red.
                    glEnable(GL_TEXTURE_2D);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                    if(glGetError() != GL_NO_ERROR) { fprintf(stderr, "Error initializing OpenGL!\n"); }
                    else {
                        LARGE_INTEGER last_counter = Win32GetWallClock();
                        LARGE_INTEGER flip_wall_clock = Win32GetWallClock();

                        float ms_per_frame = 16.6666f;
                        global_running = true;
                        global_init_game = true;
                        bool SoundIsValid = false;

                        float camx = 0.0f, camy = 0.0f;

                        Texture tree = load_texture_from_disk("tree.png");
                        Texture ball = load_texture_from_disk("ball.png");

                        // Game loop start.
                        while(global_running) {
                            MSG msg;
                            while(PeekMessageA(&msg, wnd, 0, 0, PM_REMOVE)) {
                                switch(msg.message) {
                                    case WM_QUIT: { global_running = false; } break;

                                    case WM_KEYDOWN: {
                                        switch(msg.wParam) {
                                            case 'a': case VK_LEFT:  { camx += 20.0f; } break;
                                            case 'd': case VK_RIGHT: { camx -= 20.0f; } break;
                                            case 'w': case VK_UP:    { camy += 20.0f; } break;
                                            case 's': case VK_DOWN:  { camy -= 20.0f; } break;
                                        }
                                    } break;

                                    default: {
                                        TranslateMessage(&msg);
                                        DispatchMessageA(&msg);
                                    } break;
                                }
                            }

                            // TODO(Jonny): Do game stuff here.

                            glMatrixMode(GL_MODELVIEW);
                            glPopMatrix();
                            glLoadIdentity();

                            glTranslatef(camx, camy, 0.0f);
                            glPushMatrix();

                            glClear(GL_COLOR_BUFFER_BIT);
                            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

                            glMatrixMode(GL_MODELVIEW);
                            glPopMatrix();

                            // Drawing test.
#if 1
                            {
                                glScalef(0.25f, 0.25f, 1.0f);

                                float x = 50.0f, y = 50.0f;

                                glBindTexture(GL_TEXTURE_2D, ball.id);
                                glColor3f(1.0f, 1.0f, 1.0f);
                                glBegin(GL_POLYGON);
                                glTexCoord2f(0.0f, 0.0f); glVertex2f(x + 0,         y + 0);
                                glTexCoord2f(1.0f, 0.0f); glVertex2f(x + ball.width, y + 0);
                                glTexCoord2f(1.0f, 1.0f); glVertex2f(x + ball.width, y + ball.height);
                                glTexCoord2f(0.0f, 1.0f); glVertex2f(x + 0,         y + ball.height);
                                glEnd();

                                glBindTexture(GL_TEXTURE_2D, 0);

                                glScalef(2.0f, 2.0f, 1.0f);

                                x = 250.0f, y = 250.0f;
                                glBindTexture(GL_TEXTURE_2D, tree.id);
                                glColor3f(1.0f, 1.0f, 1.0f);
                                glBegin(GL_POLYGON);
                                glTexCoord2f(0.0f, 0.0f); glVertex2f(x + 0,         y + 0);
                                glTexCoord2f(1.0f, 0.0f); glVertex2f(x + tree.width, y + 0);
                                glTexCoord2f(1.0f, 1.0f); glVertex2f(x + tree.width, y + tree.height);
                                glTexCoord2f(0.0f, 1.0f); glVertex2f(x + 0,         y + tree.height);
                                glEnd();
                                glBindTexture(GL_TEXTURE_2D, 0);
                            }
#endif

                            SwapBuffers(global_dc);

                            float seconds_for_frame = Win32GetSecondsElapsed(last_counter, Win32GetWallClock(), perf_counter_frequency);
                            if(seconds_for_frame >= target_seconds_per_frame) { fprintf(stderr, "Missed frame rate"); }
                            else {
                                DWORD time_to_sleep = (DWORD)(1000.0f * (target_seconds_per_frame - seconds_for_frame));
                                if(time_to_sleep > 0) { Sleep(time_to_sleep); }

                                float test_seconds_elapsed_for_frame = Win32GetSecondsElapsed(last_counter, Win32GetWallClock(),
                                                                                              perf_counter_frequency);
                                if(test_seconds_elapsed_for_frame < target_seconds_per_frame) { fprintf(stderr, "Missed sleep"); }

                                while(seconds_for_frame < target_seconds_per_frame) {
                                    seconds_for_frame = Win32GetSecondsElapsed(last_counter, Win32GetWallClock(),
                                                                               perf_counter_frequency);
                                }
                            }

                            LARGE_INTEGER end_counter = Win32GetWallClock();
                            ms_per_frame = 1000.0f * Win32GetSecondsElapsed(last_counter, end_counter, perf_counter_frequency);
                            last_counter = end_counter;

                            flip_wall_clock = Win32GetWallClock();
                        }
                    }
                }
            }
        }
    }

    return(0);
}
