//
// Created by Anne LAHNECHE on 12/04/2021.
//

#include "fonction.h"

pile * creer_pile(){
    pile * p = malloc(sizeof(pile));
    p->tab=malloc(sizeof(int)*50);
    p->sommet=0;
    return p;
};
bool pile_vide(pile * p){
    return p->sommet==0;
};
void empiler(pile * p, cellule c){
    p->tab[p->sommet]=c;
    p->sommet++;
};
void depiler(pile * p, cellule * val){
    if (!pile_vide(p)){
        *val=p->tab[p->sommet-1];
        p->sommet--;
    }else{
        printf("la pile est vide\n");
    }
};

file * creer_file(int taille){
    file * f = malloc(sizeof(pile));
    f->tab=malloc(sizeof(int)*taille);
    f->tete=0;
    f->queue=0;
    return f;
};
bool file_pleine(file * f){
    return (f->tete)==(f->queue+1)%(f->longueur);
};

bool file_vide(file * f){
    return (f->tete)==(f->queue)%(f->longueur);
};


void enfiler(file * f, cellule *c){
    if (!file_pleine(f)){
        f->tab[f->tete]=c;
        f->tete++;
    }else{
        printf("file pleine\n");
    }
};
int defiler(file * f, struct cellule* val){
    if (!file_vide(f)){
        *val = f->tab[f->tete];
        f->tete=(f->tete+1)%f->longueur;
        return 1;
    }else{
        printf("la file est vide \n");
        return 0;
    }
};

cellule * creer_cellule(cellule * pere){
    cellule *c = malloc(sizeof(cellule));
    c->pere=pere;
    c->fils=NULL;
    c->frere=NULL;
    return c;
}

void parcoursarbrekaire(file *f){
    cellule * val=creer_cellule(NULL);
        while(!file_vide(f)){
            defiler(f, val);
            afficher(val);
            cellule * parcours = val->fils;
            while (parcours!=NULL){
                enfiler(f, parcours);
                parcours=parcours->frere;
            }
        }
}