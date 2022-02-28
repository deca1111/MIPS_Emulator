#ifndef __MEMOIRE_H__
#define __MEMOIRE_H__

#define TAILLE_MAX_PROG 100
#define TAILLE_MEM 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registres.h"
#include "fonctions_outils.h"
#include "traduction.h"


typedef struct {
    unsigned int adresse;
    long int donnees;
}case_memory;//structure contenant le couple adresse/donnees


extern int stock_prog_bin[TAILLE_MAX_PROG][32];//stockage du programme traduit (100 lignes max)

extern char stock_prog_string[TAILLE_MAX_PROG][LONGUEUR_LIGNE];//stockage du programme en string (100 lignes max)

extern char stock_prog_hexa[TAILLE_MAX_PROG][8];//stockage du programme en hexa


void init_mem();//initialise la memoire

void ecrire_mem(unsigned int adresse_dest, long int data);//permet d'ecrire dans la memoire a une adresse donnee, une donnee stockee sur 32 bits a une adresse donnee

void charge_mem(unsigned int adresse_src, int reg[32]);//permet de dans un registre une donnee stockee sur 32 bits a une adresse donnee en memoire

void affiche_mem();//affiche la memoire (seuelement les adresse non vide)

//ATTENTION Cette fonction incremente le PC
void recopie_ligne_prog(int ligne[32],char motsSepares[4][20],char hexa_l[8]);//recopie la ligne en cours de traduction dans les tableaux contenant le programme sous differente forme

void affiche_prog();//affiche le programme en hexa puis en toutes lettre ( affiche aussi le numero de ligne)

#endif
