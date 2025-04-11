#include <stdio.h>
#include <stdlib.h>


typedef struct Liste {
    int data ;
    struct Liste* next ;
}Liste ;


Liste* ajoutFin(Liste* L, int valeur) {

    Liste* nv = malloc(sizeof(Liste)) ;
    nv->data = valeur ;
    nv->next = NULL ;

    if(L == NULL) L = nv ;
    else {
        Liste* courant = L ;
        while(courant->next != NULL) courant = courant->next ;
        courant->next = nv ;
    }

    return L ;
}

void affichage(Liste* L){
    if(L == NULL) printf("la liste est vide !") ;

    else{
        Liste* courant = L ;
        while(courant != NULL) {
            printf("%d-> ", courant->data) ;
            courant = courant->next ;
        }
    }
    printf("\n");
}

Liste* Echange(Liste* L, int pos1, int pos2){
    Liste* courant = L ;
    for(int i=1; i<pos1; i++) courant = courant->next ;
    Liste* temp = courant ;
    for(int i=pos1; i<pos2; i++) temp = temp->next ;

    int val = temp->data ;
    temp->data = courant->data ;
    courant->data = val ;

    return L ;
}

int tailleListe(Liste* L){
    int taille = 0 ;

    if(L == NULL) return taille ;
    else{
        Liste* courant = L ;
        while(courant != NULL) {
            taille++ ;
            courant = courant->next ;
        }
    }
    return taille ;
}

// la FONCTION DE PARCOURS JUSQU'A LA POSITION MENTIONNER

Liste* parcoursPos(Liste* L, int pos) {

    if(L == NULL) return NULL ;
    Liste* courant = L ;
    for(int j=1; j<pos; j++) courant = courant->next ;

    return courant ;
}


// LA POSITION QUI MANIPOULE LE CHANGEMEMNT DES POSITION
Liste* tas(Liste* L, int taille, int i) {

    if(L == NULL) return ;

    int maxIndx = i ;
    int g = 2*i  ;
    int d = 2*i +1 ;

    Liste* courantG = L, *courantD = L, *courantI = L ;

    if(courantI){
        courantI = parcoursPos(courantI, i) ;
    }else courantI = L ;


    if(g <= taille) {
        courantG = parcoursPos(courantG, g) ;
    } else courantG = NULL ;

    if(courantG && (courantG->data > courantI->data)) maxIndx = g ;

     if(d <= taille) {
        courantD = parcoursPos(courantD, d) ;
     }else courantD = NULL ;


    if(courantD && ( courantD->data > courantI->data )) {
        if(courantD->data > courantG->data) maxIndx = d ;
    }



    if(maxIndx != i){
        L = Echange(L, i, maxIndx) ;
        L = tas(L, taille, maxIndx) ;
    }

    return L ;
}



void triTas(Liste* L, int taille ) {
    for(int i= taille/2; i>=1; i--) {
        L = tas(L, taille, i) ;
    }
    printf("hadi hiya liste :      ") ;
    affichage(L) ;


    for(int i=taille ; i>1; i--) {
        L = Echange(L, 1, i) ;
        printf("hadi %d --->   ", i) ;
        affichage(L) ;
        L = tas(L, i-1, 1) ;

        printf("\n") ;
    }

}



int main()
{

    Liste* L = NULL ;
    L = ajoutFin(L, 44) ;
    L = ajoutFin(L, 10) ;
    L = ajoutFin(L, 8) ;
    L = ajoutFin(L, 78) ;
    L = ajoutFin(L, 20) ;
    L = ajoutFin(L, 14) ;

    affichage(L) ;

    int taille = tailleListe(L) ;

    //tas( L,taille,2 ) ;
    triTas(L, taille ) ;
    affichage(L) ;



    return 0;
}
