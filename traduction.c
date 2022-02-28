#include "traduction.h"
#include "data.h"
#include "memoire.h"
#include "fonctions_outils.h"
#include "registres.h"



//fonction de traduction de assembleur a hexa
void traduire_pas_inter(char nomFichierIn[], char nomFichierOut[],int afficher){

	char testDir[100] = "";
	char exitDir[100] = "";

	
	

	printf("%s\n%s\n",testDir,exitDir);

	FILE* fichierIn = NULL;
	FILE* fichierOut = NULL;

	PC = 0;//mise à 0 du pc avant traduction afin de bien remplir le tableau contenant le programme depuis le debut

	//ouverture des fichiers
	fichierIn = fopen(strcat(strcat(testDir,TESTDIR),nomFichierIn),"r");
    if(fichierIn == NULL) {
        perror("Probleme ouverture fichier");
        exit(1);
    }

	fichierOut = fopen(strcat(strcat(exitDir,EXITDIR),nomFichierOut),"w");
    if(fichierOut == NULL) {
        perror("Probleme ouverture fichier");
        exit(1);
    }

	ligne ligneCourante;

	//boucle principale qui lit le fichier ligne par ligne et actualise "ligneCourante"
	while (fgets(ligneCourante.string_l,LONGUEUR_LIGNE,fichierIn))
	{

		ligneCourante.erreur = 0;

		if(afficher){
			printf("LIGNE = %s\n",ligneCourante.string_l);
		}

		decomposerMots(&ligneCourante);


		if(ligneCourante.nb_mots==0){//detecte les erreurs
			if(afficher){
				printf("La ligne n'est pas prise en compte (commentaire, vide, ...)\n");
			}
		}else{
			if(afficher){
				for (int i = 0; i < ligneCourante.nb_mots; i++){
					printf("[%s]\n",ligneCourante.motsSepares[i]);
				}
			}

			chercherType(&ligneCourante);

			if(ligneCourante.type_l =='I'){
				remplirPatternI(&ligneCourante,afficher);

				if(ligneCourante.erreur == 0){
					ecritureLigne(fichierOut, ligneCourante.hexa_l);
					recopie_ligne_prog(ligneCourante.binaire_l,ligneCourante.motsSepares,ligneCourante.hexa_l);
				}
			}else if (ligneCourante.type_l =='R'){
				remplirPatternR(&ligneCourante,afficher);

				if(ligneCourante.erreur == 0){
					ecritureLigne(fichierOut, ligneCourante.hexa_l);
					recopie_ligne_prog(ligneCourante.binaire_l,ligneCourante.motsSepares,ligneCourante.hexa_l);
				}
			}else if (ligneCourante.type_l =='J'){
				remplirPatternJ(&ligneCourante,afficher);

				if(ligneCourante.erreur == 0){
					ecritureLigne(fichierOut, ligneCourante.hexa_l);
					recopie_ligne_prog(ligneCourante.binaire_l,ligneCourante.motsSepares,ligneCourante.hexa_l);
				}
			}else{
				printf("ERREUR\nInstruction incconue\n");
			}
		}
		if(afficher){
			printf("---------------------------------\n\n");
		}
	}

	//fermeture des fichiers
	fclose(fichierIn);
	fclose(fichierOut);


	PC = 0; // remise a 0 de PC avant de commencer à executer le code pour bien comencer à la première instruction
}

