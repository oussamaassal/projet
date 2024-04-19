#ifndef IMAGE_H
#define IMAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

/**
* @struct image
* @brief struct for menu buttons
*/

typedef struct 
{
    SDL_Rect pos1; /*!< The button's position*/
    SDL_Rect pos2; /*!< The button's width and height*/
    SDL_Rect pos3; /*!< */
    SDL_Surface* img; /*!< The button's image*/

}image;


void add_pos(image* m,int pos,int x,int y,int w,int h);
void menu_button(image* m,char name[],int x,int y,int w,int h);
void initBackground(image* background,char name[]);
void liberer(image A);
void afficher_selected(image *m,image *b,SDL_Surface *f,int *i,char selected[]);
void afficher_deselected(image *m,image *b,SDL_Surface *f,int *i,char deselected[]);

#endif
