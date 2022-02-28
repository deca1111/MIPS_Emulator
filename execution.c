#include "memoire.h"
#include "fonctions_outils.h"
#include "registres.h"
#include "execution.h"
#include "traduction.h"

void executer(int pasAPas,int intercatif){
  PC = 0; // remise a 0 de PC pour commencer l'execution au debut

  if (intercatif) {//initialisation de la condition pour le mode interactif
    stock_prog_bin[PC][0] = 0;
  }

  while(PC < TAILLE_MAX_PROG && stock_prog_bin[PC][0] != -1 ){
    //mots binaires contenant les differents champs
    int opcode[6];
    int target[26];
    int function[6];
    int immediate[16];
    int rs[5];
    int rt[5];
    int rd[5];
    int sa[5];


    printf("\n**************************************************\nLigne en cours d'execution : \n");
    printf("[%d] -- %s\n",PC,stock_prog_string[PC]);
    
    if (intercatif) {
      traduire_inter();//appel de la fonction permettant de traduire une seule ligne renseignee par l'utilisateur
      PC = 0;
    }

    //utilisation de la fonction decoupeur_binaire pour remplir les differents champs
    decoupeur_binaire(0,5,stock_prog_bin[PC],opcode);
    decoupeur_binaire(6,31,stock_prog_bin[PC],target);
    decoupeur_binaire(26,31,stock_prog_bin[PC],function);
    decoupeur_binaire(16,31,stock_prog_bin[PC],immediate);
    decoupeur_binaire(6,10,stock_prog_bin[PC],rs);
    decoupeur_binaire(11,15,stock_prog_bin[PC],rt);
    decoupeur_binaire(16,20,stock_prog_bin[PC],rd);
    decoupeur_binaire(21,25,stock_prog_bin[PC],sa);

    //structure elseif permettant de selectionner l'instruction contenue dans la ligne
    if(bin2Decimal(6,opcode,0) == 0){//opcode special

      if (bin2Decimal(6,function,0) == 32) {//function ADD
        instruction_ADD(rd,rs,rt);
      }else if (bin2Decimal(6,function,0) == 36) {//function AND
        instruction_AND(rd,rs,rt);
      }else if (bin2Decimal(6,function,0) == 26) {//function DIV
        instruction_DIV(rs,rt);
      }else if (bin2Decimal(6,function,0) == 8) {//function JR
        instruction_JR(rs);
      }else if (bin2Decimal(6,function,0) == 16) {//function MFHI
        instruction_MFHI(rd);
      }else if (bin2Decimal(6,function,0) == 18) {//function MFLO
        instruction_MFLO(rd);
      }else if (bin2Decimal(6,function,0) == 24) {//function MULT
        instruction_MULT(rs,rt);
      }else if (bin2Decimal(6,function,0) == 0) {//function SLL / NOP
        instruction_SLL(rd,rt,sa);
      }else if (bin2Decimal(6,function,0) == 37) {//function OR
        instruction_OR(rd,rs,rt);
      }else if (bin2Decimal(6,function,0) == 2) {//function SRL / ROTR
        if (stock_prog_bin[PC][10] == 1) {//function ROTR
          instruction_ROTR(rd,rt,sa);
        }else{//function SRL
          instruction_SRL(rd,rt,sa);
        }
      }else if (bin2Decimal(6,function,0) == 42) {//function SLT
        instruction_SLT(rd,rs,rt);
      }else if (bin2Decimal(6,function,0) == 34) {//function SUB
        instruction_SUB(rd,rs,rt);
      }else if (bin2Decimal(6,function,0) == 12) {//function SYSCALL
        instruction_SYSCALL();
      }else if (bin2Decimal(6,function,0) == 38) {//function XOR
        instruction_XOR(rd,rs,rt);
      }else{//function incconu
        printf("ERREUR : Instruction incconue\n");
        PC++;
      }
    }else if (bin2Decimal(6,opcode,0) == 8) {//opcode ADDI
      instruction_ADDI(rt,rs,immediate);
    }else if (bin2Decimal(6,opcode,0) == 4) {//opcode BEQ
      instruction_BEQ(rs,rt,immediate);
    }else if (bin2Decimal(6,opcode,0) == 7) {//opcode BGTZ
      instruction_BGTZ(rs,immediate);
    }else if (bin2Decimal(6,opcode,0) == 6) {//opcode BLEZ
      instruction_BLEZ(rs,immediate);
    }else if (bin2Decimal(6,opcode,0) == 5) {//opcode BNE
      instruction_BNE(rs,rt,immediate);
    }else if (bin2Decimal(6,opcode,0) == 2) {//opcode J
      instruction_J(target);
    }else if (bin2Decimal(6,opcode,0) == 3) {//opcode JAL
      instruction_JAL(target);
    }else if (bin2Decimal(6,opcode,0) == 15) {//opcode LUI
      instruction_LUI(rt,immediate);
    }else if (bin2Decimal(6,opcode,0) == 35) {//opcode LW
      instruction_LW(rt,immediate,rs);
    }else if (bin2Decimal(6,opcode,0) == 43) {//opcode SW
      instruction_SW(rt,immediate,rs);
    }else if (bin2Decimal(6,opcode,0) == 1) {//opcode EXIT //On choisi l'opcode 1 car non utilise pour representer EXIT
      exit(0);
    }else{//opcode incconu
      printf("ERREUR : Instruction incconue\n");
      PC++;
    }
	
    //comme demand� dans le sujet, affiche une atualisation des registres et de la memoire apres chaque instruction
    printf("\n********** Etat Memoire + Registres **********\n");
    affiche_mem();
    affiche_reg();
    
    if (pasAPas) {//attende que l'utilisateur ai appuy� sur "entree" pour passer a la ligne suivante
      printf("\n********* Prochaine instruction *********\n*********      PRESS ENTER      *********\n");
    	scanf("*");
      viderBuffer();
    }

    if (intercatif) {
      PC = 0;
    }
  }

}



