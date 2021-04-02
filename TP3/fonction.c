//
// Created by Anne LAHNECHE on 02/04/2021.
//

#include "fonction.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
t_semaine_elt *creerSemaine(int num_semaine, int nb_vaccins){
    t_semaine_elt * s=malloc(sizeof(t_semaine_elt));
    if (s==NULL) exit(EXIT_FAILURE);

    while (num_semaine<1 || num_semaine>53){
        printf("le nombre de semaine n'est pas valide \n");
        //viderbuffer();
        scanf("%d", &num_semaine);
    }

    while (nb_vaccins<0){
        printf("le nombre de vaccins est inferieur a 0 ceci n'est opas valide\n");
        //viderbuffer();
        scanf("%d", &nb_vaccins);
    }
    s->numero_semaine=num_semaine;
    s->nombre_vaccins=nb_vaccins;
    s->suivant=NULL;
    return s;
};

t_ville_elt *creerVille(char *ville){
    t_ville_elt * t=malloc(sizeof(t_ville_elt));
    if (t==NULL) exit(EXIT_FAILURE);

    t->nom_ville=malloc(sizeof(char)*50);
    strcpy(t->nom_ville,ville);

    t->nombre_vaccins_total=0;
    t->suivant=NULL;
    t->semaines_planifiees=NULL;
};

t_vaccin_elt *creerVaccin(char *marque){
    t_vaccin_elt * v=malloc(sizeof(t_vaccin_elt));
    if (v==NULL) exit(EXIT_FAILURE);
    v->marque=malloc(sizeof(char)*50);
    strcpy(v->marque,marque);

    v->villes_dispo=NULL;
};

t_semaine_elt *ajouterVaccinS(t_semaine_elt *liste, int semaine, int nb_vaccins){

    t_semaine_elt * liste1 =liste;

    while (liste1->suivant!=NULL && semaine<liste1->suivant->numero_semaine){
        liste1=liste1->suivant;
    }

    if (liste1->suivant!=NULL && semaine==liste1->suivant->numero_semaine) liste1->suivant->nombre_vaccins+=nb_vaccins;
    else if(liste1->numero_semaine==semaine) liste1->nombre_vaccins+=nb_vaccins; //cas d'une liste d'un élément de la semaine recheché
    else{
        t_semaine_elt * s;
        s = creerSemaine(semaine,nb_vaccins);
        if (liste1->numero_semaine<semaine) {
            s->suivant = liste1->suivant;
            liste1->suivant = s;
        }
        else {
            s->suivant=liste1;
            liste=s;
        }
    }

    return liste;
};

t_semaine_elt *deduireVaccinS(t_semaine_elt *liste, int semaine, int nb_vaccins){
        t_semaine_elt * current = liste ;

        while (current->suivant!=NULL && current->numero_semaine!=semaine){
            current=current->suivant;
        }

        if(current->suivant==NULL) {
            printf("la semaine n'existe pas\n");
            return 0;
        }

        if(current->nombre_vaccins-nb_vaccins<=0){

        }
        current->nombre_vaccins-=nb_vaccins;

};

