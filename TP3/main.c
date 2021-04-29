#include <stdio.h>
#include "fonction.h"

int main() {
    int i=0;

    char *ville = malloc(sizeof(char) * 50);
    char *vac = malloc(sizeof(char) * 50);
    int sem;
    int nb_v;
    int j;

    // tests fusionner stocks
    t_vaccin_elt* mod = creerVaccin("moderna");
    t_vaccin_elt* chup = creerVaccin("chupachups");
    mod->villes_dispo = ajouterVaccinV(mod->villes_dispo,"Crespieres",3,50);
    mod->villes_dispo = ajouterVaccinV(mod->villes_dispo,"Crespieres",10,35);
    mod->villes_dispo = ajouterVaccinV(mod->villes_dispo,"Vannes", 5,70);
    mod->villes_dispo = ajouterVaccinV(mod->villes_dispo,"Marseille", 5,90);
    chup->villes_dispo = ajouterVaccinV(chup->villes_dispo, "Vannes", 5, 10);
    chup->villes_dispo = ajouterVaccinV(chup->villes_dispo, "Vannes", 2, 10);
    chup->villes_dispo = ajouterVaccinV(chup->villes_dispo, "Paris", 3, 30);
    //mod->villes_dispo = deduireVaccinV(mod->villes_dispo, "Marseille", 5, 1);
    //mod->villes_dispo->suivant->semaines_planifiees = deduireVaccinS(mod->villes_dispo->suivant->semaines_planifiees, 3, 60);
    mod->villes_dispo = deduireVaccinV(mod->villes_dispo, "Vannes", 5, 80);

    taille = 2;
    tab=malloc(sizeof(t_vaccin_elt*)*2);
    tab[0]=mod;
    tab[1]=chup;

    while (i!=7) {

        printf("1. Initialiser la liste des marques de vaccin disponibles\n");
        printf("2. Ajouter un nombre de vaccins dans le stock d\x27une marque\n");
        printf("3. Retirer un nombre de vaccins du stock\n");
        printf("4. Afficher le stock d\x27un vaccin\n");
        printf("5. Afficher la planification pour une semaine\n");
        printf("6. Fusionner les stocks de deux marques de vaccins\n");
        printf("7. Quitter\n");
        printf("donnez votre choix\n");

        fflush(stdin);
        scanf("%d", &i);

        switch (i) {
            case 1 :
                printf("combien de vaccin voulez vous rentrer ?\n");
                fflush(stdin);
                scanf("%d", &nb_v);
                taille = nb_v;
                tab = malloc(sizeof(t_vaccin_elt *) * nb_v);
                for (int it = 0; it < nb_v; it++) {
                    printf("quel est le nom du vaccin %d\n", it);
                    fflush(stdin);
                    scanf("%s", vac);
                    tab[it] = creerVaccin(vac);
                }
                break;

            case 2:
                printf("De quel vaccin voulez-vous incrémenter le stock\n");
                fflush(stdin);
                scanf("%s", vac);
                for (j = 0; j < taille; j++) {
                    if (strcmp(vac, tab[j]->marque) == 0) {
                        printf("Dans quelle ville voulez-vous ajouter les vaccins\n");
                        fflush(stdin);
                        scanf("%s", ville);
                        printf("Dans quelle semaine voulez-vous ajouter les vaccins\n");
                        fflush(stdin);
                        scanf("%d", &sem);
                        printf("Combien de vaccin voulez-vous ajouter\n");
                        fflush(stdin);
                        scanf("%d", &nb_v);
                        tab[j]->villes_dispo = ajouterVaccinV(tab[j]->villes_dispo, ville, sem, nb_v);
                        break;
                    }
                }
                if (j == taille) printf("le vaccin n\x27 existe pas\n");
                else printf("le changement de stock a bien \x94t\x94 effectu\x94\n");
                break;

            case 3:
                printf("De quel vaccin voulez-vous incrémenter le stock\n");
                fflush(stdin);
                scanf("%s", vac);
                for (j = 0; j < taille; j++) {
                    if (strcmp(vac, tab[j]->marque) == 0) {
                        printf("Dans quelle ville voulez-vous ajouter les vaccins\n");
                        fflush(stdin);
                        scanf("%s", ville);
                        printf("Dans quelle semaine voulez-vous ajouter les vaccins\n");
                        fflush(stdin);
                        scanf("%d", &sem);
                        printf("Combien de vaccin voulez-vous ajouter\n");
                        fflush(stdin);
                        scanf("%d", &nb_v);
                        tab[j]->villes_dispo = deduireVaccinV(tab[j]->villes_dispo, ville, sem, nb_v);
                        break;
                    }
                }
                if (j == taille) printf("le vaccin n\x27 existe pas\n");
                else printf("le changement de stock a bien \x94t\x94 effectu\x94\n");
                break;

            case 4:
                printf("De quel vaccin voulez-vous afficher le stock\n");
                fflush(stdin);
                scanf("%s", vac);
                for (j=0; j<taille; j++){
                    if (strcmp(vac, tab[j]->marque) == 0) {
                        afficherStock(tab[j]);
                        break;
                    }
                }
                if(j==taille) printf("le vaccin n\x27 existe pas\n");
                break;

            case 5:
                printf("De quel vaccin voulez-vous afficher la planification\n");
                fflush(stdin);
                scanf("%s", vac);
                printf("De quel numero de semaine voulez-vous afficher la planification\n");
                fflush(stdin);
                scanf("%i", &sem);
                for (j=0; j<taille; j++){
                    if (strcmp(vac, tab[j]->marque) == 0) {
                        afficherPlanification(tab[j], sem);
                        break;
                    }
                }
                if(j==taille) printf("le vaccin n\x27 existe pas\n");
                break;

            case 6:
                printf("Vous avez demand\x94t a fusionner deux vaccins.\n");
                char* nomV1 = malloc(sizeof(char)*50);
                t_vaccin_elt* V1;
                char* nomV2 = malloc(sizeof(char)*50);
                t_vaccin_elt* V2;

                printf("Veuillez entrer le nom du premier vaccin :");
                fflush(stdin);
                scanf("%s",nomV1);
                for (j = 0; j < taille; j++) {
                    if (strcmp(nomV1, tab[j]->marque) == 0) {
                        V1 = tab[j];
                    }
                }
                printf("\nVeuillez entrer le nom du deuxieme vaccin :");
                fflush(stdin);
                scanf("%s",nomV2);
                for (j = 0; j < taille; j++) {
                    if (strcmp(nomV2, tab[j]->marque) == 0) {
                        V2 = tab[j];
                    }
                }
                t_vaccin_elt *VT = fusionnerStocks(V1,V2);
                t_vaccin_elt ** newtab = malloc(sizeof(t_vaccin_elt*) * (taille+1));
                for(j=0; j<taille; j++) newtab[j]=tab[j];
                t_vaccin_elt ** oldtab=tab;
                tab=newtab;
                free(oldtab);
                tab[taille++]=VT;
        }
        }



    return 0;
}
