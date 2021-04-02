#include <stdio.h>
#include "fonction.h"

int main() {
    t_semaine_elt *s;
    s=creerSemaine(4,5);

    t_semaine_elt *s2;

    s2 = ajouterVaccinS(s, 4, 8);

    printf("%d", s2->nombre_vaccins);

    return 0;
}
