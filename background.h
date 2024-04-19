#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

/**
* @struct background
* @brief struct for background
*/

typedef struct
{
    SDL_Surface *img; /*!< background principale. */
    SDL_Surface *img1; /*!< premiere couche. */
    SDL_Surface *img2; /*!< deuxieme couche. */
    SDL_Surface *mask; /*!< mask pour collision. */
    SDL_Rect pos1,pos2,pos3; /*!< les zone des surfaces de background. */
    Mix_Chunk *effet; /*!< effet sonore. */
    Mix_Music *music; /*!< musique. */
    int niveau; /*!< le niveau du jeu. */
    int volume; /*!< . */
    int  mode; /*!< . */
    int scroll; /*!< . */
    int timer; /*!< . */
    
}background;

/**
* @struct scrolling
* @brief struct for background
*/

typedef struct 
{
    int direction;
    int up;
    int down;
    int time;
    int init_time;
    int pos_init;
    double acceleration,vitesse;
    SDL_Rect camera;
}scrolling;


/*typedef struct 
{
    SDL_Surface *img;
    SDL_Rect pos;
    Mix_Chunk *effet;
}collision;*/

#include "perso.h"
#include "personnage.h"


void initBack(background* b,int x,int y,char image[],char song[],char effet[]);
void init_mask(background* b,char name[],SDL_Surface* screen);
void liberer_back(background b);
//void libere_collision(collision o);
void add_background_pos(background *b,int pos,int x,int y,int w,int h);
void afficherBack(background b,SDL_Surface *screen,scrolling scroll);
void init_animation(background* animated_object,char name[],int x,int y,int w,int h);
void continuous_animation(background* bg,background* animated_object,char name[],int y,int w,int h,SDL_Surface* screen,int n,int ms);
void object_animation(background* bg,background* animated_object,char name[],int y,int w,int h,SDL_Surface* screen,int n,int start);
/*void init_obstacle(background *b,collision *obstacle,char name[],int x,int y);
void collisionPP(perso *p,collision obstacle,scrolling *scroll,background b);
void collisionPP1(personne *pe,collision obstacle,scrolling *scroll,background b);*/
void auto_scroll(background *b,scrolling *scroll,int *dt);
void init_scroll(scrolling *scroll,double vitesse,double acceleraion);
void scrolling_perso(background b,scrolling *scroll,perso *p,Uint8 *keystates);
void scrolling_perso1(background b,scrolling *scroll,personne *p,Uint8 *keystates);
void merge(perso personnage,perso personnage1,scrolling *camera1,scrolling *camera2);
void afficher_perso2(background b,SDL_Surface *screen,scrolling scroll1);
void partage_ecran(scrolling *camera1,scrolling *camera2);
void init_pixel(personne *p,SDL_Rect* pixels);
SDL_Rect* allocate_pixels(void);
int color_fix(personne *p,background b,SDL_Rect* pixels);
int color_check(personne *p,background b,SDL_Rect* pixels,int i);
SDL_Color getpixel(background b,SDL_Rect pos);
void fall_check(personne *p,background b,SDL_Rect* pixels);




#endif
