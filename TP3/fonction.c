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

    t_semaine_elt * liste1 = liste;

    while (liste1->suivant!=NULL && semaine>liste1->suivant->numero_semaine){
        printf("%d\n", liste1->numero_semaine);
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

        while (current->suivant!=NULL && current->suivant->numero_semaine!=semaine && current->numero_semaine!=semaine){
            //on verifie toujours le numero de semaine de la semaine suivante pour pouvoir gérer la supression d'une semaine
            //la dernière condition permet simplement de vérifier si le permière élément est le bon
            current=current->suivant;
        }

        if(current->suivant==NULL) {
            if (current->numero_semaine==semaine){ //cas de le liste unique
                if(current->nombre_vaccins-nb_vaccins<=0){
                    free(liste);
                    return 0;
                }
                else {
                    current->nombre_vaccins-=nb_vaccins;
                    return current;
                }
            }
            else { //cas où la semaine n'existe pas
                printf("la semaine n'existe pas\n");
                return 0;
            }
        } else if (current->numero_semaine==semaine) { //cas du premier élément
            if (current->nombre_vaccins-nb_vaccins<=0) {
                free(current);
                return 0;
            }
            else current->nombre_vaccins-=nb_vaccins;

        } else if (current->suivant->nombre_vaccins-nb_vaccins<=0){ //cas simple mais avec suppression de la semaine
            t_semaine_elt *sup=current->suivant;
            current->suivant=current->suivant->suivant; //suppression dans la liste chaîné
            free(sup);
            return 0;
        }
        else { //cas le plus simple : semaien trouvé mais on ne doit pas la supprimer
            current->suivant->nombre_vaccins-=nb_vaccins; //déduction simple
            return liste;
        }

};

