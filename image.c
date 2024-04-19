#include <SDL/SDL.h>
#include "image.h"
#include <SDL/SDL_image.h>

/**
* @file image.c
* @brief Testing Program.
* @author Unfinished Legacy
* @version 0.1
* @date Apr 22, 2022
*
* menu buttons fonctions
*
*/

void add_pos(image* m,int pos,int x,int y,int w,int h)
{
    if(pos==3)
    {
    m->pos3.x=x;
    m->pos3.y=y;
    m->pos3.w=w;
    m->pos3.h=h;
    }
    else
    {
    m->pos2.x=x;
    m->pos2.y=y;
    m->pos2.w=w;
    m->pos2.h=h;
    }

}

void menu_button(image* m,char name[],int x,int y,int w,int h)
{
    m->img=IMG_Load(name);
    if(m->img==NULL){return;}

    m->pos1.x=x;
    m->pos1.y=y;
    m->pos1.w=m->img->w;
    m->pos1.h=m->img->h;
    if(w!=0 && h!=0)
    {
        m->pos1.w=w;
        m->pos1.h=h;
    }
}


void initBackground(image* background,char name[])
{
    background->img=IMG_Load(name);
    if(background->img==NULL){return ;}

    background->pos1.x=0;
    background->pos1.y=0;

    background->pos2.x=180;
    background->pos2.w=500;
    background->pos2.h=160;

    background->pos3.x=180;
}

void liberer(image m)
{
    SDL_FreeSurface(m.img);
}

void afficher(image m,SDL_Surface *screen)
{
    SDL_BlitSurface(m.img,&m.pos2,screen,&m.pos1);
}
void afficher_selected(image *m,image *b,SDL_Surface *f,int *i,char selected[])
{
             
               SDL_FreeSurface(m->img);
               m->img=IMG_Load(selected);
               m->pos1.x=180;
               b->pos2.y=m->pos1.y;
               b->pos3.y=m->pos1.y;
               SDL_BlitSurface(m->img,NULL,f,&m->pos1);
               SDL_UpdateRect(f,180,b->pos2.y,500,160);
               (*i)=1;
}
void afficher_deselected(image *m,image *b,SDL_Surface *f,int *i,char deselected[])
{
               SDL_FreeSurface(m->img);
               m->img=IMG_Load(deselected);
               m->pos1.x=200;
               SDL_BlitSurface(m->img,NULL,f,&m->pos1);
               SDL_UpdateRect(f,180,b->pos2.y,500,160);
               (*i)=0;
}
