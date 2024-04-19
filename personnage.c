#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


#include "background.h"
#include "personnage.h"


void init_perso(perso* b,int x,int y,char name[])
{
    b->img=IMG_Load(name);
    b->pos1.x=x;
    b->pos1.y=y;
    b->pos1.w=50;
    b->pos1.h=50;
    b->collision=-1;
    b->mode=0;
    b->scroll=0;
    b->acceleration=0;
    b->vitesse=10;
}

void liberer_perso(perso *p)
{
    //SDL_FreeSurface(p->img1);
    SDL_FreeSurface(p->img);

}

void init_perso_animation(animation* animated_object,char name[],int x,int y,int w,int h)
{
    animated_object->img=IMG_Load(name);
    animated_object->pos_sprite.x=-w;
    animated_object->pos_sprite.y=y;
    animated_object->pos_sprite.w=w;
    animated_object->pos_sprite.h=h;
}

/*void standing_animation(background *bg,perso* animated_mouvement,animation *mouvement,SDL_Surface* screen,int n)
{
    int now;
        now=SDL_GetTicks();
        if(now>mouvement->timer+(150*mouvement->level))
        {
            mouvement->pos_sprite.x=(mouvement->pos_sprite.x+mouvement->pos_sprite.w)%(mouvement->pos_sprite.w*n);
            mouvement->level++;
        }
            SDL_BlitSurface(bg->img1,&animated_mouvement->pos1,bg->img,&animated_mouvement->pos1);
            SDL_BlitSurface(mouvement->img,&mouvement->pos_sprite,bg->img,&animated_mouvement->pos1);
            SDL_UpdateRect(screen,animated_mouvement->pos1.x,animated_mouvement->pos1.y,mouvement->pos_sprite.w,mouvement->pos_sprite.h);
            
        
}*/
void sprint_perso(perso *p)
{
    if(p->acceleration<0.039)
        {
            p->time=SDL_GetTicks()-p->init_time;
            p->acceleration+=0.003;
        }  
}


void slow_perso(perso *p)
{
    if(p->acceleration>0)
        {
            p->acceleration-=0.01;
        }
    if(p->acceleration<0)
    {
        p->acceleration=0;
    }
}

void auto_slow_perso(perso *p)
{
    if(p->acceleration>0)
        {
            p->acceleration-=0.001;
        }
    if(p->acceleration<0)
    {
        p->acceleration=0;
    }
}

void move_perso(background b,perso *p,SDL_Surface* screen)
{    
    SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
    p->pos1.x-=((p->direction)*(p->vitesse+(p->time*p->acceleration)));
    SDL_BlitSurface(p->img,NULL,b.img,&p->pos1);
    SDL_UpdateRect(screen,p->pos1.x,p->pos1.y,p->pos1.w,p->pos1.h);
}

void perso_jump(background b,perso *p,SDL_Surface *screen)
{
    SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
    p->pos1.y-=p->vitesse;
    SDL_BlitSurface(p->img,NULL,b.img,&p->pos1);
    SDL_UpdateRect(screen,p->pos1.x,p->pos1.y,p->pos1.w,p->pos1.h);
}
void gravity(perso *p,background b,SDL_Surface *screen)
{
    SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
    p->pos1.y+=3;
    SDL_BlitSurface(p->img,NULL,b.img,&p->pos1);
    SDL_UpdateRect(screen,p->pos1.x,p->pos1.y,p->pos1.w,p->pos1.h);
}