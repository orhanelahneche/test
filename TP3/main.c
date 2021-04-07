#include <stdio.h>
#include "fonction.h"

int main() {
    t_semaine_elt *s;
    s=creerSemaine(3,5);

    t_semaine_elt *s2;

    t_semaine_elt *s3;

    s2 = creerSemaine(4, 6);

    s3 = creerSemaine(5, 7);

    s->suivant=s2;

    s2->suivant=s3;

    tab = malloc(sizeof(t_vaccin_elt*)*5);

    taille = 1;

    t_vaccin_elt *v = creerVaccin("moderna");

    t_ville_elt *vil=creerVille("Noyon");

    v->villes_dispo = vil;

    t_semaine_elt * sb=creerSemaine(3,5);

    t_semaine_elt * s2b = creerSemaine(4, 6);

    t_semaine_elt * s3b = creerSemaine(5, 7);

    sb->suivant=s2b;

    s2b->suivant=s3b;

    vil->semaines_planifiees = s;

    tab=v;

    t_ville_elt *vil2=creerVille("compiegne");

    vil->suivant=vil2;

    vil2->semaines_planifiees = sb;

    vil->semaines_planifiees = ajouterVaccinS(vil->semaines_planifiees, 2, 3);

    vil->semaines_planifiees = ajouterVaccinS(vil->semaines_planifiees, 1, 3);

    vil->semaines_planifiees = ajouterVaccinS(vil->semaines_planifiees, 4, 3);

    vil->nombre_vaccins_total=27;

    vil2->nombre_vaccins_total=18;

    //printf("%d", vil->semaines_planifiees->suivant->numero_semaine);

    afficherStock(v);

    afficherPlanification(v, 4);

    /*t_semaine_elt *l = deduireVaccinS(s, 5, 3);

    if (l){
        printf("%d", l->suivant->suivant->nombre_vaccins);
    }*/



    return 0;
}
