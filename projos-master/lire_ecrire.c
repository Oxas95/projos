#include <stdio.h>
#include <stdlib.h>
#include "lire_ecrire.h"
#include "se_fichier.h"


char estChiffreOuSigne(char c){
	if((c >= '0' && c <= '9') || c == '+' || c == '-') return 1;
	return 0;
}

char estChiffre(char c){
	if(c >= '0' && c <= '9') return 1;
	return 0;
}

Plateau init_jeu(){
	Plateau p;
	SE_FICHIER f = SE_ouverture("param.lv21",READ);
	if(f.descripteur==-1)exit(1);
	char c = 0, ret;
	while(c != '\n' && (ret = SE_lectureCaractere(f,&c) > 0)) if(ret != 1) exit(1);
	
	if(SE_lectureEntier(f,&p.nbJoueur) < 1)exit(1);
	if(SE_lectureEntier(f,&p.nbDecks) < 1)exit(1);
	if(SE_lectureEntier(f,&p.nbMains) < 1)exit(1);
	
	SE_fermeture(f);
	
	return p;
}

void init_joueurs(Joueur j[], int taille_tab){
	int i= 0, ret;
	char c = 0;
	
	SE_FICHIER f = SE_ouverture("param.lv21",READ);
	
	for(i = 0; i < 2; i++){
		while(c != '\n' && (ret = SE_lectureCaractere(f,&c) > 0)) if(ret != 1) exit(1);
	}
	
	for (i = 0; i < taille_tab; i++){
		if((SE_lectureEntier(f,&(j[i].nb_jeton)) < 1))exit(1);
		
		if((SE_lectureEntier2(f,&(j[i].mise),&c) < 1))exit(1);
		switch(c){
			case ';' : j[i].typeMise = CSTE;		break;
			case '+' : j[i].typeMise = CROISSANT;	break;
			case '-' : j[i].typeMise = DESCENDANT;	break;
			default  : j[i].typeMise = CSTE;		break;
		}
		
		if(SE_lectureEntier(f,&(j[i].valStop)) < 1)exit(1);
		if(SE_lectureEntier(f,&(j[i].objJetons)) < 1)exit(1);
	}
	
	SE_fermeture(f);
}

int taille_chaine(const char* string){
	int cpt = 0;
	while(string[cpt++] != '\0');
	return cpt;
}

void print(const char* string){ //a tester
	SE_FICHIER s = SE_ouverture("sortie.txt",WRITE);
	SE_ecritureChaine(s,string,taille_chaine(string));
	SE_fermeture(s);
}
