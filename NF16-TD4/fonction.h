//
// Created by Anne LAHNECHE on 22/03/2021.
//

#ifndef UNTITLED_FONCTION_H
#define UNTITLED_FONCTION_H
typedef struct monome{
    int coef;
    int deg;
    struct monome * p;
} monome;

typedef struct monome * polynome;

polynome constructeur(int c, int d, polynome P);
#endif //UNTITLED_FONCTION_H