void instruction_ADD(int rd[5], int rs[5], int rt[5]){
  long int val_rs, val_rt;
  val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],1);
  val_rt = bin2Decimal(32,registres[bin2Decimal(5,rt,0)],1);
  if (bin2Decimal(5,rd,0) != 0 && (val_rs + val_rt < 2147483648) && (val_rs + val_rt > -2147483649)) { // exceptions
    decimal2bin(32,registres[bin2Decimal(5,rd,0)],val_rs + val_rt);
  }
  PC++;
}

void instruction_ADDI(int rt[5], int rs[5], int immediate[16]){
  long int val_rs, val_immediate;
  val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],1);
  val_immediate = bin2Decimal(16,immediate,1);
  if (bin2Decimal(5,rt,0) != 0 && (val_rs + val_immediate < 2147483648) && (val_rs + val_immediate > -2147483649)) { // exceptions
    decimal2bin(32,registres[bin2Decimal(5,rt,0)],val_rs + val_immediate);
  }
  PC++;
}

void instruction_AND(int rd[5], int rs[5], int rt[5]){
  if (bin2Decimal(5,rd,0) != 0) {
    for(int i = 0; i < 32; i++){
      registres[bin2Decimal(5,rd,0)][i] = registres[bin2Decimal(5,rs,0)][i] & registres[bin2Decimal(5,rt,0)][i];
    }
  }
  PC++;
}

void instruction_BEQ(int rs[5], int rt[5], int immediate[16]){//comme on est sensé shift de 2 l'offset (*4) pour correspondre à un bloc dans la memoire, ici il nous suffit d'ajouter l'immediate directement au PC
  long int val_rs, val_rt;
  val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],1);
  val_rt = bin2Decimal(32,registres[bin2Decimal(5,rt,0)],1);
  if (val_rs == val_rt) {
    if ((PC + 1 + bin2Decimal(16,immediate,1)) < 0 || (PC + 1 + bin2Decimal(16,immediate,1)) >= TAILLE_MAX_PROG) {
      printf("ERREUR, adresse de jump non valable (hors des limites du programme), instruction ignoree\n");
      PC++;
    }else{
      PC += 1 + bin2Decimal(16,immediate,1);
    }
  }else{
    PC++;
  }
}

void instruction_BGTZ(int rs[5], int immediate[16]){
  long int val_rs;
  val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],1);
  if (val_rs > 0) {
    if ((PC + 1 + bin2Decimal(16,immediate,1)) < 0 || (PC + 1 + bin2Decimal(16,immediate,1)) >= TAILLE_MAX_PROG) {
      printf("ERREUR, adresse de jump non valable (hors des limites du programme), instruction ignoree\n");
      PC++;
    }else{
      PC += 1 + bin2Decimal(16,immediate,1);
    }
  }else{
    PC++;
  }
}

void instruction_BLEZ(int rs[5], int immediate[16]){
  long int val_rs;
  val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],1);
  if (val_rs <= 0) {
    if ((PC + 1 + bin2Decimal(16,immediate,1)) < 0 || (PC + 1 + bin2Decimal(16,immediate,1)) >= TAILLE_MAX_PROG) {
      printf("ERREUR, adresse de jump non valable (hors des limites du programme), instruction ignoree\n");
      PC++;
    }else{
      PC += 1 + bin2Decimal(16,immediate,1);
    }
  }else{
    PC++;
  }
}