void traduire_inter(){//demande a l'utilisateur de rentrer une ligne de commande et la traduit de la meme maniere que dans traduire_pas_inter

	ligne ligneCourante;
	ligneCourante.erreur = 0;
	int afficher = 0;

	printf("Entrez une ligne de commande en assembleur :\n ");
	fgets(ligneCourante.string_l,LONGUEUR_LIGNE,stdin);

  decomposerMots(&ligneCourante);
  viderBuffer();


	if(ligneCourante.nb_mots==0){//detecte les erreurs
		if(afficher){
			printf("La ligne n'est pas prise en compte (commentaire, vide, ...)\n");
		}
	}else{
		if(afficher){
			for (int i = 0; i < ligneCourante.nb_mots; i++){
				printf("[%s]\n",ligneCourante.motsSepares[i]);
			}
		}

		chercherType(&ligneCourante);

		if(ligneCourante.type_l =='I'){
			remplirPatternI(&ligneCourante,afficher);

			if(ligneCourante.erreur == 0){
				PC = 0;
				recopie_ligne_prog(ligneCourante.binaire_l,ligneCourante.motsSepares,ligneCourante.hexa_l);
			}
		}else if (ligneCourante.type_l =='R'){
			remplirPatternR(&ligneCourante,afficher);

			if(ligneCourante.erreur == 0){
				PC = 0;
				recopie_ligne_prog(ligneCourante.binaire_l,ligneCourante.motsSepares,ligneCourante.hexa_l);
			}
		}else if (ligneCourante.type_l =='J'){
			remplirPatternJ(&ligneCourante,afficher);

			if(ligneCourante.erreur == 0){
				PC = 0;
				recopie_ligne_prog(ligneCourante.binaire_l,ligneCourante.motsSepares,ligneCourante.hexa_l);
			}
		}else{
			printf("ERREUR : Instruction incconue\n");
		}
	}
	if(afficher){
		printf("---------------------------------\n\n");
	}

}


//affiche la table de correspondance des registres (affiche simplement)
void afficherTableReg(){
	for(int i = 0; i<32;i++){
		printf("[%d] | mnemo = %s | reg = %s\n",
			i,
			table_corres_reg[i].mnemo,
			table_corres_reg[i].reg
		);

	}
};


//decompose en plusieurs mots la ligne (modifie directement la ligne)
void decomposerMots(ligne *ligne_fct){
	const char *separateurs= " ,()\t\n\r";//separateurs
	int index = 0;
	char ligne[LONGUEUR_LIGNE]= "";

	for (int i = 0; i < LONGUEUR_LIGNE; i++){//copie de la ligne dans la variables locale
		ligne[i] = ligne_fct->string_l[i];
	}

	char *mot = strtok(ligne, separateurs );
    while (index < 4 && mot != NULL  && mot[0] != '#') {
		strcpy(ligne_fct->motsSepares[index++],mot) ;

        // On demande le token suivant.
        mot = strtok ( NULL, separateurs );
    }
	ligne_fct->nb_mots = index;

};


//cherche le type de l'instruction décrite dans la ligne (modifie directement la ligne)
void chercherType(ligne *ligne_fct){
	int index=0, tailleTable;
	tailleTable = sizeof(table_type_fct)/sizeof(table_type_fct[0]);

	while ((index < tailleTable-1) && (strcmp(ligne_fct->motsSepares[0],table_type_fct[index].nom) != 0 )){
		index++;
	}

	ligne_fct->type_l = table_type_fct[index].type;
}


