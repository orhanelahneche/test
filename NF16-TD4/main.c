#include <stdio.h>
#include "fonction.h"
#include <stdlib.h>

int main() {
    printf("Hello, World!\n");

    polynome pol=malloc(sizeof(struct monome));

    monome * m;

    m->coef=4;
    m->deg=3;
    m->p=NULL;

    pol = m;

    pol = constructeur (5,8, pol);

    printf("%d", pol->p->deg);

    return 0;
}
