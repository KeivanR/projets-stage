#include <SDL/SDL.h>
//#include <SDL/SDL_rotozoom.h>
//#include <SDL/SDL_framerate.h>
//#include <SDL/SDL_gfxPrimitives.h>
//#include <SDL/SDL_imageFilter.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define OUI 1
#define NON 0
#define MAX 200
#define LG_MAX_TITRE 100

Uint32 obtenirPixel(SDL_Surface *surface, int x, int y)
{
    /*nbOctetsParPixel représente le nombre d'octets utilisés pour stocker un pixel.
    En multipliant ce nombre d'octets par 8 (un octet = 8 bits), on obtient la profondeur de couleur
    de l'image : 8, 16, 24 ou 32 bits.*/
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    /* Ici p est l'adresse du pixel que l'on veut connaitre */
    /*surface->pixels contient l'adresse du premier pixel de l'image*/
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
    /*Gestion différente suivant le nombre d'octets par pixel de l'image*/
    switch(nbOctetsParPixel)
    {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
        /*Ne devrait pas arriver, mais évite les erreurs*/
        default:
            return 0;
    }
}

double absol(double a) {
    if(a < 0) a=-a;
    return a;
}
struct cote {
float x,y;
};

int dansrect(SDL_Surface * rectangle,  SDL_Rect   position, SDL_Event event)
{
    if ((event.motion.x>position.x)&&(event.motion.x<position.x+rectangle->w)&&(event.motion.y>position.y)&&(event.motion.y<position.y+rectangle->h))
        return OUI;
    else return NON;
}
void demarrer(SDL_Surface * ecran, SDL_Surface * image1, SDL_Surface * image2, SDL_Surface * chgt0, SDL_Surface * chgt1, SDL_Surface * chgt2, SDL_Surface * chgt3)
{
    SDL_Rect position;
    int i;
    position.x=200;
    position.y=10;
    SDL_BlitSurface(image1,NULL,ecran,&position);
    SDL_Flip(ecran);
    SDL_Delay(1000);
    SDL_BlitSurface(image2,NULL,ecran,&position);
    SDL_Flip(ecran);
    SDL_Delay(1000);
    for (i=1;i<4;i++){
        SDL_BlitSurface(chgt0,NULL,ecran,&position);
        SDL_Flip(ecran);
        SDL_Delay(500);
        SDL_BlitSurface(chgt1,NULL,ecran,&position);
        SDL_Flip(ecran);
        SDL_Delay(500);
        SDL_BlitSurface(chgt2,NULL,ecran,&position);
        SDL_Flip(ecran);
        SDL_Delay(500);
        SDL_BlitSurface(chgt3,NULL,ecran,&position);
        SDL_Flip(ecran);
        SDL_Delay(500);
        SDL_Flip(ecran);
        }
    position.x=0;
    position.y=0;
    SDL_BlitSurface(image1,NULL,ecran,&position);
    position.x+=500;
    SDL_BlitSurface(image1,NULL,ecran,&position);
}
void afficher_disque(SDL_Surface *ecran, Uint32 couleur, SDL_Rect position, float diametre)
{
    int i,j;
    SDL_Rect pos_pixel;
    SDL_Surface *pixel;
    pixel=SDL_CreateRGBSurface(SDL_HWSURFACE,1,1,32,0,0,0,0);
    SDL_FillRect(pixel,NULL,couleur);
    for (i=position.y;i<=position.y+diametre;i++)
    {
        for (j=position.x;j<=position.x+diametre;j++)
        {
            pos_pixel.x=j;
            pos_pixel.y=i;
            if ((i-position.y-diametre/2)*(i-position.y-diametre/2)+(j-position.x-diametre/2)*(j-position.x-diametre/2)<diametre*diametre/4)
             SDL_BlitSurface(pixel,NULL,ecran,&pos_pixel);
        }
    }

}

void dessiner(SDL_Surface *rectangle, Uint32 couleur, SDL_Event *event, SDL_Surface * ecran,  SDL_Surface * limite, SDL_Rect pos_null, SDL_Rect position_null, int choix_disque){
    SDL_Event evenement;
    struct cote distance;
    evenement=*event;
    float i, rapport,sens;
     SDL_Rect   position, intermediaire;
     SDL_FillRect(rectangle,NULL,couleur);
    position.x=evenement.motion.x-rectangle->w/2;
    position.y=evenement.motion.y-rectangle->h/2;
 while (evenement.type!=SDL_MOUSEBUTTONUP)
            {
SDL_PollEvent(&evenement);
                 if (dansrect(ecran, position_null, evenement)==OUI)
               {
                   if (position.x<pos_null.x-rectangle->w/2) position.x=pos_null.x-rectangle->w/2;
                   if (position.x>pos_null.x+limite->w-rectangle->w/2) position.x=pos_null.x+limite->w-rectangle->w/2;
                   if (position.y<pos_null.y-rectangle->h/2) position.y=pos_null.y-rectangle->h/2;
                   if (position.y>pos_null.y+limite->h-rectangle->h/2) position.y=pos_null.y+limite->h-rectangle->h/2;
                   if (evenement.motion.x<pos_null.x) evenement.motion.x=pos_null.x;
                   if (evenement.motion.x>pos_null.x+limite->w) evenement.motion.x=pos_null.x+limite->w;
                   if (evenement.motion.y<pos_null.y) evenement.motion.y=pos_null.y;
                   if (evenement.motion.y>pos_null.y+limite->h) evenement.motion.y=pos_null.y+limite->h;
                   distance.x=(evenement.motion.x-rectangle->w/2-position.x);
                distance.y=(evenement.motion.y-rectangle->h/2-position.y);
                if ((distance.x==0)&&(distance.y==0))
                {
                    if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&position);
                      else afficher_disque(ecran,couleur,position,rectangle->w);
                       SDL_Flip(ecran) ;
                }
                if (distance.x==0)
                {
                    intermediaire.x=position.x;
                    intermediaire.y=position.y;
                    while ((intermediaire.y-evenement.motion.y+rectangle->h/2)*distance.y<0)
                    {
                      if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                      else afficher_disque(ecran,couleur,intermediaire,rectangle->w);

                   if (distance.y>0) intermediaire.y++;
                   if (distance.y<0) intermediaire.y--;
                    }
                    SDL_Flip(ecran) ;
                }
                else{
                        if (distance.y==0)
                {
                    intermediaire.x=position.x;
                    intermediaire.y=position.y;
                    while ((intermediaire.x-evenement.motion.x+rectangle->w/2)*distance.x<0)
                    {
                      if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                      else afficher_disque(ecran,couleur,intermediaire,rectangle->w);

                   if (distance.x>0) intermediaire.x++;
                   if (distance.x<0) intermediaire.x--;
                    }
                    SDL_Flip(ecran) ;
                }
                else{
                        rapport=distance.y/distance.x;
                        sens=absol(distance.x)/distance.x;
                for (i=0;i<=absol(distance.x)-1;i++)
                {
                    intermediaire.x=position.x+i*sens;
                       intermediaire.y=position.y+i*rapport*sens;
                       if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                      else afficher_disque(ecran,couleur,intermediaire,rectangle->w);

                    while ((intermediaire.y-position.y-(i+1)*rapport*sens)*distance.y<0)
                    {
                     if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                      else afficher_disque(ecran,couleur,intermediaire,rectangle->w);


                   if (distance.y>0) intermediaire.y++;
                   if (distance.y<0) intermediaire.y--;
                    }

                }
                SDL_Flip(ecran) ;
                }
                }
               }
               position.x=evenement.motion.x-rectangle->w/2;
      position.y=evenement.motion.y-rectangle->h/2;
            }
             SDL_FreeSurface(rectangle);
             *event=evenement;
};

