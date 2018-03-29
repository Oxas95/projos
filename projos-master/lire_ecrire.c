#include <stdio.h>
#include <stdlib.h>
#include "lire_ecrire.h"
#include "se_fichier.h"
//a mettre dans lire ecire.h
/*
typedef struct {
	int nbJoueur,nbDecks,nbMains;
	Joueur* j;
} Plateau;

*/

char estChiffreOuSigne(char c){
	if((c >= '0' && c <= '9') || c == '+' || c == '-') return 1;
	return 0;
}

char estChiffre(char c){
	if(c >= '0' && c <= '9') return 1;
	return 0;
}

Plateau init_jeu(){ //a remplacer avec se_fichier.h
	Plateau p;
	SE_FICHIER f = SE_ouverture("param.lv21",READ);
	int l = 0,i,j = 0;
	char c = 0, chaine [30] = {0}; int ret;
	while(c != '\n' && (ret = SE_lectureCaractere(f,&c) > 0)) if(ret != 1) exit(1);
	
	if(SE_lectureEntier(f,&p.nbJoueur) < 1)exit(1);
	if(SE_lectureEntier(f,&p.nbDecks) < 1)exit(1);
	if(SE_lectureEntier(f,&p.nbMains) < 1)exit(1);
	p.joueur = malloc(p.nbJoueur*sizeof(Joueur)); // j'ai enlevé un exit(1); ici
	
	for (i = 0; i < p.nbJoueur; i++){
		if(SE_lectureEntier(f,&(p.joueur[i].nb_jeton)) < 1)exit(1);
		c = 0; j = 0;
		while(c != ';' && (ret = SE_lectureCaractere(f,&c)) > 1){
			if(estChiffreOuSigne(c) && j < 30)chaine[j++] = c;
		} if(ret < 1) exit(1);
		j = 0;
		while(estChiffre(chaine[j])){
			l *= 10; l += atoi(chaine[j++]); 
		}
		if(chaine[j] != '+' && chaine[j] != '-')p.joueur[i].typeMise = CSTE;
		else p.joueur[i].typeMise = chaine[j];
		p.joueur[i].mise = l;
		
		if(SE_lectureEntier(f,&(p.joueur[i].valStop)) < 1)exit(1);
		if(SE_lectureEntier(f,&(p.joueur[i].objJetons)) < 1)exit(1);
	}
	
	
	return p;
}

int lire_entier(int fd)
{
	int entier=0;
	return entier;
	
	}	
	


void ecrire_fichier()
{
	
	
	;
	
	}