//remplie une structure qui copie le pattern d'une instruction de type I element par element puis concatene et convertit en hexa (modifie .binaire et .hexa de la ligne en parametre)
void remplirPatternI(ligne *ligne_fct,int afficher){
	patternI patternLigneCourante;
	int index = 0, tailleTable, placeRegTmp;
	tailleTable = sizeof(table_pattern_fct_I)/sizeof(table_pattern_fct_I[0]);
	//------recherche dans la table pour definir l'index correspondant à l'instruction--------------------------------------------------
	while ((index < tailleTable-1) && (strcmp(ligne_fct->motsSepares[0],table_pattern_fct_I[index].nom) != 0 )){
		index++;
	}

	if (index == tailleTable-1){
		ligne_fct->erreur = 1;
		printf("ERREUR, l'instruction n'est pas présente dans la table des patternI");
	}else if (ligne_fct->nb_mots != table_pattern_fct_I[index].nb_mot_voulu){//verification du nombre d'operande
		ligne_fct->erreur = 1;
		printf("ERREUR, le nombre d'operande n'est pas celui attendu\n");
	}

	if(ligne_fct->erreur == 0){
		//------traitement opcode--------------------------------------------------
		for (int i = 0; i < 6; i++){//recopie opcode
			patternLigneCourante.opcode[i] = table_pattern_fct_I[index].opcode[i];
		}

		if(afficher){
			printf("OPCODE : ");
			printf("{%d,%d,%d,%d,%d,%d}\n",
					patternLigneCourante.opcode[0],
					patternLigneCourante.opcode[1],
					patternLigneCourante.opcode[2],
					patternLigneCourante.opcode[3],
					patternLigneCourante.opcode[4],
					patternLigneCourante.opcode[5]
			);//affiche opcode
		}

		//------traitement rs--------------------------------------------------
		placeRegTmp = table_pattern_fct_I[index].place_rs;
		if (placeRegTmp != -1){
			tradRegistre(ligne_fct->motsSepares[placeRegTmp],patternLigneCourante.rs);
			if (patternLigneCourante.rs[0] == -1) ligne_fct->erreur = 1;
		}else{
			decimal2bin(5,patternLigneCourante.rs,0);
		}

		if(afficher){
			printf("RS : ");
			printf("{%d,%d,%d,%d,%d}\n",
					patternLigneCourante.rs[0],
					patternLigneCourante.rs[1],
					patternLigneCourante.rs[2],
					patternLigneCourante.rs[3],
					patternLigneCourante.rs[4]
			);//affiche rs
		}
	}

	if(ligne_fct->erreur == 0){
		//------traitement rt--------------------------------------------------
		placeRegTmp = table_pattern_fct_I[index].place_rt;
		if (placeRegTmp != -1){
			tradRegistre(ligne_fct->motsSepares[placeRegTmp],patternLigneCourante.rt);
			if (patternLigneCourante.rt[0] == -1) ligne_fct->erreur = 1;
		}else{
			decimal2bin(5,patternLigneCourante.rt,0);
		}

		if(afficher){
			printf("RT : ");
			printf("{%d,%d,%d,%d,%d}\n",
					patternLigneCourante.rt[0],
					patternLigneCourante.rt[1],
					patternLigneCourante.rt[2],
					patternLigneCourante.rt[3],
					patternLigneCourante.rt[4]
			);//affiche rt
		}
	}

	if(ligne_fct->erreur == 0){
		//------traitement immediate--------------------------------------------------
		placeRegTmp = table_pattern_fct_I[index].place_immediate;

		int val_temp = string2decimal(ligne_fct->motsSepares[placeRegTmp]);

		if (val_temp > 32767 || val_temp < -32768)
		{
			printf("Erreur immediat trop grand, merci d'utiliser des nombres entre -32768 et 32767\n");
			ligne_fct->erreur = 1;
		}else{

			decimal2bin(16,patternLigneCourante.immediate,val_temp);

			if(afficher){
				printf("IMMEDIATE : ");
				printf("{");
				for(int i = 0; i < 16; i++){
					printf("%d,",patternLigneCourante.immediate[i]);
				}
				printf("}\n");//affiche immediate
			}


			//------concatenation vecteur binaire----------------------------------------------

			//copie opcode
			for (int i = 0; i < 6; i++){
				ligne_fct->binaire_l[i]=patternLigneCourante.opcode[i];
			}
			//copie rs
			for (int i = 0; i < 5; i++){
				ligne_fct->binaire_l[i+6]=patternLigneCourante.rs[i];
			}
			//copie rt
			for (int i = 0; i < 5; i++){
				ligne_fct->binaire_l[i+11]=patternLigneCourante.rt[i];
			}
			//copie immediate
			for (int i = 0; i < 16; i++){
				ligne_fct->binaire_l[i+16]=patternLigneCourante.immediate[i];
			}

			if(afficher){
				//affiche la ligne en binaire
				printf("{");
				for (int i = 0; i < 32; i++){
					if (i%4 == 0){
						printf(" ");
					}

					printf("%d",ligne_fct->binaire_l[i]);
				}
				printf(" }\n");
			}

			//------conversion hexa----------------------------------------------

			binaire2Hex(ligne_fct->binaire_l,ligne_fct->hexa_l);

			if(afficher){
				//affiche la ligne en hexa
				printf("{");
				for (int i = 0; i < 8; i++){

					printf("  %c  ",ligne_fct->hexa_l[i]);
				}
				printf(" }\n");
			}
		}
	}
}