void tracer_droite(SDL_Surface *rectangle, Uint32 couleur, SDL_Event *event, SDL_Surface * ecran, SDL_Surface *ecran2,  SDL_Surface * limite, SDL_Rect pos_null, SDL_Rect position_null, int choix_disque){
    SDL_Event evenement;
    struct cote distance;
    evenement=*event;
    float i, rapport;
     SDL_Rect   position, intermediaire, temp;
     SDL_FillRect(rectangle,NULL,couleur);
    position.x=evenement.motion.x-rectangle->w/2;
    position.y=evenement.motion.y-rectangle->h/2;
    SDL_BlitSurface(ecran,NULL,ecran2,&position_null);
 while (evenement.type!=SDL_MOUSEBUTTONUP)
            {
                temp.x=evenement.motion.x-rectangle->w/2;
      temp.y=evenement.motion.y-rectangle->h/2;
SDL_PollEvent(&evenement);
 if ((temp.x!=evenement.motion.x-rectangle->w/2)||(temp.y!=evenement.motion.y-rectangle->h/2))
                                   SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
                 if (dansrect(ecran, position_null, evenement)==OUI)
               {
                   if (evenement.motion.x<pos_null.x) evenement.motion.x=pos_null.x;
                   if (evenement.motion.x>pos_null.x+limite->w) evenement.motion.x=pos_null.x+limite->w;
                   if (evenement.motion.y<pos_null.y) evenement.motion.y=pos_null.y;
                   if (evenement.motion.y>pos_null.y+limite->h) evenement.motion.y=pos_null.y+limite->h;
                   distance.x=(evenement.motion.x-rectangle->w/2-position.x);
                distance.y=(evenement.motion.y-rectangle->h/2-position.y);
                if ((distance.x==0)&&(distance.y==0))
                {
                    if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                      else afficher_disque(ecran,couleur,intermediaire,rectangle->w);
                    SDL_Flip(ecran) ;
                }
                if (distance.x==0)
                {
                    intermediaire.x=position.x;
                    intermediaire.y=position.y;
                    while ((intermediaire.y-evenement.motion.y+rectangle->h/2)*distance.y<0)
                    {
                      if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                      else afficher_disque(ecran,couleur,intermediaire,rectangle->w);

                   if (distance.y>0) intermediaire.y++;
                   if (distance.y<0) intermediaire.y--;
                    }
                    SDL_Flip(ecran) ;
                }
                else{
                        if (distance.y==0)
                {
                    intermediaire.x=position.x;
                    intermediaire.y=position.y;
                    while ((intermediaire.x-evenement.motion.x+rectangle->w/2)*distance.x<0)
                    {
                      if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                      else afficher_disque(ecran,couleur,intermediaire,rectangle->w);

                   if (distance.x>0) intermediaire.x++;
                   if (distance.x<0) intermediaire.x--;
                    }
                    SDL_Flip(ecran) ;
                }
                else{
                        rapport=distance.y/distance.x;
                for (i=0;i<=absol(distance.x)-1;i++)
                {
                    intermediaire.x=position.x+i*absol(distance.x)/distance.x;
                       intermediaire.y=position.y+i*rapport*absol(distance.x)/distance.x;
                       if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                      else afficher_disque(ecran,couleur,intermediaire,rectangle->w);

                    while ((intermediaire.y-position.y-(i+1)*rapport*absol(distance.x)/distance.x)*distance.y<0)
                    {
                      if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&intermediaire);
                      else afficher_disque(ecran,couleur,intermediaire,rectangle->w);

                   if (distance.y>0) intermediaire.y++;
                   if (distance.y<0) intermediaire.y--;
                    }
                }
                 SDL_Flip(ecran) ;
                }
                }
               }
            }
             SDL_FreeSurface(rectangle);
             *event=evenement;
};

void changer_taille_carre(float *taille, SDL_Event *event, SDL_Surface * ecran,  SDL_Surface * limite, SDL_Rect pos_null, int choix_disque){
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
                 if ((evenement.motion.x<pos_null.x+limite->w)&&(evenement.motion.x-position.x<pos_null.y+limite->h-position.y)&&(evenement.motion.x>=position.x))
               {
                    SDL_FillRect(limite,NULL,blanc);
                    SDL_BlitSurface(limite,NULL,ecran,&pos_null);
                    rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE,evenement.motion.x-position.x,evenement.motion.x-position.x,32,0,0,0,0);
                    SDL_FillRect(rectangle,NULL,noir);
                    if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&position);
                      else afficher_disque(ecran,noir,position,rectangle->w);
                    *taille=evenement.motion.x-position.x;
                    SDL_Flip(ecran);
               }
            }
            SDL_FreeSurface(rectangle);
            *event=evenement;
}

void changer_taille_rect(float *taille, float* taille2, SDL_Event *event, SDL_Surface * ecran,  SDL_Surface * limite, SDL_Rect pos_null){
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
                 if ((dansrect(limite, pos_null, evenement)==OUI)&&(evenement.motion.x>=position.x)&&(evenement.motion.y>=position.y))
               {
                    SDL_FillRect(limite,NULL,blanc);
                    SDL_BlitSurface(limite,NULL,ecran,&pos_null);
                    rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE,evenement.motion.x-position.x,evenement.motion.y-position.y,32,0,0,0,0);
                    SDL_FillRect(rectangle,NULL,noir);
                    SDL_BlitSurface(rectangle,NULL,ecran,&position);
                    *taille=evenement.motion.x-position.x;
                    *taille2=evenement.motion.y-position.y;
                    SDL_Flip(ecran);
               }
            }
            SDL_FreeSurface(rectangle);
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
                    SDL_FreeSurface(limite);
                     }
void curseur(SDL_Surface *limite_int, SDL_Surface *rectangle, Uint32 couleur, SDL_Surface *ecran, SDL_Surface *ecran2, SDL_Event event, SDL_Rect position_null, SDL_Rect pos_null, int choix_disque){
    SDL_Rect pos_init;
    pos_init.x=event.motion.x-rectangle->w/2;
    pos_init.y=event.motion.y-rectangle->h/2;
    if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&pos_init);
                      else afficher_disque(ecran,couleur,pos_init,rectangle->w);
    SDL_Flip(ecran);
     SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
};


void remplissage(SDL_Surface *ecran, SDL_Surface *pixel, int x, int y, Uint32 couleur_initiale, Uint32 couleur, int taille_marge, SDL_Rect pos_init)
{
    cote distance;
SDL_Rect position;
position.x=x;
position.y=y;
distance.x=absol(pos_init.x-x);
distance.y=absol(pos_init.y-y);
SDL_FillRect(pixel,NULL,couleur);
    SDL_BlitSurface(pixel,NULL,ecran,&position);
if ((distance.x<100)&&(distance.y<100)&&(couleur_initiale!=couleur))

   {
       if (couleur_initiale==obtenirPixel(ecran,x+1,y)) {remplissage(ecran,pixel,x+1,y,couleur_initiale,couleur,taille_marge,pos_init);}

    if ((couleur_initiale==obtenirPixel(ecran,x-1,y))&&(x!=8)) {remplissage(ecran,pixel,x-1,y,couleur_initiale,couleur,taille_marge,pos_init);}

    if ((couleur_initiale==obtenirPixel(ecran,x,y-1))&&(y!=8+taille_marge)) {remplissage(ecran,pixel,x,y-1,couleur_initiale,couleur,taille_marge,pos_init);}

    if (couleur_initiale==obtenirPixel(ecran,x,y+1)) {remplissage(ecran,pixel,x,y+1,couleur_initiale,couleur,taille_marge,pos_init);}
   }

};

