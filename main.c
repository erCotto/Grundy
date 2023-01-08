#include <stdio.h>
#include <stdlib.h>

#define MAXBORNE    100

int grundy[MAXBORNE];

/* retourne le nombre de Grundy de la position (0 => perdant, >0 : gagnant) */
int jeu_ordi(int tas[], int nb_tas, int *tas_choisi, int *pions) {
    int nimber=0;

    /** calcul du nombre de Grundy (nimber) de la position **/

    /******* A REMPLACER **********/
    int i;
    for( i = 0; i < nb_tas - 1; i++){
        nimber ^= grundy[tas[i]];
    }
    //printf("S = %d\n", nimber);

    //printf("Fontion non �crite.\n");
    //exit(-1);
    /******************************/


    if (nimber==0) {
        /** position perdante : on joue le premier coup qui nous tombe sous la main */
        *tas_choisi=0;
        *pions = 1;
        return 0;
    } else {
        /** position gagnante  : on doit trouver un coup gagnant *****/
        i = 0;
        while( (( nimber ^ grundy[tas[i]] ) <= grundy[tas[i]]) && (i < nb_tas - 1) ){
            i++;
            //print("i = %d\n", i);
        }
        *tas_choisi = i;
        int p = 1;
        if( tas[*tas_choisi] != 3 ){
            int q = tas[i] - 1;
            i = 0;
            while( (( nimber ^ grundy[tas[i]] ) != ( grundy[p] ^ grundy[q] )) && (i < nb_tas - 1) ){
                p++;
                q--;
                i++;
                //printf("p = %d\nq = %d\ni = %d\n", p, q, i);
            }
        }
        *pions = p;

        /**************** A REMPLIR **********************************/

        return nimber;
    }
}


void construit_tableau(int borne) {


    /** initialisation **/
    grundy[0] = grundy[1] = grundy[2] = 0;

    /***************** A REMPLACER *************************/
    int i, j;
    for( i = 3; i < MAXBORNE; i++){
        int tab[MAXBORNE];
        for( j = 0; j < MAXBORNE; j++){
            tab[j] = 0;
        }
        for( j = 1; j <= (i - 1)/2; j++){
            tab[grundy[j] ^ grundy[i - j]] = 1;
        }
        j = 0;
        while( tab[j] != 0 ){
            j++;
        }
        grundy[i] = j;
    }

}

void joue_grundy(int initial) {
    int tas[initial];
    int nb_tas=1;
    int ordi_joue=1;

    tas[0] = initial;
    printf("Jeu de Grundy, avec %d pions\n",initial);
    printf("Les tas avec 1 ou 2 pions sont ignores. Le jeu s'arrete quand il n'y a plus de tas disponibles.\n");
    printf("L'ordinateur commence.");
    while (nb_tas>0) {
        int i,p;
        /* affichage */
        printf("%d tas secable(s) : ",nb_tas);
        for (i=0;i<nb_tas-1;i++) { printf("%d, ",tas[i]);  }
        printf("%d\n",tas[i]);
        if (ordi_joue) {
           /* jeu de l'ordinateur */
           /* calcul du nombre de grundy */
           int ret = jeu_ordi(tas,nb_tas,&i,&p);
           printf("Calcul de l'ordinateur : grundy = %d (position %s)\n",ret,(ret==0 ? "perdante" : "gagnante"));
           printf("Ordinateur coupe un tas a %d pions en separant %d pions (reste %d pions)\n",tas[i],p,tas[i]-p);
        } else {
            /* jeu de l'humain */
            p=-1;
            i = nb_tas;
            while (i==nb_tas) {
                printf("Nombre de pions dans le tas a couper ? ");
                scanf("%d",&p);
                i=0; while (i<nb_tas && tas[i]!=p) i++;
                if (i==nb_tas) { printf("Tas non trouve.\n"); }
            }
            p=0;
            while (p<1) {
                printf("Nombre de pions a separer du tas ? ");
                scanf("%d",&p);
                if (p<1 || p>=tas[i] || 2*p==tas[i]) {
                    printf("Nombre invalide, ou separation du tas en parties egales. Recommencer.\n");
                    p=0;
                }
            }
            printf("Humain : separation du tas %d (pions %d) en %d+%d\n",i,tas[i],p,tas[i]-p);
        }
        ordi_joue = !ordi_joue;
        tas[i] = tas[i]-p;
        if (tas[i]<=2) {
            if (p<=2) {
                printf("Ces deux tas sont mis de cote.\n");
                while (i<nb_tas-1) { tas[i] = tas[i+1]; i++; }
                nb_tas--;
            } else {
                printf("Le petit tas est mis de cote1\n");
                tas[i]=p;
            }
        } else if (p<=2) {
            printf("Le petit tas est mis de cote2 %d\n",p);
        } else {
            tas[nb_tas]=p;
            nb_tas++;
        }
    }
    if (ordi_joue) {
        printf("L'ordinateur a perdu.\n");
    } else {
        printf("L'ordinateur a gagne.\n");
    }
}


int main()
{
    int i;
    int nb;
    printf("Taille du jeu (max %d) : ",MAXBORNE-1);
    scanf("%d",&nb),
    construit_tableau(nb);
    printf("Tableau construit.\n");
    for (i=0;i<=nb;i++) {
        printf("Grundy[%d]=%d\n",i,grundy[i]);
    }
    joue_grundy(nb);
    return 0;
}
