#if !defined(_WIN32_H)

struct Controls {
    bool left;
    bool prev_left;

    bool right;
    bool prev_right;

    bool up;
    bool prev_up;

    bool down;
    bool prev_down;
};

struct GameState;
void update_and_render(Controls controls, bool init, GameState *game_state);

struct Texture {
    int unsigned id;
    int width;
    int height;
};
Texture load_texture_from_disk(char const *fname);
void delete_texture(Texture t);

void draw_sprite(Texture tex, float x, float y, float xscale = 1.0f, float yscale = 1.0f);

// Put your stuff here!
struct GameState {
    Texture tree;
    Texture ball;
};

#define _WIN32_H
#endif