#if !defined(_WIN32_H)

struct Controls {
    bool left;
    bool right;
    bool up;
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

struct V2 {float x; float y; };

static V2 v2(float x, float y) { V2 res = {x, y}; return(res); }
static V2 v2_add(V2 a, V2 b) {V2 res = {a.x + b.x, a.y + b.y}; return(res); }
static V2 v2_div(V2 a, V2 b) {V2 res = {a.x / b.x, a.y / b.y}; return(res); } // TODO(Jonny): This is stupid...

struct Block {
    V2 pos;
    bool is_enabled;
};

#define array_count(arr) (sizeof(arr) / sizeof((arr)[0]))

// Put your stuff here!
struct GameState {
    Texture tex_paddle;
    Texture tex_ball;
    Texture tex_block;

    V2 ball_pos;
    V2 ball_speed;
    V2 paddle_pos;

    Block block[32];
};

#define _WIN32_H
#endif