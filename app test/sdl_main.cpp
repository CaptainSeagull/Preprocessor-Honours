#include <assert.h>
#include "SDL2/SDL.h"

#include "generated.h"


struct V2 {
    float x;
    float y;
};

struct Transform {
    V2 pos;
    V2 size;
};

struct Paddle {
    char const *name;
    Transform trans;
    int speed;
    int max_speed;
};

Paddle create_paddle(int x, bool right)
{
    Paddle res = {};

    res.trans.pos.x = x;
    res.max_speed = 4;

    res.name = (right) ? "right" : "left";

    return(res);
}

int
main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Paddle l = create_paddle(1, false);
    Paddle r = create_paddle(2, true);

    {
        size_t const size = 1024;
        char buf[size] = {};
        size_t bytes_written = serialize_struct(l, Paddle, buf, size);
        int len = strlen(buf);
        assert(bytes_written < size);
        printf("\n%s\n", buf);
        //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Left Paddle", buf, 0);
    }

    {
        size_t const size = 1024;
        char buf[size] = {};
        size_t bytes_written = serialize_struct(r, Paddle, buf, size);
        assert(bytes_written < size);
        //printf("%s", buf);
        //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Right Paddle", buf, 0);
    }

    SDL_Quit();

    return(0);
}