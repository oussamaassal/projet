/**
* @file Settings.c
*/
#include <SDL/SDL.h>
#include "image.h"
#include "Settings.h"
#include <SDL/SDL_image.h>
#include "text.h"
 

/**
* @file Settings.c
* @brief Testing Program.
* @author Unfinished Legacy
* @version 0.1
* @date Apr 22, 2022
*
* Settingss fonctions
*
*/

/**
* @brief To decrease volume .
* @param t the volume text
* @param the volume char
* @param the volume integer
* @param paper the settings background
* @param fenetre the screen
* @return Nothing
*/
void diminuer_vol(text *t,char volume[],int *vol,image *paper,SDL_Surface *fenetre)
{

    (*vol)=(int)(Mix_VolumeMusic(-1)-1.28);
    sprintf(volume,"%d",(int)((*vol)/1.28));
    t->txt=TTF_RenderText_Blended(t->fonttext,volume,t->fontcolor);
    Mix_VolumeMusic((*vol));
    SDL_BlitSurface(paper->img,&paper->pos2,fenetre,&paper->pos3);
    SDL_BlitSurface(t->txt,NULL,fenetre,&t->postext);
    SDL_UpdateRect(fenetre,1155,350,45,35);
    SDL_Delay(150);
}

/**
* @brief To increase volume .
* @param t the volume text
* @param the volume char
* @param the volume integer
* @param paper the settings background
* @param fenetre the screen
* @return Nothing
*/
void augmenter_vol(text *t,char volume[],int *vol,image *paper,SDL_Surface *fenetre)
{

    (*vol)=(int)(Mix_VolumeMusic(-1)+1.28);
    sprintf(volume,"%d",(int)((*vol)/1.28));
    t->txt=TTF_RenderText_Blended(t->fonttext,volume,t->fontcolor);
    Mix_VolumeMusic((*vol));
    SDL_BlitSurface(paper->img,&paper->pos2,fenetre,&paper->pos3);
    SDL_BlitSurface(t->txt,NULL,fenetre,&t->postext);
    SDL_UpdateRect(fenetre,1155,350,45,35);
    SDL_Delay(150);
}

/**
* @brief To open settings .
* @param fenetre the screen.
* @param x the settings state(open or closed)
* @param paper the settings background
* @param circle the circle arround the volume number
* @param plus the button to increase volume
* @param minus the button to decrease volume
* @param vol the volume text 
* @param fullscreen the text that indicates how to toggle fullscreen mode
* @return Nothing
*/
void afficher_settings(SDL_Surface* fenetre,int *x,image paper,image circle,image plus,image minus,text vol,text fullscreen)
{
    SDL_BlitSurface(paper.img,NULL,fenetre,&paper.pos1);
    SDL_BlitSurface(fullscreen.txt,NULL,fenetre,&fullscreen.postext);
    SDL_BlitSurface(vol.txt,NULL,fenetre,&vol.postext);
    SDL_BlitSurface(circle.img,NULL,fenetre,&circle.pos1);
    SDL_BlitSurface(plus.img,NULL,fenetre,&plus.pos1);
    SDL_BlitSurface(minus.img,NULL,fenetre,&minus.pos1);
    SDL_UpdateRect(fenetre,paper.pos1.x,paper.pos1.y,paper.pos1.w,paper.pos1.h);
    SDL_Delay(150);
    (*x)=1;
}

/**
* @brief To close settings .
* @param fenetre the screen.
* @param x the settings state(open or closed)
* @param paper the settings background
* @param circle the circle arround the volume number
* @param plus the button to increase volume
* @param minus the button to decrease volume
* @return Nothing
*/
void close_settings(image plus,image minus,image paper,image circle,image bg,SDL_Surface* fenetre,int *x)
{
    SDL_BlitSurface(bg.img,&paper.pos1,fenetre,&paper.pos1);
    SDL_UpdateRect(fenetre,paper.pos1.x,paper.pos1.y,paper.pos1.w,paper.pos1.h);
    liberer(plus);
    liberer(minus);
    liberer(paper);
    liberer(circle);
    SDL_Delay(150);
    (*x)=0;
}
