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

    if (liste == NULL){
        printf("il n'y a pas de semaine\n");
        t_semaine_elt * s = creerSemaine(semaine, nb_vaccins);
        return s;
    }
    else {
            t_semaine_elt *liste1 = liste;

            while (liste1->suivant != NULL && semaine > liste1->suivant->numero_semaine) {
                printf("%d\n", liste1->numero_semaine);
                liste1 = liste1->suivant;
            }

            if (liste1->suivant != NULL && semaine == liste1->suivant->numero_semaine)
                liste1->suivant->nombre_vaccins += nb_vaccins; // cas normal
            else if (liste1->numero_semaine == semaine)
                liste1->nombre_vaccins += nb_vaccins; //cas d'une liste d'un élément de la semaine recheché
            else {
                t_semaine_elt *s;
                s = creerSemaine(semaine, nb_vaccins);
                if (liste1->numero_semaine < semaine) {
                    s->suivant = liste1->suivant;
                    liste1->suivant = s;
                } else {
                    s->suivant = liste1;
                    liste = s;
                }
            }

            return liste;
        }
};


t_semaine_elt *deduireVaccinS(t_semaine_elt *liste, int semaine, int nb_vaccins){
    if (liste ==NULL){
        printf("il n'y a pas de semaine planifie");
        return 0;
    }
    else {
        t_semaine_elt *current = liste;

        while (current->suivant != NULL && current->suivant->numero_semaine<semaine) {
            current = current->suivant;
        }

        if (current->numero_semaine == semaine) { //cas de le liste unique ou du premier élément
            if (current->nombre_vaccins - nb_vaccins <= 0) {
                if (current->suivant==NULL){ //cas de la liste unique
                    free(liste);
                    return 0;
                }else{ //cas du premier élément
                    t_semaine_elt * s = liste->suivant;
                    free(liste);
                    return s;
                }
            } else {
                current->nombre_vaccins -= nb_vaccins;
                return current;
            }
        }else if(current->suivant==NULL){ //on a parcouru toute la liste et la semaine n'existe pas
            printf("la semaine n'existe pas\n");
            return 0;
        }else{ //cas le plus simple
            if (current->suivant->nombre_vaccins - nb_vaccins <=0) { //cas simple mais avec suppression de la semaine
                t_semaine_elt *sup = current->suivant;
                current->suivant = current->suivant->suivant; //suppression dans la liste chaîné
                free(sup);
                return liste;
            } else { //cas le plus simple : semaien trouvé mais on ne doit pas la supprimer
                current->suivant->nombre_vaccins -= nb_vaccins; //déduction simple
            return liste;
            }
        }
    }
}


t_ville_elt *ajouterVaccinV(t_ville_elt *liste, char* ville, int semaine, int nb_vaccins){
    t_ville_elt* parcours;

    if (liste==NULL) {
        printf("la liste est nulle, je cree la nouvelle ville %s\n", ville);
        liste = creerVille(ville);
        liste->nombre_vaccins_total += nb_vaccins;
        liste->semaines_planifiees=ajouterVaccinS(liste->semaines_planifiees,semaine,nb_vaccins);
        return liste;
    }
    else {
        parcours = liste;
        while (parcours!=NULL) {
            if (strcmp(parcours->nom_ville,ville)==0) {
                parcours->nombre_vaccins_total += nb_vaccins;
                parcours->semaines_planifiees = ajouterVaccinS(parcours->semaines_planifiees, semaine, nb_vaccins);
                return liste;
            }
            parcours = parcours->suivant;
        }
        printf("la ville n'existe pas\n");

        parcours = liste;
        if (parcours == NULL) printf("ça beug gros\n");

        while (parcours->suivant!=NULL && parcours->suivant->nombre_vaccins_total<=nb_vaccins) {
                    parcours = parcours->suivant;
            }

            t_ville_elt* nouvelleVille = creerVille(ville);
            nouvelleVille->nombre_vaccins_total += nb_vaccins;
            nouvelleVille->semaines_planifiees = ajouterVaccinS(nouvelleVille->semaines_planifiees,semaine,nb_vaccins);

        if (parcours->nombre_vaccins_total<=nb_vaccins){
            nouvelleVille->suivant = parcours->suivant;
            parcours->suivant = nouvelleVille;
            return liste;
        } else{
            nouvelleVille->suivant=parcours;
            return nouvelleVille;
        }
    }
}


void afficherStock(t_vaccin_elt *vaccin){

    int i = 0;
    t_vaccin_elt * copietab=tab;

    while (i<taille && vaccin!=copietab) {
        copietab ++;
        i++;
    }

    if (i==taille) printf("le vaccin n'existe pas ");
    else{
        printf("%s : \n", copietab->marque);
        t_ville_elt * vil = copietab->villes_dispo;
        while(vil!=NULL){

            printf(" --- %s [Total = %d]\n", vil->nom_ville, vil->nombre_vaccins_total);

            t_semaine_elt *sem = vil->semaines_planifiees;

            while(sem !=NULL){
                printf("    --- semaine %d : %d\n", sem->numero_semaine, sem->nombre_vaccins);
                sem=sem->suivant;
            }

            vil=vil->suivant;
        }
    }
};


void afficherPlanification(t_vaccin_elt *vaccin, int semaine){
    int i = 0;
    t_vaccin_elt * copietab=tab;

    while (i<taille && vaccin!=copietab) {
        copietab ++;
        i++;
    }

    if (i==taille) printf("le vaccin n'existe pas ");
    else{
        printf("%s : \n", copietab->marque);
        printf(" --- semaine %d :\n", semaine);
        t_ville_elt * vil = copietab->villes_dispo;


        while(vil!=NULL){

            t_semaine_elt * sem = vil->semaines_planifiees;

            while(sem !=NULL && sem->numero_semaine!=semaine){
                sem=sem->suivant;
            }

            printf("    --- %s : %d\n", vil->nom_ville, sem->nombre_vaccins);

            vil=vil->suivant;
        }
    }
};


