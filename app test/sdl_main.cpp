#include "SDL2/SDL.h"

int
main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Test", "Test message box", 0);

    SDL_Quit();

    return(0);
}