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
    return v;
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


/*t_semaine_elt *deduireVaccinS(t_semaine_elt *liste, int semaine, int nb_vaccins){
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
            if (current->nombre_vaccins <= nb_vaccins) {
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
            if (current->suivant->nombre_vaccins <= nb_vaccins) { //cas simple mais avec suppression de la semaine
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
}*/

t_semaine_elt *deduireVaccinS(t_semaine_elt *liste, int semaine, int nb_vaccins){
    int rep = -1;
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

            if (current->nombre_vaccins <= nb_vaccins) {
                while (rep!=1 && rep!=0)
                {
                    printf("Vous voulez supprimer tous les vaccins de cette ville, continuer et supprimer la ville ?\n(1 : oui/ 0 : non) Votre choix : ");
                    fflush(stdin);
                    scanf("%d", &rep);
                }
                if (rep==1) {
                    if (current->suivant==NULL){ //cas de la liste unique
                        free(liste);
                        return 0;
                    }else{ //cas du premier élément
                        t_semaine_elt * s = liste->suivant;
                        free(liste);
                        return s;
                    }
                }
                else {
                    printf("Op%cration annul%ce.\n",130,130);
                    return liste;
                }
            } else {
                current->nombre_vaccins -= nb_vaccins;
                return current;
            }
        }else if(current->suivant==NULL){ //on a parcouru toute la liste et la semaine n'existe pas
            printf("la semaine n'existe pas\n");
            return 0;
        }else{ //cas le plus simple
            if (current->suivant->nombre_vaccins <= nb_vaccins) { //cas simple mais avec suppression de la semaine
                while (rep!=1 && rep!=0)
                {
                    printf("Vous voulez supprimer plus de vaccins qu'il y en a pour cette ville, continuer et supprimer la ville ?\n(1 : oui/ 0 : non) Votre choix : ");
                    fflush(stdin);
                    scanf("%d", &rep);
                }
                if (rep==1) {
                    t_semaine_elt *sup = current->suivant;
                    current->suivant = current->suivant->suivant; //suppression dans la liste chaîné
                    free(sup);
                    return liste;
                }
                else {
                    printf("Op%cration annul%ce.\n",130,130);
                    return liste;
                }
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
        if (strcmp(parcours->nom_ville,ville)==0){ //ici on traite le cas du premier élément de la même manière que précedement
            parcours->nombre_vaccins_total += nb_vaccins;
            parcours->semaines_planifiees = ajouterVaccinS(parcours->semaines_planifiees, semaine, nb_vaccins);
            t_ville_elt* pointeur_semaine=parcours; //permettra de garder un pointeur sur l'élément de la ville
            if (parcours->suivant!=NULL && parcours->nombre_vaccins_total > parcours->suivant->nombre_vaccins_total){ //ici on réorganise déplace l'élément si celui-ci doit changer de place (cas où le nb totale de vaccin et plus grand que le nb du suivant)
                liste=parcours->suivant;
                //on parcours la liste et on place l'élément à la bonne position
                while(parcours->suivant!=NULL && pointeur_semaine->nombre_vaccins_total > parcours->suivant->nombre_vaccins_total) parcours = parcours->suivant;
                pointeur_semaine->suivant=parcours->suivant;
                parcours->suivant = pointeur_semaine;
            }
            return liste;
        }else{
            while (parcours->suivant!=NULL) { //on parcours la liste
                if (strcmp(parcours->suivant->nom_ville,ville)==0) { //on rentre dans la boucle quand on tombe sur le bon vaccin
                    parcours->suivant->nombre_vaccins_total += nb_vaccins;
                    parcours->suivant->semaines_planifiees = ajouterVaccinS(parcours->suivant->semaines_planifiees, semaine, nb_vaccins);
                    t_ville_elt* pointeur_semaine=parcours->suivant; //permettra de garder un pointeur sur l'élément de la ville
                    if (pointeur_semaine->nombre_vaccins_total > pointeur_semaine->suivant->nombre_vaccins_total){ //ici on réorganise déplace l'élément si celui-ci doit changer de place (cas où le nb totale de vaccin et plus grand que le nb du suivant)
                        parcours->suivant=pointeur_semaine->suivant;
                        parcours = pointeur_semaine;
                        //on parcours la liste et on place l'élément à la bonne position
                        while(parcours->suivant!=NULL && pointeur_semaine->nombre_vaccins_total > parcours->suivant->nombre_vaccins_total) parcours = parcours->suivant;
                        pointeur_semaine->suivant=parcours->suivant;
                        parcours->suivant = pointeur_semaine;
                    }
                    return liste;
                }
                parcours = parcours->suivant;
            }
        }

        printf("la ville n'existe pas\n");

        parcours = liste;

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

/*t_ville_elt *ajouterVaccinV(t_ville_elt *liste, char* ville, int semaine, int nb_vaccins){
    t_ville_elt* parcours;

    if (liste==NULL) {
        //printf("la liste est nulle, je cree la nouvelle ville %s\n", ville);
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
        //printf("la liste n'est pas nulle mais la ville recherchee n'y est pas\n\n");

        // il faut créer une nouvelle ville et l'insérer...
        parcours = liste;
        //if (parcours == NULL) printf("ça beug gros\n");

        // on regarde s'il faut l'insérer en tête de liste
        if (parcours->nombre_vaccins_total > nb_vaccins){
            //printf("je vais l'ajouter en tete de liste :\n\n");
            t_ville_elt* nouvelleVille = creerVille(ville);
            nouvelleVille->nombre_vaccins_total += nb_vaccins;
            nouvelleVille->semaines_planifiees = ajouterVaccinS(nouvelleVille->semaines_planifiees,semaine,nb_vaccins);
            nouvelleVille->suivant = parcours;
            liste = nouvelleVille;
            return liste;
        }

        // sinon on parcourt la liste jusqu'à trouver sa position (en fin de liste ou avant la ville avec un nombre de vaccins directement supérieur
        while (parcours->suivant!=NULL && parcours->suivant->nombre_vaccins_total<=nb_vaccins) {
            parcours = parcours->suivant;
            //printf("on va tester la suivante\n");
        }

        // à la fin du while, parcours->suivant pointe sur null (fin de liste) ou parcours->suivant->nombre_vaccins_total > nb_vaccins (milieu de liste)
        if (parcours->suivant == NULL) { // on crée la ville en fin de liste
            //printf("je l'ajoute en fin de liste\n");

            t_ville_elt* nouvelleVille = creerVille(ville);
            nouvelleVille->nombre_vaccins_total += nb_vaccins;
            nouvelleVille->semaines_planifiees = ajouterVaccinS(nouvelleVille->semaines_planifiees,semaine,nb_vaccins);
            parcours->suivant = nouvelleVille;

            return liste;
        }

        else { // on l'insère entre parcours et son suivant
            t_ville_elt* nouvelleVille = creerVille(ville);
            nouvelleVille->nombre_vaccins_total += nb_vaccins;
            nouvelleVille->semaines_planifiees = ajouterVaccinS(nouvelleVille->semaines_planifiees,semaine,nb_vaccins);
            nouvelleVille->suivant = parcours->suivant;
            parcours->suivant = nouvelleVille;
            return liste;
        }
    }
}*/

/***************** Déduire vaccins de ville ******************/

t_ville_elt *deduireVaccinV(t_ville_elt *liste, char* ville, int semaine, int nb_vaccins){
    t_ville_elt* parcours = liste;
    t_semaine_elt * parcours_s;
    unsigned int Nbtest=0;
    unsigned int modif;
    while (parcours!=NULL && strcmp(parcours->nom_ville, ville)!=0) parcours = parcours->suivant;
    if (parcours !=NULL) {
        parcours_s = parcours->semaines_planifiees;
        while (parcours_s != NULL && parcours_s->numero_semaine != semaine) parcours_s = parcours_s->suivant;
        if (parcours_s != NULL) Nbtest = parcours_s->nombre_vaccins;
        else return liste;
    }else{
        return liste;
    }

    if (liste==NULL) {
        return liste;
    }
    else {
        parcours = liste;
        if (strcmp(parcours->nom_ville,ville)==0){ //ici on traite le cas du premier élément de la même manière que précedement
            parcours->semaines_planifiees = deduireVaccinS(parcours->semaines_planifiees, semaine, nb_vaccins);
            parcours_s = parcours->semaines_planifiees;
            while (parcours_s != NULL && parcours_s->numero_semaine != semaine) parcours_s = parcours_s->suivant;
            if (parcours_s != NULL) {
                modif = parcours_s->nombre_vaccins;
                if (modif==Nbtest) return liste;
                else{
                    if (parcours->nombre_vaccins_total<=nb_vaccins){
                        t_ville_elt* buf = parcours->suivant;
                        free(parcours);
                        return buf;
                    }else {
                        parcours->nombre_vaccins_total -= nb_vaccins;
                        return liste;
                    }
                }
            }
            else {
                if (parcours->nombre_vaccins_total<=Nbtest){
                t_ville_elt* buf = parcours->suivant;
                free(parcours);
                return buf;
                }else {
                    parcours->nombre_vaccins_total -= Nbtest;
                    return liste;
                }
            }
        }else{
            while (parcours->suivant!=NULL) { //on parcours la liste
                if (strcmp(parcours->suivant->nom_ville,ville)==0) { //on rentre dans la boucle quand on tombe sur le bon vaccin
                    parcours->suivant->semaines_planifiees = deduireVaccinS(parcours->suivant->semaines_planifiees, semaine, nb_vaccins);
                    parcours_s = parcours->suivant->semaines_planifiees;
                    while (parcours_s != NULL && parcours_s->numero_semaine != semaine) parcours_s = parcours_s->suivant;
                    if (parcours_s != NULL) {
                        modif = parcours_s->nombre_vaccins;
                        if (modif==Nbtest) return liste;
                        else{
                            if (parcours->suivant->nombre_vaccins_total<=nb_vaccins){
                                t_ville_elt* buf = parcours->suivant;
                                parcours->suivant=parcours->suivant->suivant;
                                free(buf);
                                return liste;
                            }else {
                                parcours->nombre_vaccins_total -= nb_vaccins;
                                return liste;
                            }
                        }
                    }
                    else {
                        if (parcours->nombre_vaccins_total<=Nbtest){
                            t_ville_elt* buf = parcours->suivant;
                            free(parcours);
                            return buf;
                        }else {
                            parcours->nombre_vaccins_total -= Nbtest;
                            return liste;
                        }
                    }
                    if (parcours->nombre_vaccins_total<=nb_vaccins){
                        t_ville_elt* buf = parcours->suivant;
                        parcours->suivant=parcours->suivant->suivant;
                        free(buf);
                        return liste;
                    }else{
                        parcours->suivant->nombre_vaccins_total -= nb_vaccins;
                        parcours->suivant->semaines_planifiees = deduireVaccinS(parcours->suivant->semaines_planifiees, semaine, nb_vaccins);
                        t_ville_elt * parcours1 = parcours->suivant;
                        parcours->suivant=parcours1->suivant;
                        if (liste->nombre_vaccins_total>parcours1->nombre_vaccins_total) {
                            parcours1->suivant = liste;
                            return parcours1;
                        }
                        parcours = liste;
                        while (parcours->suivant!=NULL && parcours->suivant->nombre_vaccins_total<parcours1->nombre_vaccins_total) parcours=parcours->suivant;
                        parcours1->suivant=parcours->suivant;
                        parcours->suivant=parcours1;
                        return liste;
                    }
                }
                parcours = parcours->suivant;
            }
        }

        printf("la ville n'existe pas\n");
        return 0;
    }
}



void afficherStock(t_vaccin_elt *vaccin){

    if (vaccin ==NULL) {
        printf("le vaccin n'existe pas ");
        return;
    }
    else{
        printf("%s : \n", vaccin->marque);
        t_ville_elt * vil = vaccin->villes_dispo;
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


    if (vaccin==NULL) {
        printf("le vaccin n'existe pas ");
        return ;
    }
    else{
        printf("%s : \n", vaccin->marque);
        printf(" --- semaine %d :\n", semaine);
        t_ville_elt * vil = vaccin->villes_dispo;


        while(vil!=NULL){

            t_semaine_elt * sem = vil->semaines_planifiees;

            while(sem !=NULL && sem->numero_semaine!=semaine){
                sem=sem->suivant;
            }

            if (sem!=NULL) printf("    --- %s : %d\n", vil->nom_ville, sem->nombre_vaccins);

            vil=vil->suivant;
        }
    }
};

t_vaccin_elt *fusionnerStocks(t_vaccin_elt *vaccinA, t_vaccin_elt *vaccinB){

    size_t fullsize;
    char* fullname;
    t_ville_elt* parcoursVille;
    t_semaine_elt* parcoursSemaine;

    // on concatène les deux noms
    fullsize = strlen(vaccinA->marque) + 1 + strlen(vaccinB->marque) + 1;
    fullname = malloc(fullsize*sizeof(char));
    strcpy(fullname, vaccinA->marque);
    strcat(fullname,"_");
    strcat(fullname,vaccinB->marque);

    // on crée le nouveau vaccin fusion qui porte ce nouveau nom
    t_vaccin_elt* fusion = creerVaccin(fullname);

    // on ajoute d'abord toutes le villes du vaccinA à fusion
    parcoursVille = vaccinA->villes_dispo;
    while (parcoursVille!=NULL)
    {
        // on parcourt l'ensemble des villes pour chaque semaine
        parcoursSemaine = parcoursVille->semaines_planifiees;
        while (parcoursSemaine!=NULL)
        {
            fusion->villes_dispo = ajouterVaccinV(fusion->villes_dispo, parcoursVille->nom_ville, parcoursSemaine->numero_semaine, parcoursSemaine->nombre_vaccins);
            parcoursSemaine = parcoursSemaine->suivant;
        }
        parcoursVille = parcoursVille->suivant;
    }
    afficherStock(fusion);

    // puis on parcours vaccinB pour compléter
    parcoursVille = vaccinB->villes_dispo;

    while (parcoursVille!=NULL)
    {
        // on parcourt l'ensemble des villes pour chaque semaine
        parcoursSemaine = parcoursVille->semaines_planifiees;
        while (parcoursSemaine!=NULL)
        {
            fusion->villes_dispo = ajouterVaccinV(fusion->villes_dispo, parcoursVille->nom_ville, parcoursSemaine->numero_semaine, parcoursSemaine->nombre_vaccins);
            parcoursSemaine = parcoursSemaine->suivant;
        }
        parcoursVille = parcoursVille->suivant;
    }

    // finalement, on retourne le pointeur sur le nouveau vaccin
    return fusion;
}


