/**
* @file background.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "background.h"

/**
* @file background.c
* @brief Testing Program.
* @author Unfinished Legacy
* @version 0.1
* @date Apr 22, 2022
*
* background fonctions
*
*/

/**
* @brief To initialize the background b .
* @param b the background
* @param coordinate x
* @param coordinate y
* @param image path
* @param song path
* @param sound effect path
* @return Nothing
*/
void initBack(background* b,int x,int y,char image[],char song[],char effet[])
{
    b->music=Mix_LoadMUS(song);

    b->effet=Mix_LoadWAV(effet);

    b->img=IMG_Load(image);
    if(b->img==NULL){return ;}

    b->img1=IMG_Load(image);
    if(b->img1==NULL){return ;}

    b->img2=IMG_Load(image);
    if(b->img==NULL){return ;}
    b->pos1.x=x;
    b->pos1.y=y;
    b->niveau=0;
    b->mode=0;
    b->scroll==0;
}

/**
* @brief To initialize the background mask b .
* @param b the background
* @param image path
* @param screen the surface where we blit the image
* @return Nothing
*/
void init_mask(background* b,char name[],SDL_Surface* screen)
{
    b->mask=IMG_Load(name);
    SDL_BlitSurface(b->mask,NULL,screen,&b->pos1);
}

void add_background_pos(background *b,int pos,int x,int y,int w,int h)
{
    if(pos==2)
    {
        b->pos2.x=x;
        b->pos2.y=y;
        b->pos2.w=w;
        b->pos2.h=h;
    }
    if(pos==3)
    {
        b->pos3.x=x;
        b->pos3.y=y;
        b->pos3.w=w;
        b->pos3.h=h;
    }
}
/**
* @brief To free the background b .
* @param b the background
* @return Nothing
*/
void liberer_back(background b)
{
    SDL_FreeSurface(b.img1);
    SDL_FreeSurface(b.img2);
    SDL_FreeSurface(b.img);
    //SDL_FreeSurface(b.mask);
    Mix_FreeChunk(b.effet);
    Mix_FreeMusic(b.music);
}


/*void libere_collision(collision o)
{
    SDL_FreeSurface(o.img);
}*/

/**
* @brief To show the background b .
* @param b the background
* @param screen the surface where we blit the image
* @param scroll the camera that follows the character
* @return Nothing
*/
void afficherBack(background b,SDL_Surface *screen,scrolling scroll)
{
    //Mix_PlayMusic(b.music,-1);
    SDL_BlitSurface(b.img,&scroll.camera,screen,&b.pos1);
    //SDL_Flip(screen);
}

void afficher_perso2(background b,SDL_Surface *screen,scrolling scroll1)
{
        SDL_BlitSurface(b.img,&scroll1.camera,screen,&b.pos3);

}

/**
* @brief To initialize the animated objetct.
* @param animated_object the image
* @param name path
* @param coordinate x
* @param coordinate y
* @param width w
* @param height h
* @return Nothing
*/
void init_animation(background* animated_object,char name[],int x,int y,int w,int h)
{
    animated_object->img=IMG_Load(name);
    animated_object->pos2.x=-w;
    animated_object->pos2.y=y;
    animated_object->pos2.w=w;
    animated_object->pos2.h=h;
}
/**
* @brief To animate an image continuously.
* @param bg background
* @param animated_object the image
* @param name path
* @param coordinate y
* @param width w
* @param height h
* @param screen
* @param n the number of images in the sprite sheet
* @param ms is how many milliseconds before moving to the next image in the sprite
* @return Nothing
*/
void continuous_animation(background* bg,background* animated_object,char name[],int y,int w,int h,SDL_Surface* screen,int n,int ms)
{
    int now;
        now=SDL_GetTicks();

        if(now>animated_object->timer+(ms*animated_object->niveau))
        {
            animated_object->pos2.x=(animated_object->pos2.x+animated_object->pos2.w)%(animated_object->pos2.w*n);
            SDL_BlitSurface(bg->img1,&animated_object->pos1,bg->img2,&animated_object->pos1);
            SDL_BlitSurface(animated_object->img,&animated_object->pos2,bg->img2,&animated_object->pos1);
            SDL_BlitSurface(bg->img2,&animated_object->pos1,bg->img,&animated_object->pos1);
            SDL_UpdateRect(screen,animated_object->pos1.x,animated_object->pos1.y,animated_object->pos2.w,animated_object->pos2.h);
            animated_object->niveau++;
        }

}

