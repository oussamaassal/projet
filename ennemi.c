#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h> 
#include <math.h>

#include "background.h"

/**
* @file ennemi.c
* @brief Testing Program.
* @author Unfinished Legacy
* @version 0.1
* @date Apr 22, 2022
*
* ennemi fonctions
*
*/
 

const int LARGEUR_SPRITE= 400;
const int HAUTEUR_SPRITE= 300;

void initEnnemi(Ennemi*e)
{

e->posMin=150;
e->posMax=1500;//identification de la ligne de déplacement horizontale



e->spritesheet = IMG_Load("ennemi/spritesheet.png"); //chargement du sprite sheet

//les posisiton de l'ennemi sur l'écran
e->posennemi.y=1070;
e->posennemi.x=1000;
e->posennemi.w=LARGEUR_SPRITE/4;
e->posennemi.h=HAUTEUR_SPRITE/2;

//le clip initial
e->possprite.x=0;
e->possprite.y=0;
e->possprite.w=LARGEUR_SPRITE/4;
e->possprite.h=HAUTEUR_SPRITE/2;

//la direction initial
e->direction=1;//initialement direction ->

}

void afficherEnnemi(Ennemi e, background b)
{
   SDL_BlitSurface( b.img2, &e.posennemi, b.img , &e.posennemi );
   SDL_BlitSurface( e.spritesheet , &e.possprite , b.img , &e.posennemi );

}
void animerEnnemi( Ennemi * e)
{
e->possprite.y=e->direction*150;//se positionner dans la ligne qui correspond à la direction

if(e->possprite.x == LARGEUR_SPRITE -100) 
   e->possprite.x=0; 
else
   e->possprite.x += 100; //passage interframes

}
void deplacer( Ennemi * e, background b)
{

if( e->posennemi.x > e->posMax)//s'il atteint la posmax il revient à gauche
 e->direction = 0;//gouche
if( e->posennemi.x < e->posMin)//s'il atteint la posmax il revient à droite
 e->direction = 1;//droite


 if( e->direction == 1)//droite
 {
   SDL_BlitSurface( b.img2 , &e->posennemi, b.img , &e->posennemi );
   e->posennemi.x+=5; //mouvement avec vitesse
   SDL_BlitSurface( e->spritesheet , &e->possprite , b.img , &e->posennemi );
 } 
 else
 {
    SDL_BlitSurface( b.img2 , &e->posennemi, b.img , &e->posennemi );
    e->posennemi.x-=5;//gauche
    SDL_BlitSurface( e->spritesheet , &e->possprite , b.img , &e->posennemi );
    
   
 }
  

}
int collisionBB( personne p, Ennemi e) 
{
if(( (p.pos1.x + p.pos1.w)< e.posennemi.x ) || (e.posennemi.x + e.possprite.w < p.pos1.x ) ||((p.pos1.y + p.pos1.h)< e.posennemi.y) || (e.posennemi.y + e.possprite.h < p.pos1.h ) )
return 0;
else
return 1;

} 

/*void init_personnage(personne* p)
{ 

p->sprite_perso = IMG_Load("ennemi/perso.png"); 

p->posperso.x=100;
p->posperso.y=400;

//le clip à afficher
p->possprite_perso.x=0;
p->possprite_perso.y=0;
p->possprite_perso.w=100;
p->possprite_perso.h=150;

p->direction_perso=0;


}*/


/*void afficher_personnage(personne p, SDL_Surface * screen)
{
SDL_BlitSurface( p.sprite_perso , &p.possprite_perso , screen , &p.posperso );

}*/





