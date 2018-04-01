#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "se_fichier.h"

SE_FICHIER SE_ouverture (const char *chemin, int acces){
	int ret;
	ret = open (chemin, acces, 00751);
	SE_FICHIER fic;
	fic.descripteur = ret;
	fic.acces = acces;
	
	if(ret != -1)	fic.chemin = (char*) chemin;
	else			fic.chemin = NULL;
	return fic;
}

int SE_fermeture (SE_FICHIER fichier){
	return close(fichier.descripteur);
}

int SE_suppression (const char * chemin){
	return unlink(chemin);
}

int SE_lectureCaractere (SE_FICHIER fichier, char * caractere){
	return (int) read(fichier.descripteur, caractere, sizeof(char));
}

int SE_ecritureCaractere (SE_FICHIER fichier, const char caractere){
	return (int) write(fichier.descripteur, &caractere, sizeof(caractere));
}

int SE_lectureChaine (SE_FICHIER fichier, char *chaine, int tailleMax){
	int i;
	int ret;
	int cpt = 0;
	char caractere;
	for (i = 0; i < tailleMax - 1; i++){
		ret = SE_lectureCaractere(fichier, &caractere);
		if(ret > 0)	cpt++,chaine[i] = caractere;
		else 	return ret;
	}
	chaine[tailleMax -1] = '\0';
	return cpt;
}

int SE_ecritureChaine (SE_FICHIER fichier, const char * chaine, int taille){
	int i;
	int ret;
	int cpt = 0;
	for (i = 0; i < taille - 1; i++){
		ret = SE_ecritureCaractere(fichier, chaine[i]);
		if(ret > 0)	cpt++;
		else 	return ret;
	}
	return cpt;
}

int SE_lectureEntier (SE_FICHIER fichier, int * entier){
	*entier = 0;
	int iszero = 0;
	int negatif = 0; // indique si l'on a lu le caractere '-' au debut
	int encore = 1; //stoppe la boucle si on tombe sur un caractere ne constituant pas un entier
	int cpt = 0; //compte le nombre d'octets lues
	int ret = 1; //stocke le retour de lecture d'un caratere
	char c; //stocke le caractere lu
	while(ret == 1 && encore){
		ret = SE_lectureCaractere (fichier, &c);
		if(ret == 1){
			if(c >= '0' && c <= '9'){
				if(c == '0' && *entier == 0)	iszero = 1;
				*entier *= 10;
				*entier += (c - 48);
			}
			else if(c == '-' && *entier == 0 && !iszero)	negatif = 1;
			else if(c == ' '){
				if(*entier != 0 || (*entier == 0 && iszero))	encore = 0;
				else if(negatif == 1)	negatif = 0;
			}
			else	encore = 0;
			cpt++;
		}
	}
	if(negatif) *entier = -*entier;
	return cpt;
}

int SE_lectureEntier2(SE_FICHIER fichier, int * entier, char *c){
	*entier = 0;
	int iszero = 0;
	int negatif = 0; // indique si l'on a lu le caractere '-' au debut
	int encore = 1; //stoppe la boucle si on tombe sur un caractere ne constituant pas un entier
	int cpt = 0; //compte le nombre d'octets lues
	int ret = 1; //stocke le retour de lecture d'un caratere
	while(ret == 1 && encore){
		ret = SE_lectureCaractere (fichier, c);
		if(ret == 1){
			if(*c >= '0' && *c <= '9'){
				if(*c == '0' && *entier == 0)	iszero = 1;
				*entier *= 10;
				*entier += (c - 48);
			}
			else if(*c == '-' && *entier == 0 && !iszero)	negatif = 1;
			else if(*c == ' '){
				if(*entier != 0 || (*entier == 0 && iszero))	encore = 0;
				else if(negatif == 1)	negatif = 0;
			}
			else	encore = 0;
			cpt++;
		}
	}
	if(negatif) *entier = -*entier;
	return cpt;
}

int SE_ecritureEntier (SE_FICHIER fichier, const int entier){
	char s[32];
	sprintf(s,"%d",entier);
	int i = 0;
	int ret = SE_ecritureChaine(fichier,s,strlen(s) + 1);
	return ret;
}

