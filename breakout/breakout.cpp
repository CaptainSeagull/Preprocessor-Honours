#include <assert.h>
#include <string.h>
#include "breakout_generated.h"

#include "sdl/SDL.h"

int global_window_width = 640;
int global_window_height = 480;

struct V2 {
    int x;
    int y;
};

struct V2f {
    float x;
    float y;
};

V2 v2(int x, int y) {
    V2 res = {x, y};

    return(res);
}

V2f v2f(float x, float y) {
    V2f res = {x, y};

    return(res);
}

struct Transform {
    V2 pos;
    V2 size;
};

struct Ball {
    V2f pos;
    V2f speed;
    int radius;
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
    rect.x = p.trans.pos.x;
    rect.y = p.trans.pos.y;
    rect.w = p.trans.size.x;
    rect.h = p.trans.size.y;

    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 255, 255));
}

void draw_ball(Ball b, SDL_Surface *surface) {
    SDL_Rect rect = {};
    rect.x = (int)b.pos.x;
    rect.y = (int)b.pos.y;
    rect.w = b.radius;
    rect.h = b.radius;

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
    if((b.pos.x < x) && (b.pos.x + b.radius > x)) {
        if ((b.pos.y < y) && (b.pos.y + b.radius > y)) {
            res = true;
        }
    }

    return(res);
}

Ball create_ball(void) {
    Ball res = {};

    res.radius = 40;
    res.speed = v2f(0.25f, 0.25f);
    res.pos = v2f((float)(global_window_width / 2), (float)(global_window_height / 2));

    return(res);
}

bool ball_paddle_collision(Ball b, Paddle p) {
    bool res = false;


    { return(res); }
}

int
main(int argc, char **argv) {
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

                size_t buf_size = 1024 * 1024;
                char *buf = (char *)malloc(buf_size);
                if(buf) {
                    memset(buf, 0, buf_size);

                    bool controls_right = false, controls_left = false;
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

                        // Paddle.
                        {
                            Paddle *paddle = &game_state.paddle;

                            int movement_speed = 1;
                            if(controls_right) { paddle->trans.pos.x -= movement_speed; }
                            if(controls_left)  { paddle->trans.pos.x += movement_speed; }
                        }

                        // Ball.
                        {
                            Ball *ball = &game_state.ball;

                            V2f fake_ball_pos = ball->pos;
                            fake_ball_pos.x += ball->speed.x;
                            fake_ball_pos.y += ball->speed.y;

                            if((fake_ball_pos.x < 0) || (fake_ball_pos.x > global_window_width))  {
                                ball->speed.x *= -1;
                                fake_ball_pos.x = ball->pos.x;
                            }
                            if((fake_ball_pos.y < 0) || (fake_ball_pos.y > global_window_height)) {
                                ball->speed.y *= -1;
                                fake_ball_pos.y = ball->pos.y;
                            }

                            ball->pos = fake_ball_pos;
                        }


                        //
                        // Serialize part.
                        //
                        if(display_game_state) { pp::serialize(game_state, buf, buf_size); }
                        else if(clicked) {
                            if(paddle_clicked(mouse_x, mouse_y, game_state.paddle))  { pp::serialize(game_state.paddle, buf, buf_size); }
                            else if(ball_clicked(mouse_x, mouse_y, game_state.ball)) { pp::serialize(game_state.ball, buf, buf_size);   }
                        }

                        if(*buf) {
                            printf("\n%s\n", buf);
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Serialized", buf, 0);
                            memset(buf, 0, buf_size);
                        }

                        //
                        // Rendering
                        //
                        SDL_FillRect(surface, &back, SDL_MapRGB(surface->format, 0, 0, 0));

                        draw_paddle(game_state.paddle, surface);
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
