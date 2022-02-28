#ifndef __EXECUTION_H__
#define __EXECUTION_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executer(int pasAPas,int intercatif);//fonction principale de ce module, elle parcourt le tableau ou est stocke le programme 
//et execute chaque ligne
//les parametres pasAPas et interactif servent a determiner le mode et les options choisis par l'utilisateur




//fonctions executant les instructions correspondantes et modifiant le PC en consequences
void instruction_ADD(int rd[5], int rs[5], int rt[5]);

void instruction_ADDI(int rt[5], int rs[5], int immediate[16]);

void instruction_AND(int rd[5], int rs[5], int rt[5]);

void instruction_BEQ(int rs[5], int rt[5], int immediate[16]);

void instruction_BGTZ(int rs[5], int immediate[16]);

void instruction_BLEZ(int rs[5], int immediate[16]);

void instruction_BNE(int rs[5], int rt[5], int immediate[16]);

void instruction_DIV(int rs[5], int rt[5]);

void instruction_J(int target[26]);

void instruction_JAL(int target[26]);

void instruction_JR(int rs[5]);

void instruction_LUI(int rt[5], int immediate[16]);

void instruction_LW(int rt[5], int immediate[16], int rs[5]);

void instruction_MFHI(int rd[5]);

void instruction_MFLO(int rd[5]);

void instruction_MULT(int rs[5], int rt[5]);

void instruction_OR(int rd[5], int rs[5], int rt[5]);

void instruction_ROTR(int rd[5], int rt[5], int sa[5]);

void instruction_SLL(int rd[5], int rt[5], int sa[5]);

void instruction_SLT(int rd[5], int rs[5], int rt[5]);

void instruction_SRL(int rd[5], int rt[5], int sa[5]);

void instruction_SUB(int rd[5], int rs[5], int rt[5]);

void instruction_SW(int rt[5], int immediate[16], int rs[5]);

void instruction_SYSCALL();

void instruction_XOR(int rd[5], int rs[5], int rt[5]);

#endif
