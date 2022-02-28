#include "traduction.h"
#include "data.h"
#include "memoire.h"
#include "fonctions_outils.h"
#include "registres.h"
#include "execution.h"

int main(int argc,char *argv[]){

	int pasAPas = 0 , afficher = 0, intercatif = 0;
	
	//detection des options
	if(argc == 1){
		intercatif=1;
	}else{
		for(int i = 0; i < argc; i++) {
			if (strcmp(argv[i],"-pas") == 0){
				pasAPas = 1;
			}
			if (strcmp(argv[i],"-afficher") == 0){
				afficher = 1;
			}
		}
	}

	init_mem();
	init_reg();

	if (intercatif) {
		printf("\n********************* Emulateur MIPS en mode intercatif *********************\n\n");
	}else{
		traduire_pas_inter(argv[1],argv[2],afficher);
		affiche_prog();

		printf("\n********* Lancement de l'execution *********\n*********       PRESS  ENTER       *********\n");
		scanf("*");
		viderBuffer();
	}

	//anciens test
/*
	unsigned int data = 4294967000;
	unsigned int add = 8400;

	for(int i = 0; i < 9; i+=4){
		ecrire_mem(i,data);
	}

	ecrire_mem(add,8754);
	ecrire_mem(44,555);

	charge_mem(0,registres[10]);
	charge_mem(44,registres[16]);

	int bin12[5]={0,1,1,0,0};//12
	int bin10[5]={0,1,0,1,0};//10
	int bin15[5]={0,1,1,1,1};//15
	int bin0[5]={0,0,0,0,0};//0

	decimal2bin(32,registres[12],41);
	decimal2bin(32,registres[10],26);

	//instruction_ADD(bin15,bin12,bin10);
*/

	executer(pasAPas,intercatif);

	if (intercatif == 0) {
		printf("\n********** Etat final Memoire + Registres **********\n");
		affiche_mem();
		affiche_reg();

		ecritureRegistre(argv[3]);
	}
	return 0;
}
