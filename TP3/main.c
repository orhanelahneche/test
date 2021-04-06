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

    t_semaine_elt *l = deduireVaccinS(s, 5, 3);

    if (l){
        printf("%d", l->suivant->suivant->nombre_vaccins);
    }


    return 0;
}
