#include "memoire.h"

case_memory memory[TAILLE_MEM];//mémoire 100*4octets

int stock_prog_bin[TAILLE_MAX_PROG][32];//stockage du programme traduit (100 lignes max)

char stock_prog_string[TAILLE_MAX_PROG][LONGUEUR_LIGNE];//stockage du programme en string (100 lignes max)

char stock_prog_hexa[TAILLE_MAX_PROG][8];//stockage du programme en hexa

void init_mem(){//initialise la memoire
  for(int i = 0; i < TAILLE_MEM ; i++){
    memory[i].adresse = 4294967295;//adresse "speciale" signifiant que la case est libre
  }
  for(int i = 0; i < TAILLE_MAX_PROG ; i++){
    stock_prog_bin[i][0] = -1;//signifie que la ligne est vide et ne doit pas être prise en compte
  }
}


void ecrire_mem(unsigned int adresse_dest, long int data){//permet d'ecrire dans la memoire une donnee stockee sur 32 bits aune adresse donnee
  if(adresse_dest%4 ==0) {//verification "naturally aligned"
    int index_mem =0;

    while ((index_mem < TAILLE_MEM) && (memory[index_mem].adresse != adresse_dest)) {//verifie si l'adresse est deja dans la memoire de l'emulateur
      index_mem++;
    }
    if(index_mem == TAILLE_MEM){//cas ou l'adresse n'est pas dans la memoire de l'emulateur, on cherche donc une case libre
      index_mem = 0;
      while ((index_mem < TAILLE_MEM) && (memory[index_mem].adresse != 4294967295)) {
        index_mem++;
      }
    }
    if (index_mem == TAILLE_MEM) {//cas ou aucune case n'est libre
      printf("ERREUR : Memoire emulateur pleine, ecriture memoire impossible\n\n");
    }else{
      memory[index_mem].adresse = adresse_dest;
      memory[index_mem].donnees = data;
    }
  }else{
    printf("ERREUR : L'adresse [%u] est non 'naturally aligned', acces memoire impossible\n\n",adresse_dest);
  }
}

void charge_mem(unsigned int adresse_src, int reg[32]){//permet de dans un registre une donnee stockee sur 32 bits a une adresse donnee en memoire
  if(adresse_src%4 ==0) {//verification "naturally aligned"
    int index_mem =0;

    while((index_mem<TAILLE_MEM) && (memory[index_mem].adresse != adresse_src)){
      index_mem++;
    }
    if(index_mem == TAILLE_MEM){
      printf("ERREUR : La mémoire est vide à l'adresse [%u], impossible de charger les donnees \n\n", adresse_src);
    }else{
      decimal2bin(32,reg,memory[index_mem].donnees);
    }
  }else{
    printf("ERREUR : L'adresse [%u] est non 'naturally aligned', acces memoire impossible\n\n",adresse_src);
  }
}

void affiche_mem(){//affiche la memoire (seuelement les adresse non vide)
  int vide = 1;
  printf("\nMemoire :\n");
  for(int index_mem = 0; index_mem <TAILLE_MEM; index_mem++){
    if(memory[index_mem].adresse != 4294967295){
      vide = 0;
      printf("Adresse bloc : %-10u  --         Donnees : %ld\n", memory[index_mem].adresse,memory[index_mem].donnees);
    }
  }
  if (vide == 1) {
    printf("Vide\n");
  }
}

//ATTENTION Cette fonction incremente le PC
void recopie_ligne_prog(int ligne[32],char motsSepares[4][20],char hexa_l[8]){//recopie la ligne en cours de traduction dans les tableaux contenant le programme sous differente forme
  if(PC<TAILLE_MAX_PROG){
    for (int i = 0; i < 32; i++) {
      stock_prog_bin[PC][i] = ligne[i];
    }
    for(int i = 0; i < 4; i++){
      strcat(stock_prog_string[PC],motsSepares[i]);
      strcat(stock_prog_string[PC],", ");
    }
    for(int i = 0; i<8; i++){
      stock_prog_hexa[PC][i]=hexa_l[i];
    }
    PC++;
  }else{
    printf("ERREUR : Programme trop long, ligne non prise en compte\n\n");
  }
}

void affiche_prog(){//affiche le programme en hexa puis en toutes lettre ( affiche aussi le numero de ligne)
  printf("Programme :\n");
  for(int index_prog = 0; index_prog <TAILLE_MAX_PROG; index_prog++){
    if(stock_prog_bin[index_prog][0] != -1){
      printf("[%d] : [", index_prog );
      for(int index_ligne = 0; index_ligne < 8; index_ligne++){
        printf("%c,", stock_prog_hexa[index_prog][index_ligne]);
      }
      printf("] -- %s \n", stock_prog_string[index_prog]);
    }
  }
}
