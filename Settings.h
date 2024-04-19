#ifndef SETTINGS_H
#define SETTINGS_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "text.h"
#include "image.h"


void open_settings(image m,SDL_Surface *fenetre);
void diminuer_vol(text *t,char volume[],int *vol,image *paper,SDL_Surface *fenetre);
void augmenter_vol(text *t,char volume[],int *vol,image *paper,SDL_Surface *fenetre);
void afficher_settings(SDL_Surface* fenetre,int* x,image paper,image circle,image plus,image minus,text vol,text fullscreen);
void close_settings(image plus,image minus,image paper,image circle,image bg,SDL_Surface* fenetre,int *x);
#endif