void ecrire(SDL_Event event, char mot[LG_MAX_TITRE], int *i, int *indice_lettre, SDL_Rect position, SDL_Surface *ecran){
    char doc[LG_MAX_TITRE];
    int k;
    doc[0]='l';
    doc[1]='_';
    doc[3]='.';
    doc[4]='b';
    doc[5]='m';
    doc[6]='p';
    doc[7]='\0';
    SDL_Surface* lettre[26];
    for (k=0;k<26;k++){
        doc[2]='a'+k;
        lettre[k]= SDL_LoadBMP(doc);
    }

 position.x+=*i;
 if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_SPACE)) {
 mot[*indice_lettre]=' ';
         *i+=10; *indice_lettre+=1;
}
if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_q)) {
 mot[*indice_lettre]='a';
        SDL_BlitSurface(lettre[0],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}
if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_b)) {
 mot[*indice_lettre]='b';
        SDL_BlitSurface(lettre[1],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}
if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_c)) {
 mot[*indice_lettre]='c';
        SDL_BlitSurface(lettre[2],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_d)) {
 mot[*indice_lettre]='d';
        SDL_BlitSurface(lettre[3],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_e)) {
 mot[*indice_lettre]='e';
        SDL_BlitSurface(lettre[4],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_f)) {
 mot[*indice_lettre]='f';
        SDL_BlitSurface(lettre[5],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=7; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_g)) {
 mot[*indice_lettre]='g';
        SDL_BlitSurface(lettre[6],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_h)) {
 mot[*indice_lettre]='h';
        SDL_BlitSurface(lettre[7],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_i)) {
 mot[*indice_lettre]='i';
        SDL_BlitSurface(lettre[8],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=5; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_j)) {
 mot[*indice_lettre]='j';
        SDL_BlitSurface(lettre[9],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=5; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_k)) {
 mot[*indice_lettre]='k';
        SDL_BlitSurface(lettre[10],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_l)) {
 mot[*indice_lettre]='l';
        SDL_BlitSurface(lettre[11],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=5;*indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_SEMICOLON)) {
 mot[*indice_lettre]='m';
        SDL_BlitSurface(lettre[12],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=15; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_n)) {
 mot[*indice_lettre]='n';
        SDL_BlitSurface(lettre[13],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_o)) {
 mot[*indice_lettre]='o';
        SDL_BlitSurface(lettre[14],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_p)) {
 mot[*indice_lettre]='p';
        SDL_BlitSurface(lettre[15],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_a)) {
 mot[*indice_lettre]='q';
        SDL_BlitSurface(lettre[16],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_r)) {
 mot[*indice_lettre]='r';
        SDL_BlitSurface(lettre[17],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=7; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_s)) {
 mot[*indice_lettre]='s';
        SDL_BlitSurface(lettre[18],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_t)) {
 mot[*indice_lettre]='t';
        SDL_BlitSurface(lettre[19],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_u)) {
 mot[*indice_lettre]='u';
        SDL_BlitSurface(lettre[20],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_v)) {
 mot[*indice_lettre]='v';
        SDL_BlitSurface(lettre[21],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_z)) {
 mot[*indice_lettre]='w';
        SDL_BlitSurface(lettre[22],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=15; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_x)) {
 mot[*indice_lettre]='x';
        SDL_BlitSurface(lettre[23],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_y)) {
 mot[*indice_lettre]='y';
        SDL_BlitSurface(lettre[24],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_w)) {
 mot[*indice_lettre]='z';
        SDL_BlitSurface(lettre[25],NULL,ecran,&position);
         SDL_Flip(ecran);
         *i+=10; *indice_lettre+=1;
}
}

void memorisation(float memoire[50][MAX],SDL_Surface *ecran,SDL_Surface *ecran2,SDL_Surface *droite,SDL_Surface *limite,SDL_Surface *limite_int,
                  SDL_Rect position_null,  SDL_Rect pos_droite, SDL_Rect pos_jonction, SDL_Rect pos_null, float taille,
                  float taille2, Uint32 couleur_choisie, int num_ecran, SDL_Surface *memoire_surface[MAX], Uint32 memoire_couleur[MAX]){
                  SDL_BlitSurface(ecran,NULL,memoire_surface[num_ecran],&position_null);
                    memoire[1][num_ecran]=droite->w;
       memoire[2][num_ecran]=limite->w;
       memoire[3][num_ecran]=limite_int->w;
       memoire[4][num_ecran]=pos_droite.x;
       memoire[5][num_ecran]=pos_jonction.x;
       memoire[6][num_ecran]=taille;
       memoire[7][num_ecran]=taille2;
       memoire[8][num_ecran]=limite->h;
       memoire[9][num_ecran]=limite_int->h;
       memoire[10][num_ecran]=pos_null.x;
       memoire[11][num_ecran]=pos_null.y;
       memoire_couleur[num_ecran]=couleur_choisie;
                  }

void retour(float memoire[50][MAX],SDL_Surface *ecran,SDL_Surface *ecran2,SDL_Surface *droite,SDL_Surface *limite,SDL_Surface *limite_int,
                  SDL_Rect position_null,  SDL_Rect pos_droite, SDL_Rect pos_jonction, SDL_Rect pos_null, float taille,
                  float taille2, Uint32 couleur_choisie, int num_ecran, SDL_Surface *memoire_surface[MAX], Uint32 memoire_couleur[MAX]){

                  SDL_BlitSurface(memoire_surface[num_ecran],NULL,ecran,&position_null);
    droite->w=memoire[1][num_ecran];
       limite->w=memoire[2][num_ecran];
       limite_int->w=memoire[3][num_ecran];
       pos_droite.x=memoire[4][num_ecran];
       pos_jonction.x=memoire[5][num_ecran];
       taille=memoire[6][num_ecran];
       taille2=memoire[7][num_ecran];
       limite->h=memoire[8][num_ecran];
       limite_int->h=memoire[9][num_ecran];
       pos_null.x=memoire[10][num_ecran];
       pos_null.y=memoire[11][num_ecran];
       couleur_choisie=memoire_couleur[num_ecran];
                  }

 void aide_direct(SDL_Surface *rectangle, SDL_Surface *aide_rectangle,SDL_Rect pos_rect, SDL_Surface *ecran, SDL_Surface *ecran2, SDL_Event *event){
 SDL_Event evenement = *event;
 SDL_Rect position;
 position.y=0;
 position.x=0;
 if (dansrect(rectangle,pos_rect,evenement)==OUI){
            SDL_BlitSurface(ecran,NULL,ecran2,&position);
            position.y=ecran->h-30;
            position.x=10;
            while ((evenement.type!=SDL_MOUSEBUTTONDOWN)&&(dansrect(rectangle,pos_rect,evenement)==OUI))
                   {
              SDL_BlitSurface(aide_rectangle,NULL,ecran,&position);
              SDL_Flip(ecran);
            SDL_PollEvent(&evenement);
                }
            position.y=0;
            position.x=0;
            SDL_BlitSurface(ecran2,NULL,ecran,&position);
            SDL_Flip(ecran);
}
*event=evenement;
 }

void afficher_degrade(SDL_Surface *ecran, float longueur, float largeur, SDL_Rect position)
{
    float i,j;
    SDL_Surface *pixel;
    SDL_Rect pos;
    pixel=SDL_CreateRGBSurface(SDL_HWSURFACE,1,1,32,0,0,0,0);
    pos.y=position.y;
    for (i=0;i<=floor(longueur/3);i++)
    {
            for (j=0;j<=floor(largeur/2);j++)
    {
        SDL_FillRect(pixel,NULL,SDL_MapRGB(ecran->format,6*j*255/largeur/longueur*i+255-j*2*255/largeur,-6*j*255/largeur/longueur*i+255,255-j*2*255/largeur));
        pos.x=i+position.x;
        pos.y=j+position.y;
        SDL_BlitSurface(pixel,NULL,ecran,&pos);
    }
            for (j=0;j<=floor(largeur/2);j++)
    {
        SDL_FillRect(pixel,NULL,SDL_MapRGB(ecran->format,3*(255-j*2*255/largeur)/longueur*i,-3*(255-j*2*255/largeur)/longueur*i+255-j*2*255/largeur,0));
        pos.x=i+position.x;
        pos.y=j+position.y+largeur/2;
        SDL_BlitSurface(pixel,NULL,ecran,&pos);
    }
    }

    for (i=0;i<=floor(longueur/3);i++)
    {
            for (j=0;j<=floor(largeur/2);j++)
    {
        SDL_FillRect(pixel,NULL,SDL_MapRGB(ecran->format,-6*j*255/largeur/longueur*i+255,255-j*2*255/largeur,6*j*255/largeur/longueur*i+255-j*2*255/largeur));
        pos.x=i+position.x+longueur/3;
        pos.y=j+position.y;
        SDL_BlitSurface(pixel,NULL,ecran,&pos);
    }
            for (j=0;j<=floor(largeur/2);j++)
    {
        SDL_FillRect(pixel,NULL,SDL_MapRGB(ecran->format,-3*(255-j*2*255/largeur)/longueur*i+255-j*2*255/largeur,0,3*(255-j*2*255/largeur)/longueur*i));
        pos.x=i+position.x+longueur/3;
        pos.y=j+position.y+largeur/2;
        SDL_BlitSurface(pixel,NULL,ecran,&pos);
    }
    }

for (i=0;i<=floor(longueur/3);i++)
    {
            for (j=0;j<=floor(largeur/2);j++)
    {
        SDL_FillRect(pixel,NULL,SDL_MapRGB(ecran->format,255-j*2*255/largeur,6*j*255/largeur/longueur*i+255-j*2*255/largeur,-6*j*255/largeur/longueur*i+255));
        pos.x=i+position.x+2*longueur/3;
        pos.y=j+position.y;
        SDL_BlitSurface(pixel,NULL,ecran,&pos);
    }
            for (j=0;j<=floor(largeur/2);j++)
    {
        SDL_FillRect(pixel,NULL,SDL_MapRGB(ecran->format,0,3*(255-j*2*255/largeur)/longueur*i,-3*(255-j*2*255/largeur)/longueur*i+255-j*2*255/largeur));
        pos.x=i+position.x+2*longueur/3;
        pos.y=j+position.y+largeur/2;
        SDL_BlitSurface(pixel,NULL,ecran,&pos);
    }
    }

}


