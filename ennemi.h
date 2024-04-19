#ifndef ENNEMI_H_INCLUDED
#define ENNEMI_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

/**
* @struct Ennemi
* @brief struct for enemy
*/

typedef struct
{
SDL_Surface *spritesheet; /*!< enemy sprite*/
SDL_Rect posennemi;  /*!< enemy's position on the screen*/
SDL_Rect possprite; /*!< image position on the sprite sheet*/
int direction;  /*!< the enemy's direction*/
int posMin,posMax;  /*!< the interval in which the enemy moves*/

}Ennemi;

/*typedef struct
{
SDL_Surface *sprite_perso;
SDL_Rect posperso;
SDL_Rect possprite_perso;
int direction_perso;
char number[20]; 
SDL_Rect position_textee;
SDL_Rect position_number;  
int valeur_score ;
} personne ;*/

// les fonctions de l'ennemi 
void initEnnemi(Ennemi*e);
void afficherEnnemi(Ennemi e, background b);
void animerEnnemi( Ennemi *e);
void deplacer( Ennemi * e, background b);
int collisionBB( personne p, Ennemi e);




// les fonction du personnage
//void init_personnage(personne* p);
//void afficher_personnage(personne p, SDL_Surface * screen); 

#endif 
