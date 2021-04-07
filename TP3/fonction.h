//
// Created by Anne LAHNECHE on 02/04/2021.
//

#ifndef TP3_FONCTION_H
#define TP3_FONCTION_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



typedef struct semaine_elt {
    unsigned int numero_semaine ;
    unsigned int nombre_vaccins ;
    struct semaine_elt* suivant;
} t_semaine_elt;

typedef struct ville_elt{
    char* nom_ville;
    unsigned int nombre_vaccins_total;
    t_semaine_elt * semaines_planifiees;
    struct ville_elt* suivant;
}t_ville_elt;

typedef struct vaccin_elt {
    char* marque;
    t_ville_elt * villes_dispo;
}t_vaccin_elt;

t_semaine_elt *creerSemaine(int num_semaine, int nb_vaccins);

t_ville_elt *creerVille(char *ville);

t_vaccin_elt *creerVaccin(char *marque);

t_semaine_elt *ajouterVaccinS(t_semaine_elt *liste, int semaine, int nb_vaccins);

t_semaine_elt *deduireVaccinS(t_semaine_elt *liste, int semaine, int nb_vaccins);

viderbuffer();

void afficherStock(t_vaccin_elt *vaccin);

void afficherPlanification(t_vaccin_elt *vaccin, int semaine);

t_vaccin_elt * tab ;
int taille;
#endif //TP3_FONCTION_H