void afficher_croix(SDL_Surface *ecran, int longueur, int largeur, SDL_Rect position,Uint32 couleur)
{
    int i;
     SDL_Surface *pixel=SDL_CreateRGBSurface(SDL_HWSURFACE,1,1,32,0,0,0,0);;
     SDL_FillRect(pixel,NULL,couleur);
     position.x-=longueur;
    for (i=0;i<=2*longueur;i++)
    {
        SDL_BlitSurface(pixel,NULL,ecran,&position);
        position.x++;
    }
    position.x-=longueur+1;
    position.y-=largeur;
    for (i=0;i<=2*largeur;i++)
    {
        SDL_BlitSurface(pixel,NULL,ecran,&position);
        position.y++;
    }
}

void contour_rectangle(SDL_Surface *ecran, float largeur, float longueur, SDL_Rect position, SDL_Surface *rectangle, int choix_disque, Uint32 couleur)
{
    int i,j;
    SDL_FillRect(rectangle,NULL,couleur);
    for (j=0;j<=1;j++)
    {
    for (i=0;i<=longueur;i++)
    {
      if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&position);
                      else afficher_disque(ecran,couleur,position,rectangle->w);
        position.x++;
    }
    position.x-=floor(longueur)+1;
    position.y+=largeur;
    }
    position.y-=2*largeur;
    for (j=0;j<=1;j++)
    {
    for (i=0;i<=largeur;i++)
    {
      if (choix_disque==NON) SDL_BlitSurface(rectangle,NULL,ecran,&position);
                      else afficher_disque(ecran,couleur,position,rectangle->w);
        position.y++;
    }
    position.y-=floor(largeur)+1;
    position.x+=longueur;
    }
}

int main (int argc , char ** argv)
{
    int CONTINUER=OUI, i,j,k, i_coche=1, taille_palettes=30, taille_marge=50, nb_palettes=50, longueur_limite=1100, largeur_limite=730,
    choix_carre=OUI, choix_souris=NON, choix_trait=NON, num_ecran=0, suivant=0, alea, deja_enr=NON, modif=NON, bon_click=NON,
    choix_txt=NON, choix_disque=NON;
    float taille=3, taille2=3, ecart, memoire[50][MAX];
     char titre[LG_MAX_TITRE],mot[LG_MAX_TITRE];
    SDL_Surface* gomme = SDL_LoadBMP("gomme.bmp"), * carre_txt = SDL_LoadBMP("carre.bmp"), *enregistrer=SDL_LoadBMP("enregistrer.bmp"),
    *rectangle_txt = SDL_LoadBMP("rectangle.bmp"), * carre_selec_txt = SDL_LoadBMP("carre_selec.bmp"),
    *rectangle_selec_txt = SDL_LoadBMP("rectangle_selec.bmp"),*disque_selec_txt = SDL_LoadBMP("disque_selec.bmp"),
    *disque_txt = SDL_LoadBMP("disque.bmp"),
     *souris = SDL_LoadBMP("souris.bmp"),
    *dfleche=SDL_LoadBMP("dfleche.bmp"), *trait=SDL_LoadBMP("trait.bmp"),*trait_selec=SDL_LoadBMP("trait_selec.bmp"),
    *choix=SDL_LoadBMP("choix.bmp"),*titre_txt=SDL_LoadBMP("titre.bmp"),*question_quit=SDL_LoadBMP("question_quit.bmp"),
    *non_txt=SDL_LoadBMP("non.bmp"),*oui_txt=SDL_LoadBMP("oui.bmp"),*annuler_txt=SDL_LoadBMP("annuler.bmp"),
    *a_txt=SDL_LoadBMP("a_txt.bmp"), /* *l_txt=SDL_LoadBMP("l_l.bmp"),*/ *fichier=SDL_LoadBMP("Fichier.bmp"),
    *ouvrir=SDL_LoadBMP("ouvrir.bmp"), *nouveau=SDL_LoadBMP("nouveau.bmp"), *aide=SDL_LoadBMP("aide.bmp"),
    *aide_icone=SDL_LoadBMP("aide_icone.bmp"), *aide_fichier=SDL_LoadBMP("aide_fichier.bmp"),
    *aide_choundeh=SDL_LoadBMP("aide_choundeh.bmp"),*aide_couleurs=SDL_LoadBMP("aide_couleurs.bmp"),
    *aide_gomme=SDL_LoadBMP("aide_gomme.bmp"),*aide_souris=SDL_LoadBMP("aide_souris.bmp"),
    *aide_trait=SDL_LoadBMP("aide_trait.bmp"),*aide_droite=SDL_LoadBMP("aide_droite.bmp"),
    *aide_texte=SDL_LoadBMP("aide_texte.bmp"), *aide_rectangle=SDL_LoadBMP("aide_rectangle.bmp"),
    *aide_carre=SDL_LoadBMP("aide_carre.bmp"),*aide_aide=SDL_LoadBMP("aide_aide.bmp"),
    *aide_disque=SDL_LoadBMP("aide_disque.bmp"),

    *Choundeh=SDL_LoadBMP("Choundeh.bmp"),*champ_de_ble=SDL_LoadBMP("champ_de_ble.bmp"),*chandelier=SDL_LoadBMP("chandelier.bmp"),
    *champignon=SDL_LoadBMP("champignon.bmp"),*chouquette=SDL_LoadBMP("chouquette.bmp"),
    *chouiner=SDL_LoadBMP("chouiner.bmp"),*choubaka=SDL_LoadBMP("choubaka.bmp"),
    *chapeau_de_paille=SDL_LoadBMP("chapeau_de_paille.bmp"),*choucroute=SDL_LoadBMP("choucroute.bmp"),
    *Schumacher=SDL_LoadBMP("Schumacher.bmp"),*Chamonix=SDL_LoadBMP("Chamonix.bmp"),
    *chanteur_ne=SDL_LoadBMP("chanteur_ne.bmp"),*choux_de_nez=SDL_LoadBMP("choux_de_nez.bmp"),

    *demarrage=SDL_LoadBMP("demarrage.bmp"), *demarrage_drawbot=SDL_LoadBMP("demarrage_drawbot.bmp"),
    *chgt1=SDL_LoadBMP("demarrage_drawbot_chgt1.bmp"), *chgt2=SDL_LoadBMP("demarrage_drawbot_chgt2.bmp"),
    *chgt3=SDL_LoadBMP("demarrage_drawbot_chgt3.bmp"),*chgt0=SDL_LoadBMP("demarrage_drawbot_chgt0.bmp");
    SDL_Rect   position[nb_palettes], pos_null, pos_droite, pos_init, position_null, pos_jonction, pos_ecrire, pos_limite;
    SDL_Event event;
    SDL_Surface * ecran, *ecran2, *ecran_init, *enr_ques, *palette[nb_palettes],*limite, *limite_int, *coche, *droite,
    *rectangle, *jonction, *droite_jonction, *memoire_surface[MAX], *fichier_rect, *segment_hor,*degrade, *pixel;
    pos_droite.x=longueur_limite+3;
    pos_droite.y=taille_marge+5+taille;
    pos_limite.x=9;
    pos_limite.y=9+taille_marge;
    position_null.x=0;
    position_null.y=0;
     pos_null.x=5+taille;
     pos_null.y=taille_marge+5+taille2;
     pos_init.x=pos_droite.x+10;
     pos_init.y=pos_droite.y+10;
     pos_jonction.x=pos_droite.x-3;
     pos_jonction.y=pos_droite.y;
    SDL_Init(SDL_INIT_VIDEO) ;
    ecran= SDL_SetVideoMode(1300, 700, 32, SDL_HWSURFACE) ;
    ecran2= SDL_CreateRGBSurface(SDL_HWSURFACE,ecran->w,ecran->h,32,0,0,0,0);
    ecran_init=SDL_CreateRGBSurface(SDL_HWSURFACE,ecran->w,ecran->h,32,0,0,0,0);
    for (i=0;i<=MAX;i++) memoire_surface[i]= SDL_CreateRGBSurface(SDL_HWSURFACE,ecran->w,ecran->h,32,0,0,0,0);
SDL_WM_SetCaption("DRAWBOT","K.R.") ;
 Uint32 blanc=SDL_MapRGB(ecran->format,255,255,255);
 Uint32 noir=SDL_MapRGB(ecran->format,0,0,0),couleur_choisie,couleur[nb_palettes], memoire_couleur[MAX], couleur_temp[10];
 limite=SDL_CreateRGBSurface(SDL_HWSURFACE,longueur_limite-2*taille,largeur_limite-2*taille_marge-2*taille,32,0,0,0,0);
 limite_int=SDL_CreateRGBSurface(SDL_HWSURFACE,limite->w-6,limite->h-6,32,0,0,0,0);
 droite=SDL_CreateRGBSurface(SDL_HWSURFACE,ecran->w-limite->w-pos_null.x-5,largeur_limite-2*taille-2*taille_marge,32,0,0,0,0);
 rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,taille,taille2,32,0,0,0,0);
 jonction=SDL_CreateRGBSurface(SDL_HWSURFACE,10,limite->h,32,0,0,0,0);
 droite_jonction=SDL_CreateRGBSurface(SDL_HWSURFACE,1,limite->h,32,0,0,0,0);
 fichier_rect=SDL_CreateRGBSurface(SDL_HWSURFACE,200,300,32,0,0,0,0);
 segment_hor=SDL_CreateRGBSurface(SDL_HWSURFACE,fichier_rect->w-10,1,32,0,0,0,0);
 pixel=SDL_CreateRGBSurface(SDL_HWSURFACE,1,1,32,0,0,0,0);
  enr_ques=SDL_CreateRGBSurface(SDL_HWSURFACE,700,100,32,0,0,0,0);
  degrade=SDL_CreateRGBSurface(SDL_HWSURFACE,900,600,32,0,0,0,0);
  SDL_FillRect(jonction,NULL,blanc);
 SDL_FillRect(ecran,NULL,blanc);
  SDL_Flip(ecran) ;
  SDL_FillRect(rectangle,NULL,noir);
  couleur_choisie=noir;
  coche=SDL_CreateRGBSurface(SDL_HWSURFACE,8,8,32,0,0,0,0);
  srand(time(NULL));
  demarrer(ecran,demarrage,demarrage_drawbot,chgt0,chgt1,chgt2,chgt3);
  //SDL_Surface * zoomage = rotozoomSurface (demarrage, 0, 0.5, 0);
