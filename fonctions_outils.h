#ifndef __FONCTIONS_OUTILS__
#define __FONCTIONS_OUTILS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void decimal2bin(int taille, int bin[], long int dec);//convertie un nombre decimal en un vecteur binaire

int string2decimal(char* nombre);//convertit une chaine de caractÃ¨re en nombre decimal

void binaire2Hex(int bin[],char hex[]);//convertit un vecteur binaire en un vecteur hexadecimal (modifie les tableaux en parametre)

long int bin2Decimal(int taille, int bin[],int compl2);//convertit un vecteur binaire en decimal

void decoupeur_binaire(int debut, int fin, int source[], int dest[fin-debut+1]);//debut et fin selon index tableau, pas selon numero de bit usuels

void viderBuffer(void);//permet de vider le buffer après utilisation de scanf

#endif
