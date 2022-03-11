#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "personnage.h"


typedef struct
{
    SDL_Surface img;
    SDL_Rect pos1,pos2,pos3;
    Mix_Chunk effet;
    Mix_Music *music;
    int niveau,volume,mode;
    
}background;

typedef struct 
{
    SDL_Surface img;
    SDL_Rect pos;
    Mix_Chunk effet;
}collision;



void initBack(background *b);
void afficherBack(background b,SDL_Surface *screen);
void animerBackground(background *e);
int collisionPP(personne p,SDL_Surface *Masque);
void scrolling(SDL_Rect *b,int direction,int pasAvancement);
void partage_ecran()





#endif
