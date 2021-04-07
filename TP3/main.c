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

    vil->semaines_planifiees = s;

    tab=v;

    t_ville_elt *vil2=creerVille("compiegne");

    vil->suivant=vil2;

    vil2->semaines_planifiees = s;

    afficherStock(v);

    afficherPlanification(v, 4);

    /*t_semaine_elt *l = deduireVaccinS(s, 5, 3);

    if (l){
        printf("%d", l->suivant->suivant->nombre_vaccins);
    }*/



    return 0;
}