/**
* @brief To animate an image once.
* @param bg background
* @param animated_object the image
* @param name path
* @param coordinate y
* @param width w
* @param height h
* @param screen
* @param n the number of images in the sprite sheet
* @param ms is how many milliseconds before moving to the next image in the sprite
* @return Nothing
*/
void object_animation(background* bg,background* animated_object,char name[],int y,int w,int h,SDL_Surface* screen,int n,int start)
{
   
    int now;
        now=SDL_GetTicks();

        if(now>animated_object->timer+(150*animated_object->niveau) && now<animated_object->timer+(150*n))
        {           
            animated_object->pos2.x+=w;
            SDL_BlitSurface(bg->img1,&animated_object->pos1,bg->img2,&animated_object->pos1);
            SDL_BlitSurface(animated_object->img,&animated_object->pos2,bg->img2,&animated_object->pos1);
            SDL_BlitSurface(bg->img2,&animated_object->pos1,bg->img,&animated_object->pos1);
            SDL_UpdateRect(screen,animated_object->pos1.x,animated_object->pos1.y,w,h);
            animated_object->niveau++;
        }
    

    if(animated_object->niveau==n)
    {
        animated_object->mode=1;
    }

}
/**
* @brief To initialize the camera.
* @param scroll camera
* @return Nothing
*/
void init_scroll(scrolling *scroll,double vitesse,double acceleraion)
{
    scroll->acceleration=acceleraion;
    scroll->vitesse=vitesse;
    scroll->up=0;
    scroll->init_time=0;
    scroll->time=0;
    scroll->camera.x=0;
    scroll->camera.y=300;
    scroll->camera.w=1920;
    scroll->camera.h=1080;
}

/**
* @brief To scroll the camera.
* @param the background b
* @param scroll camera
* @return Nothing
*/
void scrolling_perso(background b,scrolling *scroll,perso *p,Uint8 *keystates)
{
    if(p->pos1.x>(b.pos1.x+(scroll->camera.w/2)) && p->pos1.x<(b.img->w-(scroll->camera.w/2)))
    {
        scroll->camera.x=p->pos1.x-(scroll->camera.w/2);
    }
    if(p->pos1.y>(b.pos1.y+(scroll->camera.h/2)) && p->pos1.y<(b.img->h-(scroll->camera.h/2)))
    {
        scroll->camera.y=p->pos1.y-(scroll->camera.h/2);
    }
}