void instruction_BNE(int rs[5], int rt[5], int immediate[16]){
  long int val_rs, val_rt;
  val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],1);
  val_rt = bin2Decimal(32,registres[bin2Decimal(5,rt,0)],1);
  if (val_rs != val_rt) {
    if ((PC + 1 + bin2Decimal(16,immediate,1)) < 0 || (PC + 1 + bin2Decimal(16,immediate,1)) >= TAILLE_MAX_PROG) {
      printf("ERREUR, adresse de jump non valable (hors des limites du programme), instruction ignoree\n");
      PC++;
    }else{
      PC += 1 + bin2Decimal(16,immediate,1);
    }
  }else{
    PC++;
  }
}

void instruction_DIV(int rs[5], int rt[5]){
  long int val_rs, val_rt, q, r;
  val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],1);
  val_rt = bin2Decimal(32,registres[bin2Decimal(5,rt,0)],1);
  q = val_rs / val_rt;
  r = val_rs % val_rt;
  LO = q;
  HI = r;
  PC++;
}

void instruction_J(int target[26]){//la target est shift de 2, ici on prend donc la target comme numero de ligne absolu (pas PC-relatif)
  unsigned int val_target;
  val_target = bin2Decimal(26,target,0);
  if (val_target < 0 || val_target >= TAILLE_MAX_PROG) {
    printf("ERREUR, adresse de jump non valable (hors des limites du programme), instruction ignoree\n");
    PC++;
  }else{
    PC = val_target;
  }
}

void instruction_JAL(int target[26]){
  unsigned int val_target;
  val_target = bin2Decimal(26,target,0);
  if (val_target < 0 || val_target >= TAILLE_MAX_PROG) {
    printf("ERREUR, adresse de jump non valable (hors des limites du programme), instruction ignoree\n");
    PC++;
  }else{
    decimal2bin(32,registres[31],(PC+2)*4);
    PC = val_target;
  }
}

void instruction_JR(int rs[5]){
  long int val_rs;
  val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],0);
  if (val_rs%4 != 0) {
    printf("ERREUR : Adresse de Jump Non Naturally-aligned, jump non effectue\n");
  }else{
    if ((val_rs/4) < 0 || (val_rs/4) >= TAILLE_MAX_PROG) {
      printf("ERREUR, adresse de jump non valable (hors des limites du programme), instruction ignoree\n");
      PC++;
    }else{
      PC = (val_rs/4);
    }
  }
}

void instruction_LUI(int rt[5], int immediate[16]){
  if (bin2Decimal(5,rt,0) != 0) {
    for (int i = 0; i < 16; i++) {
      registres[bin2Decimal(5,rt,0)][i] = immediate[i];
    }
    for (int i = 16; i < 32; i++) {
      registres[bin2Decimal(5,rt,0)][i] = 0;
    }
  }
  PC++;
}

void instruction_LW(int rt[5], int immediate[16], int rs[5]){
  long int val_immediate, val_rs;
  val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],0);
  val_immediate = bin2Decimal(16,immediate,1);
  if (bin2Decimal(5,rt,0) != 0) {
    charge_mem(val_rs+val_immediate,registres[bin2Decimal(5,rt,0)]);
  }
  PC++;
}

void instruction_MFHI(int rd[5]){
  if (bin2Decimal(5,rd,0) != 0) {
    decimal2bin(32,registres[bin2Decimal(5,rd,0)],HI);
  }
  PC++;
}

void instruction_MFLO(int rd[5]){
  if (bin2Decimal(5,rd,0) != 0) {
    decimal2bin(32,registres[bin2Decimal(5,rd,0)],LO);
  }
  PC++;
}

void instruction_MULT(int rs[5], int rt[5]){
  long int val_rs, val_rt;
  long long int res;
  int bin_res[64], bin_HI[32], bin_LO[32];
  val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],1);
  val_rt = bin2Decimal(32,registres[bin2Decimal(5,rt,0)],1);
  res = val_rs * val_rt;
  decimal2bin(64,bin_res,res);
  decoupeur_binaire(0,31,bin_res,bin_HI);
  decoupeur_binaire(32,63,bin_res,bin_LO);
  HI = bin2Decimal(32,bin_HI,1);
  LO = bin2Decimal(32,bin_LO,1);
  PC++;
}

