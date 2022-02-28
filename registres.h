#ifndef __REGISTRES_H__
#define __REGISTRES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

#define REGDIR "sorties_registres/"

extern int registres[32][32];//tableau contenant les registres usuels (de $0 a $31)

extern int PC;//registre PC

extern long int HI,LO;//registres LI et HO

void affiche_reg();//affiche les registres avec leurs 2 nom (mnemo et decimal)

void init_reg();//initialise les registres a 0

void ecritureRegistre(char nomFichierOut[]);//ecrit des registres dans un fichier


#endif
