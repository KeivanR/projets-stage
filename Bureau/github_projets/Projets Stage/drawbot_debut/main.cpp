#include <SDL/SDL.h>   /* dorénavant indispensable, pour disposer des .h de SDL */
#define OUI 1     /* utilisé dans la fonction pause() */
#define NON 0
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_framerate.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_imageFilter.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double absol(double a) {
    if(a < 0) a=-a;
    return a;
}
struct cote {
float x,y;
};

int dansrect(SDL_Surface * rectangle,  SDL_Rect   position, SDL_Event event)
{
    if ((event.motion.x>=position.x)&&(event.motion.x<=position.x+rectangle->w)&&(event.motion.y>=position.y)&&(event.motion.y<=position.y+rectangle->h))
        return OUI;
    else return NON;
}
void ecrire(Uint32 couleur, int taille, SDL_Event *event, SDL_Surface * ecran,  SDL_Surface * limite, SDL_Rect pos_null){
    SDL_Event evenement;
    struct cote distance;
    evenement=*event;
    float i, rapport;
    SDL_Surface * rectangle;
     SDL_Rect   position, intermediaire;
     rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE,taille,taille,32,0,0,0,0);
     SDL_FillRect(rectangle,NULL,couleur);
    position.x=evenement.motion.x-rectangle->w/2;
    position.y=evenement.motion.y-rectangle->h/2;
 while (evenement.type!=SDL_MOUSEBUTTONUP)
            {
SDL_PollEvent(&evenement);
                 if (dansrect(limite, pos_null, evenement)==OUI)               {
                distance.x=(evenement.motion.x-rectangle->w/2-position.x);
                distance.y=(evenement.motion.y-rectangle->h/2-position.y);
                if ((distance.x==0)&&(distance.y==0))
                {
                    SDL_BlitSurface(rectangle,NULL,ecran,&position);                    SDL_Flip(ecran) ;
                }
                if (distance.x==0)
                {
                    intermediaire.x=position.x;
                    intermediaire.y=position.y;
                    while ((intermediaire.y-evenement.motion.y+rectangle->h/2)*distance.y<0)
                    {
                      SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                    SDL_Flip(ecran) ;
                   if (distance.y>0) intermediaire.y++;
                   if (distance.y<0) intermediaire.y--;
                    }
                }
                else{
                        if (distance.y==0)
                {
                    intermediaire.x=position.x;
                    intermediaire.y=position.y;
                    while ((intermediaire.x-evenement.motion.x+rectangle->w/2)*distance.x<0)
                    {
                      SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                    SDL_Flip(ecran) ;
                   if (distance.x>0) intermediaire.x++;
                   if (distance.x<0) intermediaire.x--;
                    }
                }
                else{
                        rapport=distance.y/distance.x;
                for (i=0;i<=absol(distance.x)-1;i+=1)
                {
                    intermediaire.x=position.x+i*absol(distance.x)/distance.x;
                       intermediaire.y=position.y+i*rapport*absol(distance.x)/distance.x;
                       SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                    SDL_Flip(ecran) ;
                    while ((intermediaire.y-position.y-(i+1)*rapport*absol(distance.x)/distance.x)*distance.y<0)
                    {
                      SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                    SDL_Flip(ecran) ;
                   if (distance.y>0) intermediaire.y+=1;
                   if (distance.y<0) intermediaire.y-=1;
                    }
                }
                }
                }
            position.x=evenement.motion.x-rectangle->w/2;
      position.y=evenement.motion.y-rectangle->h/2;
               }
            }
             SDL_FreeSurface(rectangle);
             *event=evenement;
};