//  SDL_BlitSurface(zoomage,NULL,ecran,&position_null);
  for (i=1;i<=13;i++)
{
    position[i].x=(taille_palettes+1)*i+100;
    position[i].y=10;
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
}
 position[14].x=(taille_palettes+1)*14+105;
    position[14].y=10;
    SDL_BlitSurface(gomme,NULL,ecran,&position[14]);
     position[15].x=position[14].x+450;
    position[15].y=15;
    SDL_BlitSurface(carre_selec_txt,NULL,ecran,&position[15]);
     position[16].x=position[15].x+70;
    position[16].y=15;
    SDL_BlitSurface(rectangle_txt,NULL,ecran,&position[16]);
    position[17].x=10;
    position[17].y=15;
    SDL_BlitSurface(fichier,NULL,ecran,&position[17]);
    position[18].x=position[14].x+55;
    position[18].y=10;
    SDL_BlitSurface(souris,NULL,ecran,&position[18]);
    position[19].x=position[18].x+55;
    position[19].y=10;
    SDL_BlitSurface(trait,NULL,ecran,&position[19]);
    position[20].x=position[19].x+70;
    position[20].y=10;
    SDL_BlitSurface(Choundeh,NULL,ecran,&position[20]);
     position[21].x=position[20].x+110;
    position[21].y=10;
    SDL_BlitSurface(a_txt,NULL,ecran,&position[21]);
    position[22].x=ecran->w-30;
    position[22].y=15;
    SDL_BlitSurface(aide_icone,NULL,ecran,&position[22]);
    position[23].x=position[16].x+100;
    position[23].y=15;
    SDL_BlitSurface(disque_txt,NULL,ecran,&position[23]);
                    SDL_Flip(ecran) ;

                    contour(limite, ecran, pos_null);
                    contour (droite, ecran, pos_droite);
                    SDL_BlitSurface(ecran,NULL,ecran_init,&position_null);
                    SDL_BlitSurface(rectangle,NULL,ecran,&pos_init);
memorisation(memoire,ecran,ecran2,droite,limite,limite_int,position_null,pos_droite,pos_jonction,pos_null,taille,
             taille2,couleur_choisie,num_ecran,memoire_surface,memoire_couleur);
  SDL_Flip(ecran) ;
  while (CONTINUER==OUI)
  {
      SDL_WaitEvent(&event);
      if (((event.type==SDL_QUIT)&&(modif==NON))||((event.type== SDL_KEYDOWN) && ((event.key.keysym.sym==SDLK_ESCAPE)||(event.key.keysym.sym==SDLK_RETURN)))) CONTINUER=NON;
if ((event.type==SDL_QUIT)&&(modif==OUI)){
    SDL_BlitSurface(ecran,NULL,ecran2,&position_null);
            position_null.x+=10;
    position_null.y+=10;
        contour (enr_ques, ecran, position_null);
        position_null.x+=10;
        position_null.y+=10;
        SDL_BlitSurface(question_quit,NULL,ecran,&position_null);
        position_null.x+=150;
        position_null.y+=40;
        SDL_BlitSurface(oui_txt,NULL,ecran,&position_null);
        position_null.x+=150;
        SDL_BlitSurface(non_txt,NULL,ecran,&position_null);
        position_null.x+=150;
        SDL_BlitSurface(annuler_txt,NULL,ecran,&position_null);
        SDL_Flip(ecran);
bon_click=NON;
        while ((CONTINUER==OUI)&&(bon_click==NON)){
            position_null.x=470;
        position_null.y=60;
        SDL_WaitEvent(&event);
        if (event.type==SDL_MOUSEBUTTONDOWN){
          if (dansrect(annuler_txt,position_null,event)==OUI) bon_click=OUI;
           position_null.x-=150;
           if (dansrect(non_txt,position_null,event)==OUI)
           {
               bon_click=OUI;
               CONTINUER=NON;
           }
           position_null.x-=150;
           if (dansrect(oui_txt,position_null,event)==OUI)
           {
               bon_click=OUI;
               if (deja_enr==NON){
            position_null.x+=2;
    position_null.y+=2;
        contour (enr_ques, ecran, position_null);
        position_null.x+=10;
        position_null.y+=20;
        SDL_BlitSurface(titre_txt,NULL,ecran,&position_null);
position_null.x+=50;
        SDL_Flip(ecran);
        i=0;
        j=0;
        SDL_WaitEvent(&event);
        while (event.key.keysym.sym!=SDLK_RETURN){
                ecrire(event,titre,&i,&j,position_null,ecran);
                SDL_WaitEvent(&event);
        }
         titre[j]='.';
        titre[j+1]='b';
        titre[j+2]='m';
        titre[j+3]='p';
        titre[j+4]='\0';
    }
    position_null.x=0;
    position_null.y=0;
 SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
   SDL_SaveBMP(ecran, titre);
               CONTINUER=NON;
           }
        }
        }
        bon_click=NON;
        position_null.x=0;
                position_null.y=0;
                SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
                SDL_Flip(ecran);
                 if (CONTINUER==OUI) SDL_WaitEvent(&event);
        }
if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_LEFT)&&(num_ecran>0))
{
    suivant++;
    num_ecran--;
    retour(memoire,ecran,ecran2,droite,limite,limite_int,position_null,pos_droite,pos_jonction,pos_null,taille,
             taille2,couleur_choisie,num_ecran,memoire_surface,memoire_couleur);
    SDL_Flip(ecran);
}

