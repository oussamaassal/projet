#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "background.h"
#include "enigme_image.h"
#include "image.h"
#include "text.h"
#include "Settings.h"


/**
* @file test.c
* @brief Testing Program.
* @author Unfinished Legacy
* @version 0.1
* @date Apr 22, 2022
*
* fonction main
*
*/


int main(int argc, char *argv[])
{
   int x=0,Q=0,C=0,S=0,P=0,h=0,v=128,p=0,partage=0,start;
   
   scrolling scroll,scroll1;

   char coortext[10],volume[4],num;

   SDL_Event event,open_settings,move_bg;

   SDL_Surface* fenetre=NULL;

   image bg,play,quit,settings,credits,paper,plus,minus,circle,game;

   text t,vol,fullscreen,name;

   background test,door,door1,torch;

   //collision obstacle,ground,box;

   int now=0,before=0,interval=62.5;

   perso personnage,personnage1;

   animation running,standing;

   Uint8 *keystates=SDL_GetKeyState(NULL);

   monkey monkeys;
   
   enigme barrels;

   personne pe;

   Uint32 dt;
    
   Uint32 t_prev;

   Ennemi enemy;

   SDL_Rect* pixels=allocate_pixels();

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    TTF_Init();
    srand (time(NULL));
    Mix_Music *musics;
    Mix_Chunk *son=NULL;
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
    musics=Mix_LoadMUS("Audio/wowclassic.mp3");
    Mix_PlayMusic(musics,-1);
    son=Mix_LoadWAV("Audio/click.wav");
    if(son==NULL)
    {
       printf("Failed to load : %s ",Mix_GetError());
    }
    fenetre=SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);

    SDL_Rect pospos;
    pospos.x=1750;
    pospos.y=1000;
    pospos.w=170;
    pospos.h=80;

    //Initialisation de l'ennemi
    initEnnemi(&enemy);

    //Initialisation de l'enigme
    init_enigme(&barrels,&monkeys);

    //Initialisation des personnage
    initperso(&pe,fenetre);
    init_perso(&personnage1,150,700,"Settings/minus.png");

    //Initialisation des cameras
    init_scroll(&scroll,10,0);
    init_scroll(&scroll1,10,0);

    //Initialisation des backgrounds
    initBack(&test,0,0,"background/test.jpg",NULL,NULL);
    init_mask(&test,"background/mask.jpg",fenetre);
    add_background_pos(&test,2,0,300,1000,600);
    add_background_pos(&test,3,960,0,960,1080);

    initBack(&door,900,700,"animation/door.png",NULL,NULL);
    init_animation(&door,"animation/door.png",0,0,121,240);

    initBack(&door1,1500,700,"animation/door.png",NULL,NULL);
    init_animation(&door1,"animation/door.png",0,0,121,240);

    initBack(&torch,200,600,"background/torch.png",NULL,NULL);
    init_animation(&torch,"background/torch.png",0,0,50,124);

    //Initialisation des obstacles
    /*init_obstacle(&test,&obstacle,"animation/door.png",3000,700);
    init_obstacle(&test,&ground,"background/ground.png",0,1220);
    init_obstacle(&test,&box,"background/box.png",1000,1100);*/

    //Initialisation du menu
    initBackground(&bg,"background/background.jpg");
    SDL_BlitSurface(bg.img,NULL,fenetre,&bg.pos1);
    menu_button(&play,"Menu/PLAY_DESELECTED.png",200,150,0,0);
    SDL_BlitSurface(play.img,NULL,fenetre,&play.pos1);
    menu_button(&settings,"Menu/SETTINGS_DESELECTED.png",200,350,0,0);
    SDL_BlitSurface(settings.img,NULL,fenetre,&settings.pos1);
    menu_button(&credits,"Menu/CREDITS_DESELECTED.png",200,550,0,0);
    SDL_BlitSurface(credits.img,NULL,fenetre,&credits.pos1);
    menu_button(&quit,"Menu/QUIT_DESELECTED.png",200,750,0,0);
    SDL_BlitSurface(quit.img,NULL,fenetre,&quit.pos1);


    add_pos(&paper,3,1155,350,45,35);
    add_pos(&paper,2,300,200,45,35);


    //Initialisation des textes
    sprintf(volume,"%d",(int)(Mix_VolumeMusic(-1)/1.28));
    init_text(&vol,"Settings/text.ttf",volume,30,1163,360,0,0,0);
    
    init_text(&fullscreen,"Settings/text.ttf","Appuyez sur F pour basculer en plein ecran",30,970,520,0,0,0);

    init_text(&name,"Settings/text.ttf","unfinished legacy",50,1500,10,255,50,50);
    SDL_BlitSurface(name.txt,NULL,fenetre,&name.postext);

    t.fonttext=TTF_OpenFont("Settings/text.ttf",50);
    t.fontcolor.r=255;
    t.fontcolor.g=255;
    t.fontcolor.b=255;
    
    SDL_Flip(fenetre);
    while (1)
    {
       
        if(h==2)
            {
               if(monkeys.status==0)
               {
                  if(monkeys.enig_lvl==0)
                  {
                     afficher_enigme(barrels,fenetre);
                     monkeys.enig_lvl=1;
                     monkeys.random=rand()%3000 +1000;
                     monkeys.enig_start=SDL_GetTicks()+monkeys.random;
                     monkeys.monkey_number=rand()%5 +1;
                     read_monkey(&monkeys);
                     //printf("(start=%d,now=%d,random=%d,monkey=%d)--",monkeys.enig_start,SDL_GetTicks(),monkeys.random,monkeys.monkey_number);
                  }
                  monkeys.timer=SDL_GetTicks();
               }
               monkey_pop(barrels,&monkeys,fenetre);
            }

       if(h==1)
         {
            now=SDL_GetTicks();
               if(now-before<interval)
               {
                  SDL_Delay(interval-(now-before));
               }
                  color_fix(&pe,test,pixels);
                  if(pe.up==0)
                  {
                     fall_check(&pe,test,pixels);
                  }
         
                     if(door.niveau==0)
                     {
                           door.niveau==1;
                           door.timer=SDL_GetTicks();
                           torch.timer=SDL_GetTicks();
                     }
                        afficherBack(test,fenetre,scroll);
                              continuous_animation(&test,&torch,"background/torch.png",0,35,87,fenetre,11,1);
                              continuous_animation(&test,&door,"animation/door.png",0,121,240,fenetre,4,150);
                              afficherperso(&pe,test);
                                 
                           if(door1.mode!=1)
                           {
                              if(door1.niveau==0)
                              {
                                 door1.niveau==1;
                                 door1.timer=SDL_GetTicks();
                              }
                              object_animation(&test,&door1,"animation/door.png",0,121,240,fenetre,4,start);
                 
                           }
                           //animerEnnemi(&enemy);
                           //deplacer(&enemy,test);
            
            if(!keystates[SDLK_UP])
            {
               pe.jump_ready=1;
            }
            if(keystates[SDLK_UP] && pe.jump_ready==1)
            {
               if(pe.up==0)
               {
                  pe.jump_ready=0;
                  pe.up=1;
                  pe.saut_y=pe.pos1.y;
               }else if(pe.up==1)
               {
                  pe.jump_ready=0;
                  pe.up=2;
                  pe.saut_y=pe.pos1.y;
                  pe.saut_x=-20;
               }
            }
            if(pe.up==1 || pe.up==2)
            {
               
               saut_parabolique(&pe,test,fenetre);
            }else if(pe.right==1 && pe.left==1 && pe.up==0)
            {
               if(pe.fall==0)
               {
                  pe.gravite_y=pe.pos1.y;
                  pe.fall=1;
               }
               gravite_parabolique(&pe,test,fenetre);
            }
            if((keystates[SDLK_LSHIFT] && keystates[SDLK_RIGHT]) || (keystates[SDLK_LSHIFT] && keystates[SDLK_LEFT]))
           {
              if(test.scroll==0)
              {
                 test.scroll=1;
                 pe.init_time=SDL_GetTicks();
              }
              sprint_perso1(&pe);
           }
            if(keystates[SDLK_LCTRL])
           {
              slow_perso1(&pe);
           }
            if(keystates[SDLK_RIGHT] && pe.collision!=3)
            {  
               pe.dep = 1;
               pe.dr = 0;
              if(!keystates[SDLK_LSHIFT])
              {
                 auto_slow_perso1(&pe);
              }
              //afficherperso(&pe,test);
              deplacerperso(&pe, dt,test);
              animerperso(&pe);
            
 
            }
            if(keystates[SDLK_LEFT] && pe.collision!=1)
            {
              pe.dep = 0;
             pe.dr = 1;
              if(!keystates[SDLK_LSHIFT])
              {
                 auto_slow_perso1(&pe);
              }
              //afficherperso(&pe,test);
               deplacerperso(&pe, dt,test);             
               animerperso(&pe);
               
            }
            scrolling_perso1(test,&scroll,&pe,keystates);  
            

            if(p==1)
            {
               if(partage==0)
               {
                  
                  partage_ecran(&scroll,&scroll1);
                  partage=1;
               }
            /*collisionPP(&personnage1,ground,&scroll,test);
            collisionPP(&personnage1,obstacle,&scroll,test);
            gravity(&personnage1,test,fenetre);*/
            afficher_perso2(test,fenetre,scroll1);  
            if(keystates[SDLK_SPACE])
            {
               perso_jump(test,&personnage1,fenetre);
            }
            if((keystates[SDLK_LSHIFT] && keystates[SDLK_RIGHT]) || (keystates[SDLK_LSHIFT] && keystates[SDLK_LEFT]))
           {
              if(test.scroll==0)
              {
                 test.scroll=1;
                 personnage1.init_time=SDL_GetTicks();
              }
              sprint_perso(&personnage1);
           }
            if(keystates[SDLK_d])
            {  
              personnage1.direction=-1;
              if(!keystates[SDLK_LSHIFT])
              {
                 auto_slow_perso(&personnage1);
              }
              move_perso(test,&personnage1,fenetre);  
 
            }
            if(keystates[SDLK_a])
            {
              personnage1.direction=1;
              if(!keystates[SDLK_LSHIFT])
              {
                 auto_slow_perso(&personnage1);
              }
              move_perso(test,&personnage1,fenetre);  
            }
            
            scrolling_perso(test,&scroll1,&personnage1,keystates);
         }
         dt = SDL_GetTicks() - t_prev;    
         SDL_Flip(fenetre);
         before=now;
         }
           
        SDL_PollEvent(&event);

        if(event.type==SDL_QUIT)
        {break;}
        else if(event.type==SDL_KEYDOWN)
        {
           
           if (event.key.keysym.sym==SDLK_f)
           {
              if(h==0)
              {
                 afficher_deselected(&quit,&bg,fenetre,&Q,"Menu/QUIT_DESELECTED.png");
                 afficher_deselected(&credits,&bg,fenetre,&C,"Menu/CREDITS_DESELECTED.png"); 
                 afficher_deselected(&settings,&bg,fenetre,&S,"Menu/SETTINGS_DESELECTED.png");
                 afficher_deselected(&play,&bg,fenetre,&P,"Menu/PLAY_DESELECTED.png");
              }
              SDL_WM_ToggleFullScreen(fenetre);
           }
           else if(event.key.keysym.sym==SDLK_p)
            {
              p=1;
            }
           else if(event.key.keysym.sym==SDLK_h)
           {
              if(h==1)
              {
                 h=2;
              }
           }
           else if(event.key.keysym.sym==SDLK_j)
           {
              if(h==2)
              {
                 h=1;
              }
           }
            else if(event.key.keysym.sym==SDLK_ESCAPE)
               {break;}
            }
            else if(event.type==SDL_MOUSEBUTTONDOWN)
            {
               if((h==2) && (monkeys.status!=0) && (event.button.button==SDL_BUTTON_LEFT) && (monkeys.pos_img.x+monkeys.pos_img.w>event.motion.x && event.motion.x>monkeys.pos_img.x) && (monkeys.pos_img.y+monkeys.pos_img.h>event.motion.y && event.motion.y>monkeys.pos_img.y))
               {
                  Mix_PlayChannel(-1,monkeys.sound,0);
                  SDL_BlitSurface(personnage.img,NULL,fenetre,&monkeys.pos_img);
                  SDL_Flip(fenetre);
                  SDL_Delay(2000);
                  
                  //SDL_BlitSurface(barrels.img,&monkeys.pos_img,fenetre,&monkeys.pos_img);
               }
             if((h==0) && (event.button.button==SDL_BUTTON_LEFT) && (play.pos1.x+438>event.motion.x && event.motion.x>play.pos1.x) && (play.pos1.y+140>event.motion.y && event.motion.y>play.pos1.y))
               {
                Mix_PlayChannel(-1,son,0);
                h=1;
               }
             else if((h==0) && (event.button.button==SDL_BUTTON_LEFT) && (settings.pos1.x+438>event.motion.x && event.motion.x>settings.pos1.x) && (settings.pos1.y+140>event.motion.y && event.motion.y>settings.pos1.y))
             {
                Mix_PlayChannel(-1,son,0);
                if(x==0)
                {
                   menu_button(&paper,"Settings/paper.png",900,200,0,0);
                   menu_button(&plus,"Settings/plus.png",1253,335,0,0);
                   menu_button(&minus,"Settings/minus.png",1050,360,0,0);
                   menu_button(&circle,"Settings/circle.png",1127,322,0,0);
                   afficher_settings(fenetre,&x,paper,circle,plus,minus,vol,fullscreen);
                   printf("%d",x);
                }
                else if(x==1)
                {
                   close_settings(plus,minus,paper,circle,bg,fenetre,&x);
                }

             }
             else if((h==0) && (event.button.button==SDL_BUTTON_LEFT) && (credits.pos1.x+438>event.motion.x && event.motion.x>credits.pos1.x) && (credits.pos1.y+140>event.motion.y && event.motion.y>credits.pos1.y))
             {
                Mix_PlayChannel(-1,son,0);

             }
             else if((h==0) && (event.button.button==SDL_BUTTON_LEFT) && (quit.pos1.x+438>event.motion.x && event.motion.x>quit.pos1.x) && (quit.pos1.y+140>event.motion.y && event.motion.y>quit.pos1.y))
             {
                break;
             }
             else if((x==1) && (event.button.button==SDL_BUTTON_LEFT) && (minus.pos1.x+50>event.motion.x && event.motion.x>minus.pos1.x) && (minus.pos1.y+50>event.motion.y && event.motion.y>minus.pos1.y))
             {
                diminuer_vol(&vol,volume,&v,&paper,fenetre);
             }
             else if((x==1) && (event.button.button==SDL_BUTTON_LEFT) && (plus.pos1.x+50>event.motion.x && event.motion.x>plus.pos1.x) && (plus.pos1.y+50>event.motion.y && event.motion.y>plus.pos1.y))
             {
                augmenter_vol(&vol,volume,&v,&paper,fenetre);
             }
         }

        else if((event.type==SDL_MOUSEMOTION) && (h==0))
         { 
            sprintf(coortext,"%d,%d",event.motion.x,event.motion.y);
            /*SDL_BlitSurface(bg.img,&pospos,fenetre,&pospos);
            afficher_text(t,coortext,fenetre,fenetre->w-t.txt->w-10,fenetre->h-t.txt->h,t.txt->w+10,t.txt->h);*/
            t.txt=TTF_RenderText_Solid(t.fonttext,coortext,t.fontcolor);
            t.postext.x=fenetre->w-t.txt->w-10;
            t.postext.y=fenetre->h-t.txt->h;
            t.postext.w=t.txt->w+10;
            t.postext.h=t.txt->h;
            SDL_BlitSurface(bg.img,&pospos,fenetre,&pospos);
            SDL_BlitSurface(t.txt,NULL,fenetre,&t.postext);
            SDL_UpdateRect(fenetre,pospos.x,pospos.y,pospos.w,pospos.h);
            if((quit.pos1.x+438>event.motion.x && event.motion.x>quit.pos1.x) && (quit.pos1.y+140>event.motion.y && event.motion.y>quit.pos1.y))
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_selected(&quit,&bg,fenetre,&Q,"Menu/QUIT_SELECTED.png");
            }else if(Q==1)
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_deselected(&quit,&bg,fenetre,&Q,"Menu/QUIT_DESELECTED.png");
            }else if((credits.pos1.x+438>event.motion.x && event.motion.x>credits.pos1.x) && (credits.pos1.y+140>event.motion.y && event.motion.y>credits.pos1.y))
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_selected(&credits,&bg,fenetre,&C,"Menu/CREDITS_SELECTED.png");
            }else if(C==1)
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_deselected(&credits,&bg,fenetre,&C,"Menu/CREDITS_DESELECTED.png");    
            }else if((settings.pos1.x+438>event.motion.x && event.motion.x>settings.pos1.x) && (settings.pos1.y+140>event.motion.y && event.motion.y>settings.pos1.y))
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_selected(&settings,&bg,fenetre,&S,"Menu/SETTINGS_SELECTED.png");  
            }else if(S==1)
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_deselected(&settings,&bg,fenetre,&S,"Menu/SETTINGS_DESELECTED.png");  
            }else if((play.pos1.x+438>event.motion.x && event.motion.x>play.pos1.x) && (play.pos1.y+140>event.motion.y && event.motion.y>play.pos1.y))
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_selected(&play,&bg,fenetre,&P,"Menu/PLAY_SELECTED.png");
            }else if(P==1)
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_deselected(&play,&bg,fenetre,&P,"Menu/PLAY_DESELECTED.png");
            }
         }
    }
    free(pixels);
    liberer_enigme(barrels,monkeys);
    Mix_FreeMusic(musics);
    liberer_back(test);
    liberer_back(door);
    liberer_back(door1);
    liberer_perso(&personnage1);
    liberer_perso1(&pe);
    liberer(bg);
    liberer(play);
    liberer(settings);
    liberer(credits);
    liberer(quit);
    SDL_FreeSurface(fenetre);
    TTF_Quit;
    SDL_Quit;
    return 0;
}