//remplie une structure qui copie le pattern d'une instruction de type R element par element puis concatene et converti en hexa (modifie .binaire et .hexa de la ligne en parametre)
void remplirPatternR(ligne *ligne_fct,int afficher){
	patternR patternLigneCourante;
	int index = 0, tailleTable, placeRegTmp;
	tailleTable = sizeof(table_pattern_fct_R)/sizeof(table_pattern_fct_R[0]);

	//------recherche dans la table pour definir l'index correspondant à l'instruction--------------------------------------------------
	while ((index < tailleTable-1) && (strcmp(ligne_fct->motsSepares[0],table_pattern_fct_R[index].nom) != 0 )){
		index++;
	}

	if (index == tailleTable-1){
		ligne_fct->erreur = 1;
		printf("ERREUR, l'instruction n'est pas présente dans la table des patternR");
	}else if (ligne_fct->nb_mots != table_pattern_fct_R[index].nb_mot_voulu){//verification du nombre d'operande
		ligne_fct->erreur = 1;
		printf("ERREUR, le nombre d'operande n'est pas celui attendu\n");
	}

	if(ligne_fct->erreur == 0){
		//------traitement opcode--------------------------------------------------
		for (int i = 0; i < 6; i++){//recopie opcode
			patternLigneCourante.opcode[i] = table_pattern_fct_R[index].opcode[i];
		}

		if(afficher){
			printf("OPCODE : ");
			printf("{%d,%d,%d,%d,%d,%d}\n",
					patternLigneCourante.opcode[0],
					patternLigneCourante.opcode[1],
					patternLigneCourante.opcode[2],
					patternLigneCourante.opcode[3],
					patternLigneCourante.opcode[4],
					patternLigneCourante.opcode[5]
			);//affiche opcode
		}


		//------traitement function--------------------------------------------------
		for (int i = 0; i < 6; i++){//recopie opcode
			patternLigneCourante.function[i] = table_pattern_fct_R[index].function[i];
		}

		if(afficher){
			printf("FUNCTION : ");
			printf("{%d,%d,%d,%d,%d,%d}\n",
					patternLigneCourante.function[0],
					patternLigneCourante.function[1],
					patternLigneCourante.function[2],
					patternLigneCourante.function[3],
					patternLigneCourante.function[4],
					patternLigneCourante.function[5]
			);//affiche function
		}


		//------traitement rs--------------------------------------------------
		placeRegTmp = table_pattern_fct_R[index].place_rs;
		if (placeRegTmp != -1 && placeRegTmp != 21){
			tradRegistre(ligne_fct->motsSepares[placeRegTmp],patternLigneCourante.rs);
			if (patternLigneCourante.rs[0] == -1) ligne_fct->erreur = 1;
		}else{
			decimal2bin(5,patternLigneCourante.rs,0);

			if (placeRegTmp == 21){//cas special de ROTR avec le bit 21 = 1
				patternLigneCourante.rs[4] = 1;
			}
		}

		if(afficher){
			printf("RS : ");
			printf("{%d,%d,%d,%d,%d}\n",
					patternLigneCourante.rs[0],
					patternLigneCourante.rs[1],
					patternLigneCourante.rs[2],
					patternLigneCourante.rs[3],
					patternLigneCourante.rs[4]
			);//affiche rs
		}
	}

	if(ligne_fct->erreur == 0){

		//------traitement rt--------------------------------------------------
		placeRegTmp = table_pattern_fct_R[index].place_rt;
		if (placeRegTmp != -1){
			tradRegistre(ligne_fct->motsSepares[placeRegTmp],patternLigneCourante.rt);
			if (patternLigneCourante.rt[0] == -1) ligne_fct->erreur = 1;
		}else{
			decimal2bin(5,patternLigneCourante.rt,0);
		}

		if(afficher){
			printf("RT : ");
			printf("{%d,%d,%d,%d,%d}\n",
					patternLigneCourante.rt[0],
					patternLigneCourante.rt[1],
					patternLigneCourante.rt[2],
					patternLigneCourante.rt[3],
					patternLigneCourante.rt[4]
			);//affiche rt
		}
	}

	if(ligne_fct->erreur == 0){

		//------traitement rd--------------------------------------------------
		placeRegTmp = table_pattern_fct_R[index].place_rd;
		if (placeRegTmp != -1){
			tradRegistre(ligne_fct->motsSepares[placeRegTmp],patternLigneCourante.rd);
			if (patternLigneCourante.rd[0] == -1) ligne_fct->erreur = 1;
		}else{
			decimal2bin(5,patternLigneCourante.rd,0);
		}

		if(afficher){
			printf("RD : ");
			printf("{%d,%d,%d,%d,%d}\n",
					patternLigneCourante.rd[0],
					patternLigneCourante.rd[1],
					patternLigneCourante.rd[2],
					patternLigneCourante.rd[3],
					patternLigneCourante.rd[4]
			);//affiche rd
		}
	}

	if(ligne_fct->erreur == 0){
		//------traitement sa--------------------------------------------------
		placeRegTmp = table_pattern_fct_R[index].place_sa;

		if(placeRegTmp == -1){
			decimal2bin(5,patternLigneCourante.sa,0);
		}else {
			int val_temp = string2decimal(ligne_fct->motsSepares[placeRegTmp]);

			if (val_temp < 0 || val_temp > 31){
				printf("Erreur, [sa] non valide, Merci de rentrer une valeur positive strictement plus petite que 32\n");
				ligne_fct->erreur = 1;
			}else{
				decimal2bin(5,patternLigneCourante.sa,val_temp);
			}
		}
	}


	if(ligne_fct->erreur == 0){

		if(afficher){
			printf("SA : ");
			printf("{");
			for(int i = 0; i < 5; i++){
				printf("%d,",patternLigneCourante.sa[i]);
			}
			printf("}\n");//affiche sa
		}


		//------concatenation vecteur binaire----------------------------------------------

		//copie opcode
		for (int i = 0; i < 6; i++){
			ligne_fct->binaire_l[i]=patternLigneCourante.opcode[i];
		}
		//copie rs
		for (int i = 0; i < 5; i++){
			ligne_fct->binaire_l[i+6]=patternLigneCourante.rs[i];
		}
		//copie rt
		for (int i = 0; i < 5; i++){
			ligne_fct->binaire_l[i+11]=patternLigneCourante.rt[i];
		}
		//copie rd
		for (int i = 0; i < 5; i++){
			ligne_fct->binaire_l[i+16]=patternLigneCourante.rd[i];
		}
		//copie sa
		for (int i = 0; i < 5; i++){
			ligne_fct->binaire_l[i+21]=patternLigneCourante.sa[i];
		}
		//copie function
		for (int i = 0; i < 6; i++){
			ligne_fct->binaire_l[i+26]=patternLigneCourante.function[i];
		}

		if(afficher){
			//affiche la ligne en binaire
			printf("{");
			for (int i = 0; i < 32; i++){
				if (i%4 == 0){
					printf(" ");
				}

				printf("%d",ligne_fct->binaire_l[i]);
			}
			printf(" }\n");
		}

		//------conversion hexa----------------------------------------------

		binaire2Hex(ligne_fct->binaire_l,ligne_fct->hexa_l);

		if(afficher){
			//affiche la ligne en hexa
			printf("{");
			for (int i = 0; i < 8; i++){

				printf("  %c  ",ligne_fct->hexa_l[i]);
			}
			printf(" }\n");
		}
	}
}