if ((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_RIGHT)&&(suivant>0))
{
    suivant--;
    num_ecran++;
     retour(memoire,ecran,ecran2,droite,limite,limite_int,position_null,pos_droite,pos_jonction,pos_null,taille,
             taille2,couleur_choisie,num_ecran,memoire_surface,memoire_couleur);
    SDL_Flip(ecran);
}

if ((choix_txt==NON)&&(choix_souris==NON)&&(dansrect(limite_int,pos_null,event)==OUI)){
            rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,taille,taille2,32,0,0,0,0);
            SDL_FillRect(rectangle,NULL,couleur_choisie);
            SDL_BlitSurface(ecran,NULL,ecran2,&position_null);
            while ((event.type!=SDL_MOUSEBUTTONDOWN)&&(dansrect(limite_int,pos_null,event)==OUI))
                   {
            curseur(limite_int,rectangle, couleur_choisie, ecran, ecran2, event, position_null, pos_null, choix_disque);
            SDL_PollEvent(&event);}
            SDL_Flip(ecran);
}
for (i=1;i<=13;i++) aide_direct(palette[i],aide_couleurs,position[i],ecran,ecran2,&event);
aide_direct(gomme,aide_gomme,position[14],ecran,ecran2,&event);
aide_direct(souris,aide_souris,position[18],ecran,ecran2,&event);
aide_direct(trait,aide_trait,position[19],ecran,ecran2,&event);
aide_direct(droite,aide_droite,pos_droite,ecran,ecran2,&event);
aide_direct(a_txt,aide_texte,position[21],ecran,ecran2,&event);
aide_direct(aide_icone,aide_aide,position[22],ecran,ecran2,&event);
aide_direct(carre_selec_txt,aide_carre,position[15],ecran,ecran2,&event);
aide_direct(rectangle_selec_txt,aide_rectangle,position[16],ecran,ecran2,&event);
aide_direct(disque_selec_txt,aide_disque,position[23],ecran,ecran2,&event);
aide_direct(fichier,aide_fichier,position[17],ecran,ecran2,&event);
aide_direct(Choundeh,aide_choundeh,position[20],ecran,ecran2,&event);

if ((dansrect(Choundeh,position[20],event)==OUI)||(dansrect(fichier,position[17],event)==OUI)){
         SDL_ShowCursor(SDL_DISABLE);
            SDL_BlitSurface(ecran,NULL,ecran2,&position_null);
            while ((event.type!=SDL_MOUSEBUTTONDOWN)&&((dansrect(Choundeh,position[20],event)==OUI)||(dansrect(enregistrer,position[17],event)==OUI)))
                   {
            curseur(Choundeh,choix, couleur_choisie, ecran, ecran2, event, position_null, position[20], 0);
            SDL_PollEvent(&event);}
            SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
            SDL_Flip(ecran);
 SDL_ShowCursor(SDL_ENABLE);
}

