#include "platform.h"

static void init_game(GameState *gs) {
    gs->tex_paddle = load_texture_from_disk("paddle.png");
    gs->tex_ball   = load_texture_from_disk("ball.png");
    gs->tex_block  = load_texture_from_disk("block.png");

    gs->ball_pos = v2(100.0f, 200.0f);
    gs->paddle_pos = v2(100.0f, 400.0f);

    gs->ball_speed = v2(4.0f, 4.0f);

    for(int i = 0, y = 0; (y < 3); ++y) {
        for(int x = 0; (x < 5); ++x) {
            Block *b = gs->block + i++;

            b->pos = v2((float)(x * gs->tex_block.width + (20 * x)), (float)(y * gs->tex_block.height + (y * 20)));
            b->is_enabled = true;
        }
    }
}

static bool collision(V2 posa, int a_width, int a_height, V2 posb, int b_width, int b_height) {
    bool res = false;
    if(posa.x > posb.x - a_width) {
        if(posb.x > posa.x - b_width) {
            if(posa.y > posb.y - a_height) {
                if(posb.y > posa.y - b_height) {
                    res = true;
                }
            }
        }
    }

    return(res);
}

static void update(GameState *gs, Controls controls) {
    V2 fp = v2_add(gs->ball_pos, gs->ball_speed);

    // Update ball.
    {
        // Ball and block.
        for(int i = 0; (i < array_count(gs->block)); ++i) {
            Block *b = gs->block + i;
            if(b->is_enabled) {
                if(collision(fp, gs->tex_ball.width, gs->tex_ball.height, b->pos, gs->tex_block.width, gs->tex_block.height)) {
                    b->is_enabled = false;
                    gs->ball_speed.y *= -1;
                    fp = gs->ball_pos;
                }
            }
        }

        // Ball and paddle.
        if(collision(fp, gs->tex_ball.width, gs->tex_ball.height, gs->paddle_pos, gs->tex_paddle.width, gs->tex_paddle.height)) {
            if(gs->ball_speed.y > 0) {
                gs->ball_speed.y *= -1;
                fp = gs->ball_pos;
            }
        }

        // Ball and side.
        if((fp.x < 0) || (fp.x > 640 - gs->tex_ball.width))  { fp = gs->ball_pos; gs->ball_speed.x *= -1; }
        if((fp.y < 0) || (fp.y > 480 - gs->tex_ball.height)) { fp = gs->ball_pos; gs->ball_speed.y *= -1; }

        gs->ball_pos = fp;
    }

    // Update paddle.
    {
        float mov_speed = 20.0f;
        V2 fake_paddle_pos = gs->paddle_pos;

        if(controls.left)  { fake_paddle_pos.x -= mov_speed; }
        if(controls.right) { fake_paddle_pos.x += mov_speed; }

        if((fake_paddle_pos.x < 0) || (fake_paddle_pos.x > 640 - gs->tex_ball.width)) { fake_paddle_pos = gs->paddle_pos; }

        gs->paddle_pos = fake_paddle_pos;
    }
}

static void render(GameState *gs) {
    draw_sprite(gs->tex_ball, gs->ball_pos.x, gs->ball_pos.y);
    draw_sprite(gs->tex_paddle, gs->paddle_pos.x, gs->paddle_pos.y);

    for(int i = 0; (i < array_count(gs->block)); ++i) {
        Block *b = gs->block + i;

        if(b->is_enabled) { draw_sprite(gs->tex_block, b->pos.x, b->pos.y); }
    }
}

void update_and_render(Controls controls, bool init, GameState *gs) {
    if(init) { init_game(gs); }

    update(gs, controls);
    render(gs);
}