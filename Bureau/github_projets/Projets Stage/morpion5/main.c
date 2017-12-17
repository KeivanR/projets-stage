#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>


int main()
{
  struct triplet
  {
    int y[3];
  };
struct triplet x[3];
int i,j,ii,jj,k,correct;
char qui[10];
bool gagne,perdu;
gagne=false;
perdu=false;
    for (i=0;i<=2;i++)
    {
        for (j=0;j<=2;j++)
        {
            x[i].y[j]=0;
        }
    }
    void verif(struct triplet x[3],bool *gagne,bool *perdu)
{

    int s,t,u,v,i,j;
    u=0; v=0;
    *gagne=false;
    *perdu=false;
for (i=0;(i<=2)&&(!(*gagne))&&(!(*perdu));i++)
    {
        s=0; t=0;
        u+=x[i].y[i];
        v+=x[i].y[2-i];
         if ((u==3)||(v==3)) {*gagne=true;}
           if ((u==-3)||(v==-3)) {*perdu=true;}
        for (j=0;(j<=2)&&(!(*gagne))&&(!(*perdu));j++)
        {
            s+=x[i].y[j];
            t+=x[j].y[i];
           if ((s==3)||(t==3)) {*gagne=true;}
           if ((s==-3)||(t==-3)) {*perdu=true;}
        }
    }
}
    void joue(struct triplet x[3],int *pii,int *pjj,int coup)
{
    struct triplet temp[3];
    int m,n,k,l,g;
    *pii=0;
    *pjj=0;
    int p[9];
    int i[9];
    int j[9];
g=0;
            for (m=0;m<=2;m++)
            {
                for (n=0;n<=2;n++)
                {
                     temp[m].y[n]=x[m].y[n];
                }
            }

verif(temp,&gagne,&perdu);
            for (m=0;(m<=2)&&(!(perdu));m++)
{
    for (n=0;(n<=2)&&(!(perdu));n++)
    {
        if (temp[m].y[n]==0)
        {
          temp[m].y[n]=-1;
          verif(temp,&gagne,&perdu);
          temp[m].y[n]=0;
          if (perdu) {*pii=m;*pjj=n;}
        }
    }
}

if (!perdu)
{
for (m=0;(m<=2)&&(!(gagne));m++)
{
    for (n=0;(n<=2)&&(!(gagne));n++)
    {
        if (temp[m].y[n]==0)
        {
          temp[m].y[n]=1;
          verif(temp,&gagne,&perdu);
          perdu=false;
          temp[m].y[n]=0;
          if (gagne) {*pii=m;*pjj=n;}
        }
    }
}
}
if ((!gagne)&&(!perdu))
{
                for (k=0;(k<=2)&&(g!=2);k++)
{
    for (l=0;(l<=2)&&(!(g==2));l++)
    {
        if (temp[k].y[l]==0)
        {
          temp[k].y[l]=-1;
          g=0;
           for (m=0;(m<=2)&&(!(g==2));m++)
{
    for (n=0;(n<=2)&&(!(g==2));n++)
    {
        if (temp[m].y[n]==0)
        {
          temp[m].y[n]=-1;
          verif(temp,&gagne,&perdu);
          temp[m].y[n]=0;
          if (perdu) {g++;}
        }
    }
}
temp[k].y[l]=0;
if (g==2) {*pii=k;*pjj=l;} else {perdu=false;gagne=false;}
        }
    }
}

}
if ((!perdu)&&(!gagne)&&(g!=2))
{
    p[0]=1;
    for (i[0]=0;(i[0]<=2)&&(p[0]==1);i[0]++)
    {
        for (j[0]=0;(j[0]<=2)&&(p[0]==1);j[0]++)
        {
       if (temp[i[0]].y[j[0]]==0)
       {
           temp[i[0]].y[j[0]]=-1;
           p[1]=0;
            for (i[1]=0;(i[1]<=2)&&(p[1]!=10-coup);i[1]++)
    {
        for (j[1]=0;(j[1]<=2)&&(p[1]!=10-coup);j[1]++)
        {
       if (temp[i[1]].y[j[1]]==0)
       {
           temp[i[1]].y[j[1]]=1;
           p[2]=1;
           for (i[2]=0;(i[2]<=2)&&(p[2]==1);i[2]++)
    {
        for (j[2]=0;(j[2]<=2)&&(p[2]==1);j[2]++)
        {
       if (temp[i[2]].y[j[2]]==0)
       {
           temp[i[2]].y[j[2]]=-1;
           p[3]=0;
            for (i[3]=0;(i[3]<=2)&&(p[3]!=8-coup);i[3]++)
    {
        for (j[3]=0;(j[3]<=2)&&(p[3]!=8-coup);j[3]++)
        {
       if (temp[i[3]].y[j[3]]==0)
       {
           temp[i[3]].y[j[3]]=1;
           p[4]=1;
           for (i[4]=0;(i[4]<=2)&&(p[4]==1);i[4]++)
    {
        for (j[4]=0;(j[4]<=2)&&(p[4]==1);j[4]++)
        {
       if (temp[i[4]].y[j[4]]==0)
       {
           temp[i[4]].y[j[4]]=-1;
           p[5]=0;
            for (i[5]=0;(i[5]<=2)&&(p[5]!=6-coup);i[5]++)
    {
        for (j[5]=0;(j[5]<=2)&&(p[5]!=6-coup);j[5]++)
        {
       if (temp[i[5]].y[j[5]]==0)
       {
           temp[i[5]].y[j[5]]=1;
           p[6]=1;
           for (i[6]=0;(i[6]<=2)&&(p[6]==1);i[6]++)
    {
        for (j[6]=0;(j[6]<=2)&&(p[6]==1);j[6]++)
        {
       if (temp[i[6]].y[j[6]]==0)
       {
           temp[i[6]].y[j[6]]=-1;
           p[7]=0;
            for (i[7]=0;(i[7]<=2)&&(p[7]!=4-coup);i[7]++)
    {
        for (j[7]=0;(j[7]<=2)&&(p[7]!=4-coup);j[7]++)
        {
       if (temp[i[7]].y[j[7]]==0)
       {
           temp[i[7]].y[j[7]]=1;
           p[8]=1;
for (i[8]=0;(i[8]<=2)&&(p[8]!=0);i[8]++)
    {
        for (j[8]=0;(j[8]<=2)&&(p[8]!=0);j[8]++)
        {

       if (temp[i[8]].y[j[8]]==0)
       {
           temp[i[8]].y[j[8]]=-1;
verif(x,&gagne,&perdu);
temp[i[8]].y[j[8]]=0;
if (perdu) {p[8]=0;}
       }
        }
    }
       verif(x,&gagne,&perdu);
       temp[i[7]].y[j[7]]=0;
       if (p[8]==0) {p[7]++;}
       if (p[7]==4-coup) {p[6]=0;}
        }
    }
       }
       temp[i[6]].y[j[6]]=0;
        }
    }
           if ((p[6]==0)||(perdu)) {p[5]++;}

       }
       verif(x,&gagne,&perdu);
        temp[i[5]].y[j[5]]=0;

       if (p[5]==6-coup) {p[4]=0;}
        }
    }
       }
        temp[i[4]].y[j[4]]=0;
        }
    }
           if ((p[4]==0)||(perdu)) {p[3]++;}

       }
       verif(x,&gagne,&perdu);
        temp[i[3]].y[j[3]]=0;

       if (p[3]==8-coup) {p[2]=0;}
        }
    }
       }
        temp[i[2]].y[j[2]]=0;
        }
    }
           if ((p[2]==0)||(perdu)) {p[1]++;}

       }
       verif(x,&gagne,&perdu);
        temp[i[1]].y[j[1]]=0;

       if (p[1]==10-coup) {p[0]=0;}
        }
    }
       }
        temp[i[0]].y[j[0]]=0;
        }
    }
    printf("i[0]=%d\n",i[0]);
}
if (p[0]!=1) {*pii=i[0];*pjj=j[0];}
else
{
    *pii=0;*pjj=0;
}
}


}
k=0;
printf("Qui commence ? toi ou moi ?\n");
scanf("%s",qui);
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
 for (i=0;i<=2;i++)
{
for (j=0;j<=2;j++)
{
if  (x[i].y[j]==1) {printf("O");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==-1) {printf("X");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==0) {printf(" ");
if  (j!=2) {printf("|");}}
if (j==2) {printf("\n");}
if ((i!=2)&&(j==2)) {printf("------\n");}
}
}
printf("\n\n");
if (qui[0]=='t')
{
        while ((k<8)&&(!(perdu))&&(!(gagne)))
        {
            joue(x,&ii,&jj,k+2);
            x[ii].y[jj]=-1;
printf("x=%d,y=%d\n",ii+1,jj+1);
printf("\n");
            for (i=0;i<=2;i++)
{
for (j=0;j<=2;j++)
{
if  (x[i].y[j]==1) {printf("O");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==-1) {printf("X");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==0) {printf(" ");
if  (j!=2) {printf("|");}}
if (j==2) {printf("\n");}
if ((i!=2)&&(j==2)) {printf("------\n");}
}
}
printf("\n\n");
 verif(x,&gagne,&perdu);
 if (!perdu)
 {
     correct=0;
     while(correct==0)
     {
            scanf("%d %d",&i,&j);
            printf("\n");
            if (x[i-1].y[j-1]==0) {correct=1;} else {printf("Vous ne pouvez pas jouer la. Rejouez.");}
     }
            x[i-1].y[j-1]=1;
                               for (i=0;i<=2;i++)
{
for (j=0;j<=2;j++)
{
if  (x[i].y[j]==1) {printf("O");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==-1) {printf("X");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==0) {printf(" ");
if  (j!=2) {printf("|");}}
if (j==2) {printf("\n");}
if ((i!=2)&&(j==2)) {printf("------\n");}
}
}
printf("\n\n");
            verif(x,&gagne,&perdu);
 }
 k++;k++;
        }
        if ((!perdu)&&(!gagne))
        {
        joue(x,&ii,&jj,k+2);
            x[ii].y[jj]=-1;
printf("x=%d,y=%d\n",ii+1,jj+1);
printf("\n");
                              for (i=0;i<=2;i++)
{
for (j=0;j<=2;j++)
{
if  (x[i].y[j]==1) {printf("O");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==-1) {printf("X");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==0) {printf(" ");
if  (j!=2) {printf("|");}}
if (j==2) {printf("\n");}
if ((i!=2)&&(j==2)) {printf("------\n");}
}
}
printf("\n\n");
 verif(x,&gagne,&perdu);
        }
}
else
{
    if (qui[0]=='m')
    {
         while ((k<8)&&(!(perdu))&&(!(gagne)))
        {
                    correct=0;
     while(correct==0)
     {
            scanf("%d %d",&i,&j);
            printf("\n");
            if (x[i-1].y[j-1]==0) {correct=1;} else {printf("Vous ne pouvez pas jouer la. Rejouez.");}
     }
 printf("\n");
            x[i-1].y[j-1]=1;
                              for (i=0;i<=2;i++)
{
for (j=0;j<=2;j++)
{
if  (x[i].y[j]==1) {printf("O");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==-1) {printf("X");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==0) {printf(" ");
if  (j!=2) {printf("|");}}
if (j==2) {printf("\n");}
if ((i!=2)&&(j==2)) {printf("------\n");}
}
}
printf("\n\n");
            verif(x,&gagne,&perdu);
 if (!gagne)
 {
    joue(x,&ii,&jj,k+2);
            x[ii].y[jj]=-1;
printf("x=%d,y=%d\n",ii+1,jj+1);
printf("\n");
for (i=0;i<=2;i++)
{
for (j=0;j<=2;j++)
{
if  (x[i].y[j]==1) {printf("O");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==-1) {printf("X");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==0) {printf(" ");
if  (j!=2) {printf("|");}}
if (j==2) {printf("\n");}
if ((i!=2)&&(j==2)) {printf("------\n");}
}
}
printf("\n\n");
 verif(x,&gagne,&perdu);
 }
 k++;k++;
        }
        if ((!perdu)&&(!gagne))
        {
       correct=0;
     while(correct==0)
     {
            scanf("%d %d",&i,&j);
            printf("\n");
            if (x[i-1].y[j-1]==0) {correct=1;} else {printf("Vous ne pouvez pas jouer la. Rejouez.");}
     }
        printf("\n");
            x[i-1].y[j-1]=1;
                                                      for (i=0;i<=2;i++)
{
for (j=0;j<=2;j++)
{
if  (x[i].y[j]==1) {printf("O");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==-1) {printf("X");
if  (j!=2) {printf("|");}}
if  (x[i].y[j]==0) {printf(" ");
if  (j!=2) {printf("|");}}
if (j==2) {printf("\n");}
if ((i!=2)&&(j==2)) {printf("------\n");}
}
}
printf("\n\n");
            verif(x,&gagne,&perdu);
        }
}
else {printf("Misere, que me repond ce chenapan...");}
}
if ((qui[0]=='m')||(qui[0]=='t'))
{
if (gagne) {printf("\n\nVous avez gagne sale goss !\n\n");}
else{
if (perdu) {printf("\n\nVous avez perdu boulet\n\n");}
else {printf("\n\nMatch nul c'etait inutile\n\n");}}
}
getch();
  return 0;
}