if ((choix_souris==OUI)&&(dansrect(jonction,pos_jonction,event)==OUI)){
        SDL_ShowCursor(SDL_DISABLE);
            SDL_BlitSurface(ecran,NULL,ecran2,&position_null);
            while ((event.type!=SDL_MOUSEBUTTONDOWN)&&(dansrect(jonction,pos_jonction,event)==OUI))
                   {
            curseur(jonction,dfleche, couleur_choisie, ecran, ecran2, event, position_null, pos_jonction,0);
            SDL_PollEvent(&event);}
SDL_Flip(ecran);
SDL_ShowCursor(SDL_ENABLE);
}

      if (event.type==SDL_MOUSEBUTTONDOWN) {

            if(event.button.button == SDL_BUTTON_RIGHT) {
                    if ((dansrect(limite_int,pos_null,event)==OUI)&&(choix_souris==NON))
                        {
                            pos_init.x=event.motion.x;
                            pos_init.y=event.motion.y;
                couleur_temp[0]=obtenirPixel(ecran,pos_init.x,pos_init.y);
                remplissage(ecran,pixel,event.motion.x,event.motion.y,couleur_temp[0],couleur_choisie,taille_marge,pos_init);
                modif=OUI;
                suivant=0;
       if (num_ecran<MAX)
        {
            num_ecran++;
       memorisation(memoire,ecran,ecran2,droite,limite,limite_int,position_null,pos_droite,pos_jonction,pos_null,taille,
             taille2,couleur_choisie,num_ecran,memoire_surface,memoire_couleur);
       }
                        }

                    for (i=1;i<=13;i++){
       if (dansrect(palette[i],position[i],event)==OUI)
       {
           j=0;
           couleur_temp[0]=couleur[i];

           SDL_BlitSurface(ecran,NULL,ecran2,&position_null);
           position[i].x+=10;
           position[i].y+=10;
           SDL_BlitSurface(coche,NULL,ecran,&position[i]);
           position[i].x-=10;
           position[i].y-=10;
           afficher_degrade(ecran,900,600,pos_limite);
           pos_limite.x+=20+degrade->w;
           SDL_BlitSurface(oui_txt,NULL,ecran,&pos_limite);
           pos_limite.y+=50;
           SDL_BlitSurface(annuler_txt,NULL,ecran,&pos_limite);
           pos_limite.y+=50;
           pos_limite.x+=10;
           SDL_BlitSurface(palette[i],NULL,ecran,&pos_limite);
           pos_limite.x+=40;
           SDL_BlitSurface(palette[i],NULL,ecran,&pos_limite);
           pos_limite.x-=70+degrade->w;
           pos_limite.y-=100;
            SDL_Flip(ecran);
            bon_click=NON;

            while(bon_click==NON)
            {
                SDL_WaitEvent(&event);
                while ((event.type!=SDL_MOUSEBUTTONDOWN)&&(bon_click==NON))
                {
                    if (dansrect(degrade,pos_limite,event)==OUI)
                    {
                        if (j==1)
                        {
                            pos_init.x-=3;
                            for (k=0;k<=4;k++)
                        {
                            pos_init.x++;
                            SDL_FillRect(pixel,NULL,couleur_temp[k]);
                            SDL_BlitSurface(pixel,NULL,ecran,&pos_init);
                        }
                        pos_init.x-=2;pos_init.y-=3;
                        for (k=5;k<=9;k++)
                        {pos_init.y++;
                        SDL_FillRect(pixel,NULL,couleur_temp[k]);
                            SDL_BlitSurface(pixel,NULL,ecran,&pos_init);
                        }
                        pos_init.y-=2;
                        }
                    SDL_FillRect(palette[i],NULL,obtenirPixel(ecran,event.motion.x,event.motion.y));
                    if (j==1) afficher_croix(ecran,2,2,pos_init,noir);
             pos_limite.x+=30+degrade->w;
           pos_limite.y+=100;
           SDL_BlitSurface(palette[i],NULL,ecran,&pos_limite);
           pos_limite.x-=30+degrade->w;
           pos_limite.y-=100;
           SDL_Flip(ecran);

                    }
                    SDL_PollEvent(&event);
                }

                if (dansrect(degrade,pos_limite,event)==OUI)
                    {
                       if (j==1)
                        {
                            pos_init.x-=3;
                            for (k=0;k<=4;k++)
                        {
                            pos_init.x++;
                            SDL_FillRect(pixel,NULL,couleur_temp[k]);
                            SDL_BlitSurface(pixel,NULL,ecran,&pos_init);
                        }
                        pos_init.x-=2;pos_init.y-=3;
                        for (k=5;k<=9;k++)
                        {pos_init.y++;
                        SDL_FillRect(pixel,NULL,couleur_temp[k]);
                            SDL_BlitSurface(pixel,NULL,ecran,&pos_init);
                        }
                        pos_init.y-=2;
                        }
                        j=1;
                        pos_init.x=event.motion.x-3;pos_init.y=event.motion.y;
                        for (k=0;k<=4;k++)
                        {pos_init.x++;
                        couleur_temp[k]=obtenirPixel(ecran,pos_init.x,pos_init.y);}
                        pos_init.x-=2;pos_init.y-=3;
                        for (k=5;k<=9;k++)
                        {pos_init.y++;
                        couleur_temp[k]=obtenirPixel(ecran,pos_init.x,pos_init.y);}
                        pos_init.y-=2;
                        SDL_FillRect(palette[i],NULL,couleur_temp[2]);
                        afficher_croix(ecran,2,2,pos_init,noir);
                        pos_limite.x+=70+degrade->w;
           pos_limite.y+=100;
           SDL_BlitSurface(palette[i],NULL,ecran,&pos_limite);
            pos_limite.x-=70+degrade->w;
           pos_limite.y-=100;
                        SDL_Flip(ecran);
                    }

                   pos_limite.x+=20+degrade->w;
                   if (dansrect(oui_txt,pos_limite,event)==OUI)
                   {
                       bon_click=OUI;
                        SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
                        SDL_FillRect(palette[i],NULL,couleur_temp[2]);
                        SDL_BlitSurface(palette[i],NULL,ecran,&position[i]);
                        if (couleur_choisie==couleur[i]) {
                                couleur_choisie=couleur_temp[2];
                        SDL_BlitSurface(coche,NULL,ecran,&position[i]);
                        }
                        couleur[i]=couleur_temp[2];
                        SDL_Flip(ecran);
                   }

                    pos_limite.y+=50;
                   if (dansrect(annuler_txt,pos_limite,event)==OUI)
                   {
                       bon_click=OUI;
                        SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
                        SDL_Flip(ecran);
                   }
                    pos_limite.x-=20+degrade->w;
           pos_limite.y-=50;
                                        }
                                        modif=OUI;
                suivant=0;
       if (num_ecran<MAX)
        {
            num_ecran++;
       memorisation(memoire,ecran,ecran2,droite,limite,limite_int,position_null,pos_droite,pos_jonction,pos_null,taille,
             taille2,couleur_choisie,num_ecran,memoire_surface,memoire_couleur);
       }
       }
                    }
            }
else{
if ((dansrect(limite_int,pos_null,event)==OUI)&&(choix_souris==NON)&&(choix_trait==NON)&&(choix_txt==NON))
{
    rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE,taille,taille2,32,0,0,0,0);
    dessiner(rectangle,couleur_choisie,&event,ecran,limite_int,pos_null, position_null,choix_disque);
     modif=OUI;
    suivant=0;
       if (num_ecran<MAX)  {
            num_ecran++;
       memorisation(memoire,ecran,ecran2,droite,limite,limite_int,position_null,pos_droite,pos_jonction,pos_null,taille,
             taille2,couleur_choisie,num_ecran,memoire_surface,memoire_couleur);
       }

}



if ((dansrect(limite_int,pos_null,event)==OUI)&&(choix_souris==NON)&&(choix_trait==NON)&&(choix_txt==OUI))
{
    i=0;
    j=0;
    pos_ecrire.x=event.motion.x;
    pos_ecrire.y=event.motion.y-15;
    SDL_BlitSurface(ecran,NULL,ecran2,&position_null);
    SDL_FillRect(coche,NULL,noir);
    SDL_BlitSurface(coche,NULL,ecran,&pos_ecrire);
    SDL_Flip(ecran);
        SDL_WaitEvent(&event);
        SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
        while (event.type!=SDL_MOUSEBUTTONDOWN){
                SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
                ecrire(event,mot,&i,&j,pos_ecrire,ecran);
        SDL_BlitSurface(ecran,NULL,ecran2,&position_null);
        pos_ecrire.x-=10;
        SDL_BlitSurface(coche,NULL,ecran,&pos_ecrire);
        pos_ecrire.x+=10;
        SDL_Flip(ecran);
                SDL_WaitEvent(&event);
        }
        SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
        SDL_Flip(ecran);
         modif=OUI;
        suivant=0;
       if (num_ecran<MAX)  {
            num_ecran++;
       memorisation(memoire,ecran,ecran2,droite,limite,limite_int,position_null,pos_droite,pos_jonction,pos_null,taille,
             taille2,couleur_choisie,num_ecran,memoire_surface,memoire_couleur);
       }
}



if ((dansrect(limite_int,pos_null,event)==OUI)&&(choix_souris==NON)&&(choix_trait==OUI)&&(choix_txt==NON))
{
    rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE,taille,taille2,32,0,0,0,0);
    tracer_droite(rectangle,couleur_choisie,&event,ecran,ecran2,limite_int,pos_null, position_null,choix_disque);
    modif=OUI;
    suivant=0;
       if (num_ecran<MAX)  {
            num_ecran++;
       memorisation(memoire,ecran,ecran2,droite,limite,limite_int,position_null,pos_droite,pos_jonction,pos_null,taille,
             taille2,couleur_choisie,num_ecran,memoire_surface,memoire_couleur);
       }

}

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
           choix_souris=NON;
           choix_txt=NON;
           SDL_BlitSurface(a_txt,NULL,ecran,&position[21]);
       }
    }

    if (dansrect(trait,position[19],event)==OUI) {
            if (choix_trait==NON){
        SDL_BlitSurface(trait_selec,NULL,ecran,&position[19]);
        choix_trait=OUI;
        choix_txt=NON;
           SDL_BlitSurface(a_txt,NULL,ecran,&position[21]);
        }
        else {
            SDL_BlitSurface(trait,NULL,ecran,&position[19]);
        choix_trait=NON;
        }
        SDL_Flip(ecran);
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
           choix_souris=NON;
           choix_txt=NON;
           SDL_BlitSurface(a_txt,NULL,ecran,&position[21]);
       }
       if (dansrect(souris,position[18],event)==OUI)
        {
           SDL_FillRect(coche,NULL,couleur_choisie);
           SDL_BlitSurface(coche,NULL,ecran,&position[i_coche]);
           SDL_FillRect(coche,NULL,noir);
           SDL_BlitSurface(coche,NULL,ecran,&position[18]);
           couleur_choisie=blanc;
           i_coche=18;
           choix_souris=OUI;
           choix_txt=NON;
           SDL_BlitSurface(a_txt,NULL,ecran,&position[21]);
           SDL_Flip(ecran);
       }

if (dansrect(a_txt,position[21],event)==OUI)
        {
           SDL_FillRect(coche,NULL,couleur_choisie);
           SDL_BlitSurface(coche,NULL,ecran,&position[i_coche]);
           SDL_FillRect(coche,NULL,noir);
           SDL_BlitSurface(coche,NULL,ecran,&position[21]);
           couleur_choisie=blanc;
           i_coche=21;
           choix_souris=NON;
           choix_trait=NON;
           choix_txt=OUI;
           SDL_Flip(ecran);
       }

if (dansrect(aide_icone,position[22],event)==OUI)
        {
            i=choix_souris;
            choix_souris=OUI;
    SDL_BlitSurface(ecran,NULL,ecran2,&position_null);
    position[22].x-=300;
    position[22].y+=10;
    SDL_BlitSurface(aide,NULL,ecran,&position[22]);
    SDL_Flip(ecran);
    SDL_WaitEvent(&event);
    while ((event.type!=SDL_MOUSEBUTTONDOWN)||(dansrect(aide,position[22],event)==OUI)) SDL_WaitEvent(&event);
    position[22].x+=300;
    position[22].y-=10;
    choix_souris=i;
    SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
     SDL_Flip(ecran);
        }

if (dansrect(Choundeh,position[20],event)==OUI) {
      pos_null.x-=floor(0.5*taille)-1;
        pos_null.y-=floor(0.5*taille2)-1;
        alea=rand();
       if (alea % 12 ==0) SDL_BlitSurface(champ_de_ble,NULL,ecran,&pos_null);
        if (alea % 12 ==1) SDL_BlitSurface(chandelier,NULL,ecran,&pos_null);
        if (alea % 12 ==2) SDL_BlitSurface(choux_de_nez,NULL,ecran,&pos_null);
        if (alea % 12 ==3) SDL_BlitSurface(champignon,NULL,ecran,&pos_null);
        if (alea % 12 ==4) SDL_BlitSurface(chapeau_de_paille,NULL,ecran,&pos_null);
        if (alea % 12 ==5) SDL_BlitSurface(Schumacher,NULL,ecran,&pos_null);
        if (alea % 12 ==6) SDL_BlitSurface(Chamonix,NULL,ecran,&pos_null);
        if (alea % 12 ==7) SDL_BlitSurface(chouquette,NULL,ecran,&pos_null);
        if (alea % 12 ==8) SDL_BlitSurface(chouiner,NULL,ecran,&pos_null);
        if (alea % 12 ==9) SDL_BlitSurface(choucroute,NULL,ecran,&pos_null);
        if (alea % 12 ==10) SDL_BlitSurface(choubaka,NULL,ecran,&pos_null);
        if (alea % 12 ==11) SDL_BlitSurface(chanteur_ne,NULL,ecran,&pos_null);
        pos_null.x+=floor(0.5*taille)-1;
        pos_null.y+=floor(0.5*taille2)-1;
        SDL_Flip(ecran);
        modif=OUI;
        suivant=0;
       if (num_ecran<MAX)  {
            num_ecran++;
       memorisation(memoire,ecran,ecran2,droite,limite,limite_int,position_null,pos_droite,pos_jonction,pos_null,taille,
             taille2,couleur_choisie,num_ecran,memoire_surface,memoire_couleur);
       }

}