/**
* @brief To scroll the camera.
* @param the background b
* @param scroll camera
* @return Nothing
*/
void scrolling_perso1(background b,scrolling *scroll,personne *p,Uint8 *keystates)
{
    if(p->pos1.x>(b.pos1.x+(scroll->camera.w/2)) && p->pos1.x<(b.img->w-(scroll->camera.w/2)))
    {
        scroll->camera.x=p->pos1.x-(scroll->camera.w/2);
    }
    if(p->pos1.y>(b.pos1.y+(scroll->camera.h/2)) && p->pos1.y<(b.img->h-(scroll->camera.h/2)))
    {
        scroll->camera.y=p->pos1.y-(scroll->camera.h/2);
    }
}
/*void init_obstacle(background *b,collision *obstacle,char name[],int x,int y)
{
    obstacle->img=IMG_Load(name);
    obstacle->pos.x=x;
    obstacle->pos.y=y;
    obstacle->pos.w=obstacle->img->w;
    obstacle->pos.w=obstacle->img->h;
    SDL_BlitSurface(obstacle->img,NULL,b->img,&obstacle->pos);
}

void collisionPP(perso *p,collision obstacle,scrolling *scroll,background b)
{
    if(p->pos1.y+p->pos1.h>obstacle.pos.y && p->pos1.y<obstacle.pos.y+obstacle.img->h)
    {
        if((p->pos1.x+p->pos1.w>obstacle.pos.x) && (p->pos1.x<obstacle.pos.x))
        {
            SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
            SDL_BlitSurface(obstacle.img,&p->pos1,b.img,&p->pos1);
            p->pos1.x=obstacle.pos.x-p->pos1.w;

        }else if((p->pos1.x<obstacle.pos.x+obstacle.img->w) && (p->pos1.x+p->pos1.w>obstacle.pos.x+obstacle.img->w))
        {
            SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
            SDL_BlitSurface(obstacle.img,&p->pos1,b.img,&p->pos1);
            p->pos1.x=obstacle.pos.x+obstacle.img->w;
        }
    }

    if(p->pos1.x+p->pos1.w>obstacle.pos.x && p->pos1.x<obstacle.pos.x+obstacle.img->w)
    {
        if(p->pos1.y+p->pos1.h>obstacle.pos.y && p->pos1.y<obstacle.pos.y)
        {
            SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
            SDL_BlitSurface(obstacle.img,&p->pos1,b.img,&p->pos1);
            p->pos1.y=obstacle.pos.y-(p->pos1.h);
        }else if(p->pos1.y<obstacle.pos.y+obstacle.img->h && p->pos1.y>obstacle.pos.y)
        {
            SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
            SDL_BlitSurface(obstacle.img,&p->pos1,b.img,&p->pos1);
            p->pos1.y=obstacle.pos.y+obstacle.img->h;
        }
    }

}

void collisionPP1(personne *p,collision obstacle,scrolling *scroll,background b)
{
    if(p->pos1.y+p->pos1.h>obstacle.pos.y && p->pos1.y<obstacle.pos.y+obstacle.img->h)
    {
        if((p->pos1.x+p->pos1.w>obstacle.pos.x) && (p->pos1.x<obstacle.pos.x))
        {
            SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
            SDL_BlitSurface(obstacle.img,&p->pos1,b.img,&p->pos1);
            p->pos1.x=obstacle.pos.x-p->pos1.w;

        }else if((p->pos1.x<obstacle.pos.x+obstacle.img->w) && (p->pos1.x+p->pos1.w>obstacle.pos.x+obstacle.img->w))
        {
            SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
            SDL_BlitSurface(obstacle.img,&p->pos1,b.img,&p->pos1);
            p->pos1.x=obstacle.pos.x+obstacle.img->w;
        }
    }

    if(p->pos1.x+p->pos1.w>obstacle.pos.x && p->pos1.x<obstacle.pos.x+obstacle.img->w)
    {
        if(p->pos1.y+p->pos1.h>obstacle.pos.y && p->pos1.y<obstacle.pos.y)
        {
            SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
            SDL_BlitSurface(obstacle.img,&p->pos1,b.img,&p->pos1);
            p->pos1.y=obstacle.pos.y-(p->pos1.h);
        }else if(p->pos1.y<obstacle.pos.y+obstacle.img->h && p->pos1.y>obstacle.pos.y)
        {
            SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
            SDL_BlitSurface(obstacle.img,&p->pos1,b.img,&p->pos1);
            p->pos1.y=obstacle.pos.y+obstacle.img->h;
        }
    }

}*/
/**
* @brief To dynamically allocate detection points.
* @return Array of detection points.
*/
SDL_Rect* allocate_pixels(void)
{
    SDL_Rect *pixels;
    
    pixels=(SDL_Rect*)malloc(11*sizeof(SDL_Rect));

    return(pixels);
}
/**
* @brief To initialize the detection points.
* @param p the character
* @param pixels the array of detection points
* @return Nothing
*/
void init_pixel(personne *p,SDL_Rect* pixels)
{
    pixels[0].x=p->pos1.x+(p->pos1.w/2);
    pixels[0].y=p->pos1.y;

    pixels[1].x=p->pos1.x+p->pos1.w;
    pixels[1].y=p->pos1.y+(p->pos1.h/2);

    pixels[2].x=p->pos1.x+(p->pos1.w/2);
    pixels[2].y=p->pos1.y+p->pos1.h;

    pixels[3].x=p->pos1.x;
    pixels[3].y=p->pos1.y+(p->pos1.h/2);

    pixels[4]=p->pos1;

    pixels[5].x=p->pos1.x+p->pos1.w;
    pixels[5].y=p->pos1.y;

    pixels[6].x=p->pos1.x+p->pos1.w;
    pixels[6].y=p->pos1.y+p->pos1.h;

    pixels[7].x=p->pos1.x;
    pixels[7].y=p->pos1.y+p->pos1.h;

    pixels[8].x=p->pos1.x+p->pos1.w;
    pixels[8].y=p->pos1.y+p->pos1.h+10;

    pixels[9].x=p->pos1.x;
    pixels[9].y=p->pos1.y+p->pos1.h+10;


}
/**
* @brief To detect collision.
* @param p the character
* @param b the background
* @param pixels the detection points
* @return Nothing
*/
/*void collision_color(personne *p,background b,SDL_Rect* pixels)
{
    int i=color_check(p,b,pixels);
    if()
}*/

