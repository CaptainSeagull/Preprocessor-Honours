#include <assert.h>
#include <string.h>
#include "generated.h"

#if WIN32
    #include "C:\dev\SDL2-2.0.0\include\SDL.h"

    #pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#else
    #include "SDL2/SDL.h"
#endif

int window_width = 640;
int window_height = 480;

struct Object {
    int i = 0;
};

struct V2 : public Object {
    int x;
    int y;
};

struct Transform {
    V2 pos;
    V2 size;
};

struct Ball {
    char const *name;
    V2 pos;
    int radius;
    int speed;
    int direction;
};

struct Paddle {
    char const *name;
    Transform trans;
    int score;
};

struct GameState {
    Paddle right;
    Paddle left;
    Ball ball;
};

SDL_Rect create_rect(int x, int y, int w, int h)
{
    SDL_Rect res;
    res.x = x;
    res.y = y;
    res.w = w;
    res.h = h;

    return(res);
}

void draw_paddle(Paddle p, SDL_Surface *surface)
{
    SDL_Rect rect = {};
    rect.x = p.trans.pos.x;
    rect.y = p.trans.pos.y;
    rect.w = p.trans.size.x;
    rect.h = p.trans.size.y;

    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 255, 255));
}

void draw_ball(Ball b, SDL_Surface *surface)
{
    SDL_Rect rect = {};
    rect.x = b.pos.x;
    rect.y = b.pos.y;
    rect.w = b.radius;
    rect.h = b.radius;

    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 255, 255));
}

bool paddle_clicked(int x, int y, Paddle p)
{
    bool res = false;
    if((p.trans.pos.x < x) && (p.trans.pos.x + p.trans.size.x > x)) {
        if ((p.trans.pos.y < y) && (p.trans.pos.y + p.trans.size.y > y)) {
            res = true;
        }
    }

    return(res);
}

bool ball_clicked(int x, int y, Ball b)
{
    bool res = false;
    if((b.pos.x < x) && (b.pos.x + b.radius > x)) {
        if ((b.pos.y < y) && (b.pos.y + b.radius > y)) {
            res = true;
        }
    }

    return(res);
}

Ball create_ball(void)
{
    Ball res = {};

    res.name = "Ball";
    res.radius = 40;
    res.speed = 0;
    res.direction = 0;
    res.pos.x = window_width / 2;
    res.pos.y = window_height / 2;

    return(res);
}

int
main(int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) >= 0) {
        SDL_Window *win = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                           window_width, window_height, SDL_WINDOW_SHOWN);
        if(win) {
            SDL_Surface *surface = SDL_GetWindowSurface(win);
            if(surface) {
                GameState game_state = {};

                game_state.right.name = "Right";
                game_state.right.trans.pos.x = 600;
                game_state.right.trans.pos.y = 20;
                game_state.right.trans.size.x = 20;
                game_state.right.trans.size.y = 100;

                game_state.left.name = "Left";
                game_state.left.trans.pos.x = 20;
                game_state.left.trans.pos.y = 20;
                game_state.left.trans.size.x = 20;
                game_state.left.trans.size.y = 100;

                game_state.ball = create_ball();

                SDL_Rect back = create_rect(0, 0, window_width, window_height);

                bool running = true;
                SDL_Event event = {};

                int movement_speed = 10;

                size_t buf_size = 1024 * 1024;
                char *buf = (char *)malloc(buf_size);
                if(buf) {
                    while(running) {
                        memset(buf, 0, buf_size);

                        bool right_up = false, right_down = false;
                        bool left_up = false, left_down = false;
                        bool clicked = false;
                        bool display_game_state = false;
                        int mouse_x = 0, mouse_y = 0;

                        while(SDL_PollEvent(&event)) {
                            switch(event.type) {
                                case SDL_QUIT: { running = false; } break;

                                case SDL_KEYDOWN: {
                                    switch(event.key.keysym.sym) {
                                        case SDLK_UP:   { right_up = true;   } break;
                                        case SDLK_DOWN: { right_down = true; } break;

                                        case 'w': case 'W': { left_up = true;   } break;
                                        case 's': case 'S': { left_down = true; } break;

                                        case SDLK_F1: { display_game_state = true; } break;
                                    }
                                } break;

                                case SDL_MOUSEBUTTONDOWN: {
                                    SDL_GetMouseState(&mouse_x, &mouse_y);
                                    clicked = true;
                                } break;
                            }
                        }

                        if(display_game_state) {
                            serialize_struct(game_state, GameState, buf, buf_size);
                        } else if(clicked) {
                            if(paddle_clicked(mouse_x, mouse_y, game_state.right)) {
                                serialize_struct(game_state.right, Paddle, buf, buf_size);
                            } else if(paddle_clicked(mouse_x, mouse_y, game_state.left)) {
                                serialize_struct(game_state.left, Paddle, buf, buf_size);
                            } else if(ball_clicked(mouse_x, mouse_y, game_state.ball)) {
                                serialize_struct(game_state.ball, Ball, buf, buf_size);
                            }
                        }

                        if(*buf) {
                            printf("\n%s\n", buf);
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Serialized", buf, 0);
                        }

                        if(right_up) {
                            game_state.right.trans.pos.y -= movement_speed;
                        }
                        if(right_down) {
                            game_state.right.trans.pos.y += movement_speed;
                        }
                        if(left_up) {
                            game_state.left.trans.pos.y -= movement_speed;
                        }
                        if(left_down) {
                            game_state.left.trans.pos.y += movement_speed;
                        }

                        SDL_FillRect(surface, &back, SDL_MapRGB(surface->format, 0, 0, 0));

                        draw_paddle(game_state.right, surface);
                        draw_paddle(game_state.left, surface);

                        draw_ball(game_state.ball, surface);

                        SDL_UpdateWindowSurface(win);
                    }

                    free(buf);
                }

                SDL_DestroyWindow(win);
            }
        }

        SDL_Quit();
    }

    return(0);
}
