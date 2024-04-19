#include "game.h"

void game()
{
    SDL_Event e;
    
    while(1)
    {
        if(e.key.keysym.sym==SDLK_ESCAPE)
        {break;}
    }

    return 0;
}
    