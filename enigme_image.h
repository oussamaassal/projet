#ifndef ENIGME_IMAGE_H
#define ENIGME_IMAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

/**
* @struct enigme
* @brief struct for background enigme
*/

typedef struct 
{
    SDL_Surface* img; /*!< background principale */
    SDL_Surface* img1; /*!< */
    SDL_Rect pos_img; /*!< zone d'affichage */
    
}enigme;

/**
* @struct monkey
* @brief struct for monkey
*/

typedef struct 
{
    Mix_Chunk *sound; /*!< Sound effect */
    SDL_Surface* img; /*!< Monkey image */
    SDL_Rect pos_img; /*!< Monkey's position on the screen */
    SDL_Rect pos_sprite; /*!< Monkey's position on the sprite */
    int timer;  /*!< Enigme starting time */
    int niveau;  /*!< Image position on the sprite sheet */
    int enig_start;  /*!<  */
    int enig_lvl;  /*!<  */
    int monkey_number;  /*!< The number of which monkey that comes out */
    int status;  /*!< Checks whether the monkey is going up or down or inside the barrel */
    int random; /*!< random number that chooses the monkey that comes out */
}monkey;



void init_enigme(enigme *e, monkey *m);
void afficher_enigme(enigme e,SDL_Surface* screen);
void monkey_animation(enigme e,monkey* m,SDL_Surface* screen);
void monkey_pop(enigme e,monkey* m,SDL_Surface* screen);
void read_monkey(monkey *m);
void liberer_enigme(enigme e,monkey m);





#endif
