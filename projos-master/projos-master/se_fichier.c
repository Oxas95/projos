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
	int i = 0;
	int ret;
	int cpt = 0;
	for(i = 0; i < taille; i++){
		ret = SE_ecritureCaractere(fichier, chaine[i]);
		if(ret > 0)	cpt++;
		else 	return ret;
	}
	return cpt;
}

int SE_lectureEntier (SE_FICHIER fichier, int * entier){
	int cpt = 0; //compte le nombre d'octets lues
	//
	return cpt;
}

int SE_lectureEntier2(SE_FICHIER fichier, int * entier, char *c){
	*entier = 0;
	int cpt = 0;
	SE_lectureCaractere(fichier,c);
	while(*c >= '0' && *c <= '9'){
		*entier *= 10;
		*entier += (*c - '0');
		cpt++;
		SE_lectureCaractere(fichier,c);
	}
	return cpt;
}

int nombreChiffre(int nb){
	int cmp = 1;
	while((nb = (nb / 10))){
		cmp++;
	}
	return cmp;	
}

char* itoa(int entier){
	int taille = nombreChiffre(entier);
	char* nombre = malloc((taille + 1) * sizeof(char));
	int i,chiffre;
	for(i = taille - 1; i >= 0; i--){
		chiffre = entier % 10;
		nombre[i] = chiffre + '0';
		entier /= 10;
	}
	nombre[taille] = '\0';
	return nombre;
}

int SE_ecritureEntier (SE_FICHIER fichier, const int entier){
	char* s = itoa(entier);
	int ret = SE_ecritureChaine(fichier,s,nombreChiffre(entier));
	free(s);
	return ret;
}