/**
* @brief To return the point of detection.
* @param p the character
* @param b the background
* @param pixels the detection points
* @return the point of detection.
*/
int color_fix(personne *p,background bg,SDL_Rect* pixels)
{
    int i=0,black;
    SDL_Rect pixel;
    SDL_Color col;
    Uint8 r=0,g=0,b=0;
    for(i=0;i<8;i++)
    {
        p->collision=color_check(p,bg,pixels,i);
        while(p->collision!=-1)
        {
            p->collision=color_check(p,bg,pixels,i);
            //printf("[%d]-(%d)--",i,p->collision);
            if(p->collision==0)
            {
                p->saut_x=-p->saut_x;
                p->pos1.y=p->pos1.y+5;
            }else if(p->collision==1)
            {
                p->pos1.x=p->pos1.x-5;
            }else if(p->collision==2)
            {
                p->fall=0;
                p->right=0;
                p->left=0;
                p->gravite_x=0;
                p->up=0;
                p->saut_x=-20;
                p->pos1.y=p->pos1.y-5;
            }else if(p->collision==3)
            {
                p->pos1.x=p->pos1.x+5;
            }else if(p->collision==4)
            {
                p->pos1.y=p->pos1.y+1;
                p->pos1.x=p->pos1.x+1;
            }else if(p->collision==5)
            {
                p->pos1.y=p->pos1.y+1;
                p->pos1.x=p->pos1.x-1;
            }if(p->collision==6)
            {
                p->pos1.y=p->pos1.y-1;
                p->pos1.x=p->pos1.x-1;
            }else if(p->collision==7)
            {
                p->pos1.y=p->pos1.y-1;
                p->pos1.x=p->pos1.x+1;
            }


        }
    }
    
}
/**
* @brief To check if a point is not black
* @param p the character
* @param b the background
* @param pixels the detection points
* @return nothing
*/
void fall_check(personne *p,background b,SDL_Rect* pixels)
{
    int fall,i;
    for(i=8;i<10;i++)
    {
        fall=color_check(p,b,pixels,i);
        if(fall==-1)
        {
            if(i==8)
            {
                p->right=1;
            }else
            {
                p->left=1;
            }
            
        }
    }
    
}
/**
* @brief To check if a point is not black
* @param p the character
* @param b the background
* @param pixels the detection points
* @param i the detection point's number in the array
* @return nothing
*/
int color_check(personne *p,background b,SDL_Rect* pixels,int i)
{
    int c;
    SDL_Rect pixel;
    SDL_Color col;


        init_pixel(p,pixels);
        pixel=pixels[i];
        col=getpixel(b,pixel);
        if(col.r==0 && col.g==0 && col.b==0)
        {
            return i;
        }else
        {
            return -1;
        }
    
}

/**
* @brief To detect color.
* @param b the background.
* @param pos the detection point.
* @return the color detected.
*/
SDL_Color getpixel(background b,SDL_Rect pos)
{
    SDL_Color color;
    Uint32 col=0;

    char* pPosition=(char*)b.mask->pixels;
    pPosition+=(b.mask->pitch*pos.y);
    pPosition+=(b.mask->format->BytesPerPixel*pos.x);
    memcpy(&col,pPosition,b.mask->format->BytesPerPixel);
    //printf("(x=%d / x=%d)--",pos.x,pos.y);
    SDL_GetRGB(col,b.mask->format,&color.r,&color.g,&color.b);
    return(color);
}

/**
* @brief To split the screen in half.
* @param camera1 the first character's screen.
* @param camera2 the first character's screen.
* @return nothing
*/
 void partage_ecran(scrolling *camera1,scrolling *camera2)
 {
     camera1->camera.w=camera1->camera.w/2;
     camera2->camera.w=camera1->camera.w;
     camera2->camera.y=camera1->camera.y;
     camera2->camera.h=camera1->camera.h;
 }

 void merge(perso personnage,perso personnage1,scrolling *camera1,scrolling *camera2)
 {
     if(personnage1.pos1.x-personnage.pos1.x<=1920 && personnage1.pos1.x-personnage.pos1.x>=-1920)
     {
         camera1->camera.w=camera1->camera.w*2;
     }else
     {
         partage_ecran(camera1,camera2);
     }
 }