if (dansrect(carre_txt,position[15],event)==OUI) {
        SDL_BlitSurface(rectangle_txt,NULL,ecran,&position[16]);
        SDL_BlitSurface(carre_selec_txt,NULL,ecran,&position[15]);
        SDL_BlitSurface(disque_txt,NULL,ecran,&position[23]);
        choix_carre=OUI;
        choix_disque=NON;
        SDL_Flip(ecran);
}
if (dansrect(rectangle_txt,position[16],event)==OUI) {
        SDL_BlitSurface(rectangle_selec_txt,NULL,ecran,&position[16]);
        SDL_BlitSurface(carre_txt,NULL,ecran,&position[15]);
        SDL_BlitSurface(disque_txt,NULL,ecran,&position[23]);
        choix_carre=NON;
        choix_disque=NON;
        SDL_Flip(ecran);
}
if (dansrect(disque_txt,position[23],event)==OUI) {
        SDL_BlitSurface(disque_selec_txt,NULL,ecran,&position[23]);
        SDL_BlitSurface(carre_txt,NULL,ecran,&position[15]);
        SDL_BlitSurface(rectangle_txt,NULL,ecran,&position[16]);
        choix_carre=OUI;
        choix_disque=OUI;
        SDL_Flip(ecran);
}

if ((dansrect(droite,pos_droite,event)==OUI)&&(choix_souris==NON))
{
    if (choix_carre==OUI){
            i=taille;
    changer_taille_carre(&taille, &event, ecran,  droite, pos_droite,choix_disque);
    limite->w+=i-taille; limite_int->w=limite->w-6;
    limite->h+=i-taille; limite_int->h=limite->h-6;
pos_null.x=9+taille/2;
     pos_null.y=taille_marge+9+taille/2;
     taille2=taille;}
     else
     {
         i=taille; j=taille2;
         changer_taille_rect(&taille, &taille2, &event, ecran,  droite, pos_droite);
limite->w+=i-taille; limite_int->w=limite->w-6;
    limite->h+=j-taille2; limite_int->h=limite->h-6;
pos_null.x=9+taille/2;
     pos_null.y=taille_marge+9+taille2/2;
     }
     suivant=0;
       if (num_ecran<MAX)  {
            num_ecran++;
       memorisation(memoire,ecran,ecran2,droite,limite,limite_int,position_null,pos_droite,pos_jonction,pos_null,taille,
             taille2,couleur_choisie,num_ecran,memoire_surface,memoire_couleur);
       }
}

if (dansrect(fichier,position[17],event)==OUI)
{
    i=choix_souris;
    choix_souris=OUI;
    SDL_BlitSurface(ecran,NULL,ecran2,&position_null);
    position[17].y+=20;
    contour (fichier_rect, ecran, position[17]);
    position[17].y+=20;
    SDL_BlitSurface(nouveau,NULL,ecran,&position[17]);
     position[17].y+=50;
    SDL_BlitSurface(segment_hor,NULL,ecran,&position[17]);
     position[17].y+=10;
    SDL_BlitSurface(ouvrir,NULL,ecran,&position[17]);
     position[17].y+=50;
    SDL_BlitSurface(segment_hor,NULL,ecran,&position[17]);
     position[17].y+=10;
    SDL_BlitSurface(enregistrer,NULL,ecran,&position[17]);
    SDL_Flip(ecran);
    SDL_WaitEvent(&event);
    while (event.type!=SDL_MOUSEBUTTONDOWN) SDL_WaitEvent(&event);
if (dansrect(enregistrer,position[17],event)==OUI)
{
    SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
    if (deja_enr==NON){
            position_null.x+=2;
    position_null.y+=2;
        contour (enr_ques, ecran, position_null);
        position_null.x+=10;
        position_null.y+=20;
        SDL_BlitSurface(titre_txt,NULL,ecran,&position_null);
position_null.x+=50;
        SDL_Flip(ecran);
        i=0;
        j=0;
        SDL_WaitEvent(&event);
        while (event.key.keysym.sym!=SDLK_RETURN){
                ecrire(event,titre,&i,&j,position_null,ecran);
                SDL_WaitEvent(&event);
        }
        position_null.x=0;
        position_null.y=0;
          SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
        SDL_Flip(ecran);
        titre[j]='.';
        titre[j+1]='b';
        titre[j+2]='m';
        titre[j+3]='p';
        titre[j+4]='\0';
    }
    SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
   SDL_SaveBMP(ecran, titre);
    SDL_FillRect(coche,NULL,noir);
    SDL_BlitSurface(coche,NULL,ecran,&position[17]);
    SDL_Flip(ecran);
    SDL_FillRect(coche,NULL,blanc);
    SDL_BlitSurface(coche,NULL,ecran,&position[17]);
    deja_enr=OUI;
    modif=NON;
}
position[17].y-=60;
if (dansrect(ouvrir,position[17],event)==OUI) {
            position_null.x+=2;
    position_null.y+=2;
        contour (enr_ques, ecran, position_null);
        position_null.x+=10;
        position_null.y+=20;
        SDL_BlitSurface(titre_txt,NULL,ecran,&position_null);
position_null.x+=50;
        SDL_Flip(ecran);
        i=0;
        j=0;
        SDL_WaitEvent(&event);
        while (event.key.keysym.sym!=SDLK_RETURN){
                ecrire(event,titre,&i,&j,position_null,ecran);
                SDL_WaitEvent(&event);
        }
        position_null.x=0;
        position_null.y=0;
        titre[j]='.';
        titre[j+1]='b';
        titre[j+2]='m';
        titre[j+3]='p';
        titre[j+4]='\0';/*
SDL_BlitSurface(ecran2,NULL,ecran,&pos_droite);
SDL_BlitSurface(SDL_LoadBMP(titre),NULL,ecran,&pos_null);*/

    }

position[17].y-=60;
if (dansrect(nouveau,position[17],event)==OUI) {
        modif=NON;
        SDL_BlitSurface(ecran_init,NULL,ecran,&position_null);

}
position[17].y-=20;
if (dansrect(fichier_rect,position[17],event)==NON) SDL_BlitSurface(ecran2,NULL,ecran,&position_null);
position[17].y-=20;
choix_souris=i;
SDL_Flip(ecran);
}

if ((dansrect(jonction,pos_jonction,event)==OUI)&&(choix_souris==OUI))
{
    SDL_ShowCursor(SDL_DISABLE);
    ecart=pos_droite.x-event.motion.x;
   while (event.type!=SDL_MOUSEBUTTONUP)

   {

       if ((event.motion.x>10)&&(event.motion.x<ecran->w-10))
       {
           pos_jonction.x=pos_droite.x-5;
 SDL_BlitSurface(jonction,NULL,ecran,&pos_jonction);
       limite->w=limite->w+event.motion.x+ecart-pos_droite.x;
       limite_int->w=limite->w-6;
       pos_droite.x=event.motion.x+ecart;
      droite->w=ecran->w-pos_droite.x;
        pos_droite.x--;
        SDL_BlitSurface(droite_jonction,NULL,ecran,&pos_droite);
        pos_droite.x++;
        SDL_Flip(ecran);
       }
        SDL_PollEvent(&event);
   }
   droite=SDL_CreateRGBSurface(SDL_HWSURFACE,ecran->w-pos_droite.x-10,droite->h,32,0,0,0,0);
   modif=OUI;
   suivant=0;
       if (num_ecran<MAX)  {
            num_ecran++;
       memorisation(memoire,ecran,ecran2,droite,limite,limite_int,position_null,pos_droite,pos_jonction,pos_null,taille,
             taille2,couleur_choisie,num_ecran,memoire_surface,memoire_couleur);
       }
SDL_ShowCursor(SDL_ENABLE);
}
}
  }
  }
return 0 ;
}
