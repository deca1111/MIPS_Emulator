#ifndef __TRADUCTION_H__
#define __TRADUCTION_H__

#define LONGUEUR_LIGNE 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TESTDIR "dossier_tests/"

#define EXITDIR "sorties_hex/"

typedef struct {
    char string_l[LONGUEUR_LIGNE];
    char motsSepares[4][20];
    char type_l;
    int binaire_l[32];
    char hexa_l[8];
    int nb_mots;
	int erreur;
}ligne;//structure contenant tous les elements utiles a la traduction

typedef struct {
	int opcode[6];
	int rs[5];
	int rt[5];
	int immediate[16];
} patternI;//structure immitant la forme d'une instruction de type I

typedef struct {
	int opcode[6];
	int target[26];
} patternJ;//structure immitant la forme d'une instruction de type J

typedef struct {
	int opcode[6];
	int rs[5];
	int rt[5];
	int rd[5];
	int sa[5];
	int function[6];
} patternR;//structure immitant la forme d'une instruction de type R



void remplirPatternI(ligne *ligne_fct,int afficher);//remplit une structure qui copie le pattern d'une instruction de type I element par element puis concatene et converti en hexa (modifie .binaire et .hexa de la ligne en parametre)

void remplirPatternJ(ligne *ligne_fct,int afficher);//remplit une structure qui copie le pattern d'une instruction de type J element par element puis concatene et converti en hexa (modifie .binaire et .hexa de la ligne en parametre)

void remplirPatternR(ligne *ligne_fct,int afficher);//remplit une structure qui copie le pattern d'une instruction de type R element par element puis concatene et converti en hexa (modifie .binaire et .hexa de la ligne en parametre)

void tradRegistre(char nomResitre[], int registreBin[]);//prend un nom de registre mnemonique ou decimal et modifie le vecteur binaire en parametre avec le numero du registre (5 bits)

void afficherTableReg();//affiche la table de correspondance des registres (affiche simplement)

void traduire_pas_inter(char nomFichierIn[], char nomFichierOut[],int afficher);//fonction de traduction de assembleur a hexa

void traduire_inter();//demande a l'utilisateur de rentrer une ligne de commande et la traduit de la meme maniere que dans traduire_pas_inter

void chercherType(ligne *ligneTemp);//cherche le type de l'instruction décrite dasn la ligne (modifie directement la ligne)

void decomposerMots(ligne *ligne_fct);//decompose en plusieurs mots la ligne (modifie directement la ligne)

void ecritureLigne(FILE* fichier,char ligne[]);//ecrit la ligne en hexa dans le document de sortie

#endif