void changer_taille(int *taille, SDL_Event *event, SDL_Surface * ecran,  SDL_Surface * limite, SDL_Rect pos_null){
    Uint32 noir=SDL_MapRGB(ecran->format,0,0,0);
    Uint32 blanc=SDL_MapRGB(ecran->format,255,255,255);
    SDL_Event evenement;
    evenement=*event;
    SDL_Surface * rectangle;
     SDL_Rect   position;
    position.x=evenement.motion.x;
    position.y=evenement.motion.y;
 while (evenement.type!=SDL_MOUSEBUTTONUP)
            {
SDL_PollEvent(&evenement);
                 if ((dansrect(limite, pos_null, evenement)==OUI)&&(evenement.motion.x>=position.x))
               {
                    SDL_FillRect(limite,NULL,blanc);
                    SDL_BlitSurface(limite,NULL,ecran,&pos_null);
                    rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE,evenement.motion.x-position.x,evenement.motion.x-position.x,32,0,0,0,0);
                    SDL_FillRect(rectangle,NULL,noir);
                    SDL_BlitSurface(rectangle,NULL,ecran,&position);                    *taille=evenement.motion.x-position.x;
                    SDL_Flip(ecran);
               }
            }
            *event=evenement;
}

void contour(SDL_Surface *limite, SDL_Surface *ecran, SDL_Rect pos_null)
                     {
                         Uint32 blanc=SDL_MapRGB(ecran->format,255,255,255);
 Uint32 noir=SDL_MapRGB(ecran->format,0,0,0);
 limite=SDL_CreateRGBSurface(SDL_HWSURFACE,limite->w+2,limite->h+2,32,0,0,0,0);
  pos_null.x--;
      pos_null.y--;
                         SDL_FillRect(limite,NULL,noir);
    SDL_BlitSurface(limite,NULL,ecran,&pos_null);
    limite=SDL_CreateRGBSurface(SDL_HWSURFACE,limite->w-2,limite->h-2,32,0,0,0,0);
      SDL_FillRect(limite,NULL,blanc);
      pos_null.x++;
      pos_null.y++;
    SDL_BlitSurface(limite,NULL,ecran,&pos_null);
                    SDL_Flip(ecran) ;
                     }

