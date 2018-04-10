#include <stdio.h>
#include <stdlib.h>
#include "lire_ecrire.h"
#include "se_fichier.h"
#include "deck.h"

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
	while(c != '\n' && (ret = SE_lectureCaractere(f,&c) > 0))if(ret != 1) exit(1);
	
	if(SE_lectureEntier(f,&p.nbJoueur) < 1)exit(1);
	if(SE_lectureEntier(f,&p.nbDecks) < 1)exit(1);
	if(SE_lectureEntier(f,&p.nbMains) < 1)exit(1);
	
	SE_fermeture(f);
	
	return p;
}

void init_joueurs(Joueur j[], int taille_tab){
	int i = 0, ret;
	char c = 0;
	
	SE_FICHIER f = SE_ouverture("param.lv21",READ);
	
	for(i = 0; i < 3; i++){
		while(c != '\n' && (ret = SE_lectureCaractere(f,&c) > 0)){
			if(ret != 1) exit(1);
		}
		c = 0;
	}
	
	for (i = 0; i < taille_tab; i++){
		if((SE_lectureEntier(f,&(j[i].nbJetons)) < 1))exit(1);
		if((SE_lectureEntier2(f,&(j[i].mise),&c) < 1))exit(1);
		switch(c){
			case ';' : j[i].typeMise = CSTE;		break;
			case '+' : j[i].typeMise = CROISSANT;	break;
			case '-' : j[i].typeMise = DESCENDANT;	break;
			default  : j[i].typeMise = CSTE;		break;
		}
		if(j[i].typeMise != CSTE) SE_lectureCaractere(f,&c);
		if(SE_lectureEntier(f,&(j[i].valStop)) < 1)exit(1);
		if(SE_lectureEntier(f,&(j[i].objJetons)) < 1)exit(1);
		j[i].numero = i;
		j[i].score = 0;
	}
	
	SE_fermeture(f);
}

int taille_chaine(const char* string){
	int cpt = 0;
	while(string[cpt++] != '\0');
	return cpt;
}

void print(const char* string){ 

	int fd = STDOUT_FILENO;
	write(fd,string,taille_chaine(string));
}
void ecrire_numero_carte(SE_FICHIER f,const int value){
	int i = (value % 13) + 1;
	SE_ecritureCaractere(f,i + '0');
}

void ecrire_carte(SE_FICHIER f,const int value) {
	//if (value == 52) { print ("J*"); return; }
	switch (value % 13) {
		case 0: SE_ecritureCaractere(f,'A');   break;
		case 9: SE_ecritureCaractere(f,'X');   break;
		case 10: SE_ecritureCaractere (f,'J'); break;
		case 11: SE_ecritureCaractere (f,'Q'); break;
		case 12: SE_ecritureCaractere (f,'K'); break;
		default: ecrire_numero_carte(f,value);
	}
}
int nombreChiffre(int nb){
	int cmp=1;
	while((nb=(nb/10))){
		cmp++;
	}
	return cmp;	
}



void ecrireEntier(SE_FICHIER f,int nb){
	int taille = nombreChiffre(nb);
	char nombre[taille];

	int i,chiffre;
	for(i = taille - 1; i >= 0; i--){
		chiffre=nb % 10;
		nombre[i]=chiffre+'0';
		nb/=10;
	}
	for(i=0;i<taille;i++){
		write(f.descripteur,&nombre[i],sizeof(char));
	}
}

void ecrire_fichier(Joueur j,Main banque,int totalBanque){
	int i = 0; SE_FICHIER f;
	char s[40] = {'t','o','u','r','/','J','o','u','e','u','r',i + '0','.','t','x','t','\0'};
	for (i = 0; i < 8; i++){
		s[11] = i + '0';
		if(j.numero == i)
			f = SE_ouverture(s,O_CREAT|ADD);
	}
	for(i = 0; i < j.main.sommet; i++){// écrit toutes les cartes de la main + voir si <=
		ecrire_carte(f,j.main.tab[i]);
	}
	
	ecrireEntier(f,j.score);
	for(i = 0; i < banque.sommet; i++){// écrit toutes les cartes de la banque
		ecrire_carte(f,banque.tab[i]);
	}
	ecrireEntier(f,totalBanque);
	ecrireEntier(f,j.mise);
	ecrireEntier(f,j.score);// à remplacer par le gain
	ecrireEntier(f,j.nbJetons);
	
	
	SE_fermeture(f);
}


