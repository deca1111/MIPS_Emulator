#include "registres.h"
#include "data.h"
#include "fonctions_outils.h"

int registres[32][32];//tableau contenant les registres usuels (de $0 a $31)

int PC = 0;//registre PC, defini comme etant un int car ne peut pas depasser TAILLE_MAX_PROG (en vrai PC est un vecteur de 32 bits)

long int HI = 0,LO = 0;//registres LI et HO

void init_reg(){//initialise les registres a 0
  for(int ligne = 0; ligne < 32; ligne++){
    decimal2bin(32,registres[ligne],0);
  }
}

void affiche_reg(){//affiche les registres avec leurs 2 nom (mnemo et decimal)
  printf("\nRegistres : \n");
  for(int ligne = 0; ligne < 8; ligne++){//affiche 4 registres par ligne
    printf("[$%-1d] [%-5s] : %-11ld      [$%-2d] [%-3s] : %-11ld      [$%-2d] [%-3s] : %-11ld      [$%-2d] [%-3s] : %ld\n"
    , ligne
    , table_corres_reg[ligne].mnemo
    , bin2Decimal(32,registres[ligne],1)
    , ligne+8
    , table_corres_reg[ligne+8].mnemo
    , bin2Decimal(32,registres[ligne+8],1)
    , ligne+16
    , table_corres_reg[ligne+16].mnemo
    , bin2Decimal(32,registres[ligne+16],1)
    , ligne+24
    , table_corres_reg[ligne+24].mnemo
    , bin2Decimal(32,registres[ligne+24],1)
    );
  }
  printf("\n");
  printf("PC = %d    HI = %ld    LO = %ld\n",PC,HI,LO);
}


//ecrit des registres dans un fichier
void ecritureRegistre(char nomFichierOut[]){

  char regDir[100]= "";

  FILE* fichierOut = NULL;

  fichierOut = fopen(strcat(strcat(regDir,REGDIR),nomFichierOut),"w");
    if(fichierOut == NULL) {
        perror("Probleme ouverture fichier");
        exit(1);
    }
  
	for (int i = 0; i < 32; i++){
    fprintf(fichierOut,"%s: %ld\n",table_corres_reg[i].reg,bin2Decimal(32,registres[i],1));
		/*fputs(table_corres_reg[i].reg,fichierOut);
		fputs(": ",fichierOut);
		//fputs((char*) bin2Decimal(32,registres[i],1),fichierOut);
    fputc('\n',fichierOut);*/
	}
	
  fclose(fichierOut);
}