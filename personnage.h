#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


/**
* @struct animation
* @brief struct for character(secondary)
*/
typedef struct 
{
    SDL_Surface *img;
    SDL_Rect pos_screen,pos_sprite;
    int level,timer,init_time;

}animation;

/**
* @struct perso
* @brief struct for character(secondary)
*/
typedef struct
{
    SDL_Surface *img;
    SDL_Surface *img1;
    SDL_Rect pos1,pos2,pos3;
    Mix_Chunk *effet;
    Mix_Music *music;
    int volume,mode,scroll,time,init_time,direction,collision;
    double vitesse,acceleration;
}perso;


#include "ennemi.h"

void init_perso(perso* b,int x,int y,char name[]);
void init_perso_animation(animation* animated_object,char name[],int x,int y,int w,int h);
void standing_animation(background *bg,perso* animated_mouvement,animation *mouvement,SDL_Surface* screen,int n);
void sprint_perso(perso *p);
void slow_perso(perso *p);
void auto_slow_perso(perso *p);
void move_perso(background b,perso *p,SDL_Surface* screen);
void perso_jump(background b,perso *p,SDL_Surface *screen);
void gravity(perso *p,background b,SDL_Surface *screen);
void liberer_perso(perso *p);


#endif