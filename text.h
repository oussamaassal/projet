#ifndef TEXT_H
#define TEXT_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "image.h"

/**
* @struct text
* @brief struct for text
*/

typedef struct
{
    TTF_Font *fonttext;
    SDL_Color fontcolor;
    SDL_Surface *txt;
    SDL_Rect postext,postext1;
    int police;
} text;


void afficher_text(text t,char txt[],SDL_Surface* fenetre,int x,int y,int w,int h);
void init_text(text *t,char font[],char txt[],int police,int x,int y,int r,int g,int b);
#endif
