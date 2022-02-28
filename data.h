#ifndef __DATA_H__
#define __DATA_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	char mnemo[10];
	char reg[10];
} nom_registre;//structure permettant de faire correspondre les differents noms des registres


typedef struct {
	char nom[10];
	char type;
} type_fct;//structure associant une fonction à son type

typedef struct {
	char nom[10];
	int opcode[6];
	int place_rs;
	int place_rt;
	int place_immediate;
	int nb_mot_voulu;
} patternFctI;//structure renseignant l'opcode et les emplacements des differents operandes de la fonction

typedef struct {
	char nom[10];
	int opcode[6];
} patternFctJ;

typedef struct {
	char nom[10];
	int opcode[6];
	int function[6];
	int place_rs;
	int place_rt;
	int place_rd;
	int place_sa;
	int nb_mot_voulu;
} patternFctR;

//table contenant les noms des registres (mnemo et decimaux) en les faisant correspondre à leurs index dans la table
extern const nom_registre table_corres_reg[33];

//table contenant les noms des fonctions en les faisant correspondre à leur type
extern const type_fct table_type_fct[28];

//table contenant les noms fonctions de type I en les faisant correspondre à leur opcode et la place de leurs operandes
extern const patternFctI table_pattern_fct_I[10];

//table contenant les noms fonctions de type J en les faisant correspondre à leur opcode
extern const patternFctJ table_pattern_fct_J[3];

//table contenant les noms fonctions de type R en les faisant correspondre à leur opcode et la place de leurs operandes
extern const patternFctR table_pattern_fct_R[17];

#endif
