#include "fonctions_outils.h"

//convertit un nombre decimal en un vecteur binaire
void decimal2bin(int taille, int bin[], long int dec){
	int neg = 0;
	int j = 0;

	if (dec <0){
		dec *= -1;
		neg=1;
	}
	for (int i = taille-1; i > -1; i--){
		bin[i]=dec%2;
		dec/=2;
	}
	if (neg == 1){
		for (int i = taille-1; i > -1; i--){
			(bin[i]==0)?(bin[i]=1):(bin[i]=0);
		}
		while ( bin[taille-1-j] == 1){
			bin[taille-1-j] = 0;
			j++;
		}
		bin[taille-1-j] = 1;
	}
}


//convertit une chaine de caractère en nombre decimal
int string2decimal(char* nombre){
    int res = 0,index = 0, valeur, puissance = strlen(nombre) - 1,neg = 0;//parce que 1 = 10^0

	if(nombre[0] == 45){
		index = 1;
		neg = 1;
	}
    while (nombre[index] < 58 && nombre[index] > 47){
		valeur = nombre[index] - 48;

        res += valeur * pow(10,puissance-index);
        index++;
    }
    if (neg){
	    res *= -1;
    }
    return res;
}

//convertit un vecteur binaire en un vecteur hexadecimal (modifie les tableaux en parametre)
void binaire2Hex(int bin[],char hex[]){
	char tableHex[]="0123456789abcdef";
	int valeur=0;
	for (int i = 0; i < 8; i++){
		valeur = 0;
		valeur+=bin[(i*4)]*8;
		valeur+=bin[(i*4)+1]*4;
		valeur+=bin[(i*4)+2]*2;
		valeur+=bin[(i*4)+3]*1;
		hex[i]=tableHex[valeur];
	}
}

long int bin2Decimal(int taille, int bin[],int compl2){//convertit un vecteur binaire en decimal
	int resultat = 0;
	int temp[taille];
	int neg = 0;

	if (bin[0] == 1 && compl2) {//cas ou le nombre est negatif
		neg = 1;
		int index = taille - 1;
		while (bin[index] == 0) {
			temp[index] = bin[index];
			index--;
		}
		temp[index] = bin[index];
		index --;
		for (int i = index ; i > -1; i--) {
			temp[i] = bin[i] ? 0 : 1;
		}

		for (int i = 0;  i < taille; i++) {
			resultat += temp[i]*pow(2,taille-i-1);
		}
	}else{
		for (int i = 0;  i < taille; i++) {
			resultat += bin[i]*pow(2,taille-i-1);
		}
	}
	resultat = neg ? -resultat : resultat;

	return resultat;
}

void decoupeur_binaire(int debut, int fin, int source[], int dest[fin-debut+1]){//debut et fin selon index tableau, pas selon numero de bit usuels
	for(int i = 0; i<fin-debut+1; i++){
		dest[i] = source[i+debut];
	}
}

void viderBuffer(void){
  int c;
  while((c=getchar()) != EOF && c != '\n');

}
