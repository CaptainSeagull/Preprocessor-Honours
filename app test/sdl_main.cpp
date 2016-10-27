#if WIN32
    #include "C:\dev\SDL2-2.0.0\include\SDL.h"
#else
    #include "SDL2/SDL.h"
#endif

int
main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Test", "Test message box", 0);

    SDL_Quit();

    return(0);
}