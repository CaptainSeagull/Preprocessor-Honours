#include <assert.h>
#include <string.h>
#include "generated.h"

#if WIN32
    #include "C:\dev\SDL2-2.0.0\include\SDL.h"

    #if _DEBUG
        #pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
    #endif
#else
    #include "SDL2/SDL.h"
#endif

struct V2 {
    int x;
    int y;
};

struct Transform {
    V2 pos;
    V2 size;
};

struct Paddle {
    char *name;
    Transform trans;
};

static SDL_Rect
create_rect(int x, int y, int w, int h)
{
    SDL_Rect res;
    res.x = x;
    res.y = y;
    res.w = w;
    res.h = h;

    return(res);
}

static void
draw_paddle(Paddle p, SDL_Surface *surface)
{
    SDL_Rect rect = {};
    rect.x = p.trans.pos.x;
    rect.y = p.trans.pos.y;
    rect.w = p.trans.size.x;
    rect.h = p.trans.size.y;
    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 255, 255));
}

static bool
paddle_clicked(int x, int y, Paddle p)
{
    bool res = false;
    //if((x + p.trans.size.x > p.trans.pos.x) && (p.trans.pos.x < x) && (y + p.trans.size.y > p.trans.pos.y) && (p.trans.pos.y < y)) {
    if(((p.trans.pos.x < x) && (p.trans.pos.x + p.trans.size.x > x)) && ((p.trans.pos.y < y) && (p.trans.pos.y + p.trans.size.y > y))) {
        res = true;
    }

    return(res);
}

int
main(int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) >= 0) {
        SDL_Window *win = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        if(win) {
            SDL_Surface *surface = SDL_GetWindowSurface(win);
            if(surface) {
                Paddle r = {};
                r.name = "Right";
                r.trans.pos.x = 600;
                r.trans.pos.y = 20;
                r.trans.size.x = 20;
                r.trans.size.y = 100;

                Paddle l = {};
                l.name = "Left";
                l.trans.pos.x = 20;
                l.trans.pos.y = 20;
                l.trans.size.x = 20;
                l.trans.size.y = 100;


                SDL_Rect back = create_rect(0, 0, 640, 480);

                bool running = true;
                SDL_Event e = {};

                int movement_speed = 10;

                while(running) {
                    bool right_up = false, right_down = false;
                    bool left_up = false, left_down = false;
                    bool clicked = false;
                    int mouse_x = 0, mouse_y = 0;

                    while(SDL_PollEvent(&e)) {
                        switch(e.type) {
                            case SDL_QUIT: { running = false; } break;

                            case SDL_KEYDOWN: {
                                switch(e.key.keysym.sym) {
                                    case SDLK_UP:       { right_up = true;   } break;
                                    case SDLK_DOWN:     { right_down = true; } break;
                                    case 'w': case 'W': { left_up = true;    } break;
                                    case 's': case 'S': { left_down = true;  } break;
                                }
                            } break;

                            case SDL_MOUSEBUTTONDOWN: {
                                SDL_GetMouseState(&mouse_x, &mouse_y);
                                clicked = true;
                            } break;
                        }
                    }

                    if(clicked) {
                        if(paddle_clicked(mouse_x, mouse_y, r)) {
                            size_t const size = 1024;
                            char buf[size] = {};
                            size_t bytes_written = serialize_struct(r, Paddle, buf, size);
                            assert(bytes_written < size);

                            printf("\n%s\n", buf);
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Right Paddle", buf, 0);
                        }

                        if(paddle_clicked(mouse_x, mouse_y, l)) {
                            size_t const size = 1024;
                            char buf[size] = {};
                            size_t bytes_written = serialize_struct(l, Paddle, buf, size);
                            assert(bytes_written < size);

                            printf("\n%s\n", buf);
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Left Paddle", buf, 0);
                        }
                    }

                    if(right_up) {
                        r.trans.pos.y -= movement_speed;
                    }
                    if(right_down) {
                        r.trans.pos.y += movement_speed;
                    }
                    if(left_up) {
                        l.trans.pos.y -= movement_speed;
                    }
                    if(left_down) {
                        l.trans.pos.y += movement_speed;
                    }

                    SDL_FillRect(surface, &back, SDL_MapRGB(surface->format, 0, 0, 0));

                    draw_paddle(r, surface);
                    draw_paddle(l, surface);
                    SDL_UpdateWindowSurface(win);
                }

                SDL_DestroyWindow(win);
            }
        }

        SDL_Quit();
    }


    return(0);
}