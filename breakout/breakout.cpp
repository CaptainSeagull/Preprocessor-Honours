#include <assert.h>
#include <string.h>
#include "pp_generated/breakout_generated.h"

#include "sdl/SDL.h"
#include "sdl/SDL_ttf.h"

int global_window_width = 640;
int global_window_height = 480;

struct V2 {
    float x;
    float y;
};

V2 v2(float x, float y) {
    V2 res = {x, y};

    return(res);
}

struct Transform {
    V2 pos;
    V2 size;
};

struct Ball {
    Transform trans;
    V2 speed;
};

struct Paddle {
    Transform trans;
};

struct GameState {
    Paddle paddle;
    Ball ball;
    int score;
};

void draw_paddle(Paddle p, SDL_Surface *surface) {
    SDL_Rect rect;
    rect.x = (int)p.trans.pos.x;
    rect.y = (int)p.trans.pos.y;
    rect.w = (int)p.trans.size.x;
    rect.h = (int)p.trans.size.y;

    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 255, 255));
}

void draw_ball(Ball b, SDL_Surface *surface) {
    SDL_Rect rect = {};
    rect.x = (int)b.trans.pos.x;
    rect.y = (int)b.trans.pos.y;
    rect.w = (int)b.trans.size.x;
    rect.h = (int)b.trans.size.y;

    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 255, 255));
}

bool paddle_clicked(int x, int y, Paddle p) {
    bool res = false;
    if((p.trans.pos.x < x) && (p.trans.pos.x + p.trans.size.x > x)) {
        if ((p.trans.pos.y < y) && (p.trans.pos.y + p.trans.size.y > y)) {
            res = true;
        }
    }

    return(res);
}

bool ball_clicked(int x, int y, Ball b) {
    bool res = false;
    if((b.trans.pos.x < x) && (b.trans.pos.x + b.trans.size.x > x)) {
        if ((b.trans.pos.y < y) && (b.trans.pos.y + b.trans.size.y > y)) {
            res = true;
        }
    }

    return(res);
}

Ball create_ball(void) {
    Ball res = {};

    res.speed = v2(0.1f, 0.1f);
    res.trans.pos = v2((float)(global_window_width / 2), (float)(global_window_height / 2));
    res.trans.size = {20, 20};

    return(res);
}

bool ball_paddle_collision(Ball b, Paddle p) {
    bool res = false;

    if(b.trans.pos.x + b.trans.size.x > p.trans.pos.x) {
        if(p.trans.pos.x + p.trans.size.x > b.trans.pos.x) {
            if(b.trans.pos.y + b.trans.size.y > p.trans.pos.y) {
                if(p.trans.pos.y + p.trans.size.y > b.trans.pos.y) {
                    res = true;
                }
            }
        }
    }

    return(res);
}

int main(int argc, char **argv) {
    if(SDL_Init(SDL_INIT_VIDEO) >= 0) {
        SDL_Window *win = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                           global_window_width, global_window_height, SDL_WINDOW_SHOWN);
        if(win) {
            SDL_Surface *surface = SDL_GetWindowSurface(win);
            if(surface) {
                GameState game_state = {};

                game_state.paddle.trans.pos.x = 200;
                game_state.paddle.trans.pos.y = 400;
                game_state.paddle.trans.size.x = 100;
                game_state.paddle.trans.size.y = 20;

                game_state.ball = create_ball();

                SDL_Rect back = { 0, 0, global_window_width, global_window_height };

                bool running = true;
                SDL_Event event = {};

                TTF_Init();
                TTF_Font *font = TTF_OpenFont("courier-new.ttf", 12);

                bool controls_right = false, controls_left = false;
                bool pause = false;
                while(running) {
                    bool clicked = false;
                    bool display_game_state = false;
                    int mouse_x = 0, mouse_y = 0;

                    while(SDL_PollEvent(&event)) {
                        switch(event.type) {
                            case SDL_QUIT: { running = false; } break;

                            case SDL_KEYDOWN: {
                                switch(event.key.keysym.sym) {
                                    case SDLK_LEFT:  { controls_right = true; } break;
                                    case SDLK_RIGHT: { controls_left  = true; } break;

                                    case SDLK_F1: { display_game_state = true; } break;
                                }
                            } break;

                            case SDL_KEYUP: {
                                switch(event.key.keysym.sym) {
                                    case SDLK_LEFT:  { controls_right = false; } break;
                                    case SDLK_RIGHT: { controls_left  = false; } break;

                                    case SDLK_SPACE: { pause = !pause; } break;
                                }
                            } break;

                            case SDL_MOUSEBUTTONDOWN: {
                                SDL_GetMouseState(&mouse_x, &mouse_y);
                                clicked = true;
                            } break;
                        }
                    }


                    //
                    // Updating
                    //

                    if(!pause) {
                        // Paddle.
                        {
                            Paddle *paddle = &game_state.paddle;

                            float movement_speed = 0.5f;
                            if(controls_right) { paddle->trans.pos.x -= movement_speed; }
                            if(controls_left)  { paddle->trans.pos.x += movement_speed; }
                        }

                        // Ball.
                        {
                            Ball *ball = &game_state.ball;

                            V2 fake_ball_pos = ball->trans.pos;
                            fake_ball_pos.x += ball->speed.x;
                            fake_ball_pos.y += ball->speed.y;

                            if((fake_ball_pos.x < 0) || (fake_ball_pos.x > global_window_width))  {
                                ball->speed.x *= -1;
                                fake_ball_pos.x = ball->trans.pos.x;
                            }
                            if((fake_ball_pos.y < 0) || (fake_ball_pos.y > global_window_height)) {
                                ball->speed.y *= -1;
                                fake_ball_pos.y = ball->trans.pos.y;
                            }

                            if(ball_paddle_collision(*ball, game_state.paddle)) {
                                if(ball->speed.y > 0) {
                                    fake_ball_pos = ball->trans.pos;
                                    ball->speed.y *= -1.0f;
                                }
                            }

                            ball->trans.pos = fake_ball_pos;
                        }
                    }

                    //
                    // Rendering
                    //
                    SDL_FillRect(surface, &back, SDL_MapRGB(surface->format, 0, 0, 0));

                    draw_paddle(game_state.paddle, surface);
                    draw_ball(game_state.ball, surface);

                    //
                    // Serialization code code.
                    //
                    {
                        // Serialization.
                        size_t buf_size = 1024 * 1024;
                        char *buf = (char *)malloc(buf_size);
                        size_t bytes_written = pp::serialize(game_state, buf, buf_size);
                        assert(bytes_written < buf_size);

                        SDL_Color text_colour;
                        text_colour.r = 255;
                        text_colour.g = 0;
                        text_colour.b = 0;
                        text_colour.a = 255;

                        SDL_Surface *text_surface = TTF_RenderText_Blended_Wrapped(font, buf, text_colour, strlen(buf));

                        SDL_Rect rect;
                        rect.x = mouse_x;
                        rect.y = mouse_y;
                        rect.w = 400;
                        rect.h = 200;
                        SDL_BlitSurface(text_surface, 0, surface, &rect);

                        free(buf);
                        SDL_FreeSurface(text_surface);
                    }


                    SDL_UpdateWindowSurface(win);
                }
            }

            SDL_DestroyWindow(win);
        }

        SDL_Quit();
    }

    return(0);
}
