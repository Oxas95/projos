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
		if((SE_lectureEntier(f,&(j[i].nbJetons)) < 1))exit(1);
		
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

void print(const char* string){ 

	int fd = STDOUT_FILENO;
	write(fd,string,taille_chaine(string));
}
void ecrire_numero_carte(SE_FICHIER f,const int value)
{
	int i=(value%13)+1;
	if(i==1) SE_ecritureCaractere(f,'1');
	if(i==2) SE_ecritureCaractere(f,'2');
	if(i==3) SE_ecritureCaractere(f,'3');
	if(i==4) SE_ecritureCaractere(f,'4');
	if(i==5) SE_ecritureCaractere(f,'5');
	if(i==6) SE_ecritureCaractere(f,'6');
	if(i==7) SE_ecritureCaractere(f,'7');
	if(i==8) SE_ecritureCaractere(f,'8');
	if(i==9) SE_ecritureCaractere(f,'9');
	
	}

void ecrire_carte(SE_FICHIER f,const int value) {
	//if (value == 52) { print ("J*"); return; }
	switch (value % 13) {
		case 0: SE_ecritureCaractere(f,'A'); break;
		case 9: SE_ecritureCaractere(f,'X'); break;
		case 10: SE_ecritureCaractere (f,'J'); break;
		case 11: SE_ecritureCaractere (f,'Q'); break;
		case 12: SE_ecritureCaractere (f,'K'); break;
		default: ecrire_numero_carte(f,value);
	}

}

void ecrire_fichier(Joueur j,Main banque,int totalBanque )
{
	int i; SE_FICHIER f;
	if(j.numero==0)
		f=SE_ouverture("Joueur0.txt",ADD);
	if(j.numero==0)
		f=SE_ouverture("Joueur1.txt",ADD);
	if(j.numero==0)
		f=SE_ouverture("Joueur2.txt",ADD);
	if(j.numero==0)
		f=SE_ouverture("Joueur3.txt",ADD);
	if(j.numero==0)
		f=SE_ouverture("Joueur4.txt",ADD);
	if(j.numero==0)
		f=SE_ouverture("Joueur5.txt",ADD);
	if(j.numero==0)
		f=SE_ouverture("Joueur6.txt",ADD);
	if(j.numero==0)
		f=SE_ouverture("Joueur7.txt",ADD);
	for(i=0;i<j.main.sommet;i++)// écrit toutes les cartes de la main + voir si <=
	{
		ecrire_carte(f,j.main.tab[i]);
		}
	

	
	
	
	SE_fermeture(f);
	}


