//
// Created by Anne LAHNECHE on 22/03/2021.
//

#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>

polynome constructeur(int c, int d, polynome P){

    polynome m = malloc(sizeof(monome));

    (*m).coef=c;
    (*m).deg=d;
    (*m).p=P;


    return m;
}

int degre (polynome P){
    int deg=0;

    while (P!=NULL){
        if (P->deg>deg){
            deg=P->deg;
        }
        return deg;
    }
}