void instruction_OR(int rd[5], int rs[5], int rt[5]){
  if (bin2Decimal(5,rd,0) != 0) {
    for(int i = 0; i < 32; i++){
      registres[bin2Decimal(5,rd,0)][i] = registres[bin2Decimal(5,rs,0)][i] | registres[bin2Decimal(5,rt,0)][i];
    }
  }
  PC++;
}

void instruction_ROTR(int rd[5], int rt[5], int sa[5]){
  int val_sa;
  val_sa = bin2Decimal(5,sa,0);
  if (bin2Decimal(5,rd,0) != 0) {
    for(int i = 0; i < val_sa; i++){
      registres[bin2Decimal(5,rd,0)][val_sa-1-i] = registres[bin2Decimal(5,rt,0)][31 - i];
    }
    for (int i = val_sa; i < 32; i++) {
      registres[bin2Decimal(5,rd,0)][i] = registres[bin2Decimal(5,rt,0)][i - val_sa];
    }
  }
  PC++;
}

void instruction_SLL(int rd[5], int rt[5], int sa[5]){
  int val_sa;
  val_sa = bin2Decimal(5,sa,0);
  if (bin2Decimal(5,rd,0) != 0) {
    for(int i = val_sa; i < 32; i++){
      registres[bin2Decimal(5,rd,0)][i - val_sa] = registres[bin2Decimal(5,rt,0)][i];
    }
    for(int i = 32 - val_sa; i < 32; i++){
      registres[bin2Decimal(5,rd,0)][i] = 0;
    }
  }
  PC++;
}

void instruction_SLT(int rd[5], int rs[5], int rt[5]){
  long int val_rs, val_rt;
  int res;
  if (bin2Decimal(5,rd,0) != 0) {
    val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],1);
    val_rt = bin2Decimal(32,registres[bin2Decimal(5,rt,0)],1);
    res = (val_rs < val_rt);
    decimal2bin(32,registres[bin2Decimal(5,rd,0)],res);
  }
  PC++;
}

void instruction_SRL(int rd[5], int rt[5], int sa[5]){
  int val_sa;
  if (bin2Decimal(5,rd,0) != 0) {
    val_sa = bin2Decimal(5,sa,0);
    for(int i = val_sa; i < 32; i++){
      registres[bin2Decimal(5,rd,0)][i] = registres[bin2Decimal(5,rt,0)][i - val_sa];
    }
    for(int i = 0; i < val_sa; i++){
      registres[bin2Decimal(5,rd,0)][i] = 0;
    }
  }
  PC++;
}

void instruction_SUB(int rd[5], int rs[5], int rt[5]){
  long int val_rs, val_rt;
  val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],1);
  val_rt = bin2Decimal(32,registres[bin2Decimal(5,rt,0)],1);
  if (bin2Decimal(5,rd,0) != 0 && (val_rs - val_rt < 2147483648) && (val_rs - val_rt > -2147483649)) { // exceptions
    decimal2bin(32,registres[bin2Decimal(5,rd,0)],val_rs - val_rt);
  }
  PC++;
}

void instruction_SW(int rt[5], int immediate[16], int rs[5]){
  long int val_immediate, val_rs, val_rt;
  val_rs = bin2Decimal(32,registres[bin2Decimal(5,rs,0)],0);
  val_rt = bin2Decimal(32,registres[bin2Decimal(5,rt,0)],1);
  val_immediate = bin2Decimal(16,immediate,1);
  ecrire_mem(val_rs+val_immediate,val_rt);
  PC++;
}

void instruction_SYSCALL(){//on a pas trop compris le fonctionnement de cette instruction,
//nous avons vu beaucoup de fonctionnalites disponible (une soixantaine), nous n'allons pas toutes les implementer
  long int val_v0 = bin2Decimal(32,registres[2],1);
  if(val_v0 == 1){//print integer
    printf("%ld\n", bin2Decimal(32,registres[4],1));
  }else if(val_v0 == 11){//print char
    printf("%c\n", (char) bin2Decimal(32,registres[4],1));
  }else{
    printf("ERREUR : Code SYSCALL non valide ou non implemente \n");
  }
  PC++;
}

void instruction_XOR(int rd[5], int rs[5], int rt[5]){
  if (bin2Decimal(5,rd,0) != 0) {
    for(int i = 0; i < 32; i++){
      registres[bin2Decimal(5,rd,0)][i] = registres[bin2Decimal(5,rs,0)][i] ^ registres[bin2Decimal(5,rt,0)][i];
    }
  }
  PC++;
}