//remplie une structure qui copie le pattern d'une instruction de type J element par element puis concatene et convertit en hexa (modifie .binaire et .hexa de la ligne en parametre)
void remplirPatternJ(ligne *ligne_fct,int afficher){
	patternJ patternLigneCourante;
	int index = 0, tailleTable;
	tailleTable = sizeof(table_pattern_fct_J)/sizeof(table_pattern_fct_J[0]);

	//------recherche dans la table pour definir l'index correspondant à l'instruction--------------------------------------------------
	while ((index < tailleTable-1) && (strcmp(ligne_fct->motsSepares[0],table_pattern_fct_J[index].nom) != 0 )){
		index++;
	}

	if (index == tailleTable-1){
		ligne_fct->erreur = 1;
		printf("ERREUR, l'instruction n'est pas présente dans la table des patternJ");
	}else if (ligne_fct->nb_mots != 2){//verification du nombre d'operande
		ligne_fct->erreur = 1;
		printf("ERREUR, le nombre d'operande n'est pas celui attendu\n");
	}

	if(ligne_fct->erreur == 0){
		//------traitement opcode--------------------------------------------------
		for (int i = 0; i < 6; i++){//recopie opcode
			patternLigneCourante.opcode[i] = table_pattern_fct_J[index].opcode[i];
		}

		if(afficher){
			printf("OPCODE : ");
			printf("{%d,%d,%d,%d,%d,%d}\n",
					patternLigneCourante.opcode[0],
					patternLigneCourante.opcode[1],
					patternLigneCourante.opcode[2],
					patternLigneCourante.opcode[3],
					patternLigneCourante.opcode[4],
					patternLigneCourante.opcode[5]
			);//affiche opcode
		}


		//------traitement target--------------------------------------------------
		//Pour le moment, nous ne savons pas exactement la nature de "target", nous ne mettons donc pas de conditions.
		//Pour l'instant nous considérons que target est un entier decimal potentielement signé.
		int val_temp = string2decimal(ligne_fct->motsSepares[1]);
		decimal2bin(26,patternLigneCourante.target,val_temp);// immediate

		if(afficher){
			printf("TARGET : ");
			printf("{");
			for(int i = 0; i < 26; i++){
				printf("%d,",patternLigneCourante.target[i]);
			}
			printf("}\n");//affiche target
		}


		//------concatenation vecteur binaire----------------------------------------------

		//copie opcode
		for (int i = 0; i < 6; i++){
			ligne_fct->binaire_l[i]=patternLigneCourante.opcode[i];
		}
		//copie target
		for (int i = 0; i < 26; i++){
			ligne_fct->binaire_l[i+6]=patternLigneCourante.target[i];
		}

		if(afficher){
			//affiche la ligne en binaire
			printf("{");
			for (int i = 0; i < 32; i++){
				if (i%4 == 0){
					printf(" ");
				}

				printf("%d",ligne_fct->binaire_l[i]);
			}
			printf(" }\n");
		}

		//------conversion hexa----------------------------------------------

		binaire2Hex(ligne_fct->binaire_l,ligne_fct->hexa_l);

		if(afficher){
			//affiche la ligne en hexa
			printf("{");
			for (int i = 0; i < 8; i++){

				printf("  %c  ",ligne_fct->hexa_l[i]);
			}
			printf(" }\n");
		}
	}
}

//prend un nom de registre mnemonique ou decimal et modifie le vecteur binaire en parametre avec le numero du registre (5 bits)
void tradRegistre(char nomRegistre[], int registreBin[]){
	int index =0, tailleTable = sizeof(table_corres_reg)/sizeof(table_corres_reg[0]);

	while ((index < tailleTable-1) && (strcmp(nomRegistre, table_corres_reg[index].mnemo) != 0 )){//recherche dans la table
		index++;
	}
	if (index == tailleTable-1){
		index = 0;
		while ((index < tailleTable-1) && (strcmp(nomRegistre, table_corres_reg[index].reg) != 0 )){//recherche dans la table
			index++;
		}
	}
	if (index == tailleTable-1){
		printf("Erreur, le registre n'existe pas.\n");

		for (int i = 0; i < 5; i++){//recopie registre
			registreBin[i] = -1;
		}
	}else{
		decimal2bin(5,registreBin,index);

	}
}


//ecrit la ligne en hexa dans le document de sortie
void ecritureLigne(FILE* fichier,char ligne[]){
	for (int i = 0; i < 8; i++){
		fputc(ligne[i],fichier);
	}
	fputc('\n',fichier);
}
