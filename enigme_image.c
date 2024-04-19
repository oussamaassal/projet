/**
* @file enigme_image.c
*/
#include "enigme_image.h"

/**
* @file enigme_image.c
* @brief Testing Program.
* @author Unfinished Legacy
* @version 0.1
* @date Apr 22, 2022
*
* enigme_image fonctions
*
*/

/**
* @brief To initialize the enigma through a file .
* @param e the enigma's background.
* @param m the monkey.
* @return Nothing
*/
void init_enigme(enigme *e, monkey *m)
{
    FILE* f=NULL;
    char barrels[30]={0};
    char monkeys[30]={0};
    char sound[30]={0};
    f=fopen("enigme_image/enigme_image.txt","r");
    while(fscanf(f,"%s %s %s",barrels,monkeys,sound)!=EOF)
    {
        e->img=IMG_Load(barrels);
        e->img1=IMG_Load(barrels);
        m->img=IMG_Load(monkeys);
        m->sound=Mix_LoadWAV(sound);
    }
    e->pos_img.x=0;
    e->pos_img.y=0;

    m->pos_img.x=0;
    m->pos_img.y=0;
    m->pos_img.w=373;
    m->pos_img.h=285;
    m->pos_sprite.x=-373;
    m->pos_sprite.y=0;
    m->pos_sprite.w=373;
    m->pos_sprite.h=285;
    m->status=0;
    m->niveau=1;
    m->enig_lvl=0;
    m->monkey_number=0;
    fclose(f);
}

/**
* @brief To show the background .
* @param e the enigma's background.
* @param screen
* @return Nothing
*/
void afficher_enigme(enigme e,SDL_Surface* screen)
{
    SDL_BlitSurface(e.img,NULL,screen,&e.pos_img);
    SDL_Flip(screen);
}

/**
* @brief To launch the enigma.
* @param e the enigma's background.
* @param m the monkey.
* @param screen
* @return Nothing
*/
void monkey_pop(enigme e,monkey* m,SDL_Surface* screen)
{
    int now=SDL_GetTicks();
    
    if(now>m->enig_start)
    {
        
        //printf("(enig_start=%d)--",m->enig_start);
        if(m->status==0)
        {
            
            m->status=1;
        }
        if((m->status==1 || m->status==-1))
            {
                if(m->monkey_number==1)                  
                    monkey_animation(e,m,screen);

                if(m->monkey_number==2)       
                    monkey_animation(e,m,screen);
                
                if(m->monkey_number==3)    
                    monkey_animation(e,m,screen);
                
                if(m->monkey_number==4)      
                    monkey_animation(e,m,screen);

                if(m->monkey_number==5)       
                    monkey_animation(e,m,screen);
            }
    }
    
}
/**
* @brief To read the coordinates of the monkey through a file depending on the random number generated.
* @param m the monkey.
* @return Nothing
*/
void read_monkey(monkey *m)
{

    FILE* f;
    int i,x,y;
    f=fopen("enigme_image/enigme_n.txt","r");
    while(fscanf(f, "%d %d %d\n",&i,&x,&y)!=EOF)
    {
        
        if(i==m->monkey_number)
        {
            m->pos_img.x=x;
            m->pos_img.y=y;
        }
        
    }
    fclose(f);
                    
}
/**
* @brief To animated the monkey's jump .
* @param e the enigma's background.
* @param m the monkey.
* @param the screen
* @return Nothing
*/
void monkey_animation(enigme e,monkey* m,SDL_Surface* screen)
{
    int now=SDL_GetTicks();

                if(now>m->timer+(50*m->niveau))
                {
                    m->pos_sprite.x=(m->pos_sprite.x+(m->status*m->pos_sprite.w))%(m->pos_sprite.w*6);
                    m->niveau++;

                    //printf("(niveau=%d x=%d y=%d)",m->niveau*m->status,m->pos_img.x,m->pos_img.y);
                    read_monkey(m);
                    SDL_BlitSurface(e.img1,&m->pos_img,screen,&m->pos_img);
                    SDL_BlitSurface(m->img,&m->pos_sprite,screen,&m->pos_img);    
                    SDL_UpdateRect(screen,m->pos_img.x,m->pos_img.y,m->pos_sprite.w,m->pos_sprite.h);

                    if(m->niveau%6==0 && m->status==1)
                    {
                        m->status=(-1)*m->status;
                    }
                    else if(m->niveau%6==0 && m->status==-1)
                        {
                            SDL_BlitSurface(e.img1,&m->pos_img,screen,&m->pos_img);
                            SDL_Flip(screen);
                            m->status=0;
                            m->enig_lvl=0;
                        } 
                }    
}
/**
* @brief To free the enigma.
* @param e the enigma's background.
* @param m the monkey.
* @return Nothing
*/
void liberer_enigme(enigme e,monkey m)
{
    Mix_FreeChunk(m.sound);
    SDL_FreeSurface(e.img1);
    SDL_FreeSurface(e.img);
    SDL_FreeSurface(m.img);
}