int main (int argc , char ** argv)     /* écrire le main ainsi désormais */
{
    int CONTINUER=OUI, i, i_coche=1, taille=3, taille_palettes=50, nb_palettes=20, longueur_limite=800, largeur_limite=700;
    SDL_Surface* gomme = SDL_LoadBMP("gomme.bmp");
    SDL_Rect   position[nb_palettes], pos_null, pos_droite, pos_init;
    SDL_Event event;
    SDL_Surface * ecran, *palette[nb_palettes],*limite, *coche, *droite, *rectangle;   /* déclaration de la variable ecran */
    SDL_WaitEvent(&event);
    pos_droite.x=5+longueur_limite;
    pos_droite.y=taille_palettes+5+taille;
     pos_null.x=5+taille;
     pos_null.y=taille_palettes+5+taille;
     pos_init.x=pos_droite.x+10;
     pos_init.y=pos_droite.y+10;
    SDL_Init(SDL_INIT_VIDEO) ;
    ecran= SDL_SetVideoMode(1200, 700, 32, SDL_HWSURFACE) ;
SDL_WM_SetCaption("DRAWBOT",NULL) ;
 Uint32 blanc=SDL_MapRGB(ecran->format,255,255,255);
 Uint32 noir=SDL_MapRGB(ecran->format,0,0,0),couleur_choisie,couleur[nb_palettes];
 limite=SDL_CreateRGBSurface(SDL_HWSURFACE,longueur_limite-2*taille,largeur_limite-2*taille_palettes-2*taille,32,0,0,0,0);
 droite=SDL_CreateRGBSurface(SDL_HWSURFACE,ecran->w-longueur_limite-2*taille,largeur_limite-2*taille-2*taille_palettes,32,0,0,0,0);
 rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,taille,taille,32,0,0,0,0);
 SDL_FillRect(ecran,NULL,blanc);
  SDL_Flip(ecran) ;
  SDL_FillRect(rectangle,NULL,noir);
  SDL_BlitSurface(rectangle,NULL,ecran,&pos_init);
  SDL_Flip(ecran) ;
  couleur_choisie=noir;
  coche=SDL_CreateRGBSurface(SDL_HWSURFACE,10,10,32,0,0,0,0);
  for (i=1;i<=13;i++)
{
    position[i].x=(taille_palettes+1)*i;
    position[i].y=0;
    palette[i]=SDL_CreateRGBSurface(SDL_HWSURFACE,taille_palettes,taille_palettes,32,0,0,0,0);
    if (i==1) couleur[i]=SDL_MapRGB(ecran->format,0,0,0);
    if ((i>=2)&&(i<=3)) couleur[i]=SDL_MapRGB(ecran->format,120*(i-1),0,0);
    if ((i>=4)&&(i<=5)) couleur[i]=SDL_MapRGB(ecran->format,0,120*(i-3),0);
    if ((i>=6)&&(i<=7)) couleur[i]=SDL_MapRGB(ecran->format,0,0,120*(i-5));
    if ((i>=8)&&(i<=9)) couleur[i]=SDL_MapRGB(ecran->format,120*(i-7),0,120*(i-7));
    if ((i>=10)&&(i<=11)) couleur[i]=SDL_MapRGB(ecran->format,120*(i-9),120*(i-9),0);
    if ((i>=12)&&(i<=13)) couleur[i]=SDL_MapRGB(ecran->format,0,120*(i-11),120*(i-11));
    SDL_FillRect(palette[i],NULL,couleur[i]);
    SDL_BlitSurface(palette[i],NULL,ecran,&position[i]);
                    SDL_Flip(ecran) ;
}
 position[14].x=(taille_palettes+1)*14;
    position[14].y=0;
    SDL_BlitSurface(gomme,NULL,ecran,&position[14]);
                    SDL_Flip(ecran) ;

                    contour(limite, ecran, pos_null);
                    contour (droite, ecran, pos_droite);
  while (CONTINUER==OUI)
  {
      SDL_PollEvent(&event);
      if ((event.type==SDL_QUIT)||((event.type== SDL_KEYDOWN) && ((event.key.keysym.sym==SDLK_ESCAPE)||(event.key.keysym.sym==SDLK_RETURN)))) CONTINUER=NON;
      if (event.type==SDL_MOUSEBUTTONDOWN) {
if (dansrect(limite,pos_null,event)==OUI) ecrire(couleur_choisie,taille,&event,ecran,limite,pos_null);
    for (i=1;i<=13;i++){
       if (dansrect(palette[i],position[i],event)==OUI)
       {
           SDL_FillRect(coche,NULL,couleur_choisie);
           SDL_BlitSurface(coche,NULL,ecran,&position[i_coche]);
           SDL_FillRect(coche,NULL,noir);
           SDL_BlitSurface(coche,NULL,ecran,&position[i]);
           couleur_choisie=couleur[i];
           i_coche=i;
           SDL_Flip(ecran) ;
       }
    }
       if (dansrect(gomme,position[14],event)==OUI)
        {
           SDL_FillRect(coche,NULL,couleur_choisie);
           SDL_BlitSurface(coche,NULL,ecran,&position[i_coche]);
           SDL_FillRect(coche,NULL,noir);
           SDL_BlitSurface(coche,NULL,ecran,&position[14]);
           couleur_choisie=blanc;
           i_coche=14;
           SDL_Flip(ecran);
       }


if (dansrect(droite,pos_droite,event)==OUI)
    changer_taille(&taille, &event, ecran,  droite, pos_droite);
limite=SDL_CreateRGBSurface(SDL_HWSURFACE,longueur_limite-taille,largeur_limite-2*taille_palettes-taille,32,0,0,0,0);
pos_null.x=5+taille/2;
     pos_null.y=taille_palettes+5+taille/2;
  }
  }
return 0 ;
}
