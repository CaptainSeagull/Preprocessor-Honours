// Put all your stuff in this file.

#include "win32.h"

void update_and_render(Controls controls, bool init, GameState *game_state) {
    if(init) {
        game_state->tree = load_texture_from_disk("tree.png");
        game_state->ball = load_texture_from_disk("ball.png");
    }

    draw_sprite(game_state->ball, 0,   0, 0.25f, 0.25f);
    draw_sprite(game_state->tree, 200, 200);
}