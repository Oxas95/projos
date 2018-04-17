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
	
	if(SE_lectureEntier2(f,&p.nbJoueur,&c) < 1)exit(1);
	if(SE_lectureEntier2(f,&p.nbDecks,&c) < 1)exit(1);
	if(SE_lectureEntier2(f,&p.nbMains,&c) < 1)exit(1);
	
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
		if((SE_lectureEntier2(f,&(j[i].nbJetons),&c) < 1))exit(101);
		if((SE_lectureEntier2(f,&(j[i].mise),&c) < 1))exit(1);
		switch(c){
			case ';' : j[i].typeMise = CSTE;		break;
			case '+' : j[i].typeMise = CROISSANT;	break;
			case '-' : j[i].typeMise = DESCENDANT;	break;
			default  : j[i].typeMise = CSTE;		break;
		}
		if(j[i].typeMise != CSTE) SE_lectureCaractere(f,&c);
		if(SE_lectureEntier2(f,&(j[i].valStop),&c) < 1)exit(1);
		if(SE_lectureEntier2(f,&(j[i].objJetons),&c) < 1)exit(1);
		j[i].numero = i;
		j[i].score = 0;
		j[i].fluctuation=0;	
		j[i].mise_base=j[i].mise;
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
	int val=value%13;
	if(val==0) SE_ecritureCaractere(f,'A');
	else if(val==9)SE_ecritureCaractere(f,'X');
	else if(val==10) SE_ecritureCaractere (f,'J');
	else if(val==11) SE_ecritureCaractere (f,'Q');
	else if(val==12) SE_ecritureCaractere (f,'K');
	else ecrire_numero_carte(f,value);

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
			f = SE_ouverture(s,ADD);
	}
	for(i = 0; i < j.main.sommet; i++){// écrit toutes les cartes de la main + voir si <=
		ecrire_carte(f,j.main.tab[i]);
	}
	SE_ecritureCaractere(f,';');
	ecrireEntier(f,j.score);
	SE_ecritureCaractere(f,';');
	for(i = 0; i < banque.sommet; i++){// écrit toutes les cartes de la banque
		ecrire_carte(f,banque.tab[i]);

	}
	SE_ecritureCaractere(f,';');	
	ecrireEntier(f,totalBanque);
	SE_ecritureCaractere(f,';');
	ecrireEntier(f,j.mise);
	SE_ecritureCaractere(f,';');
	ecrireEntier(f,j.gain);// à remplacer par le gain
	SE_ecritureCaractere(f,';');
	ecrireEntier(f,j.nbJetons);
	SE_ecritureCaractere(f,';');
	SE_ecritureCaractere(f,'\n');
	SE_fermeture(f);
}

void viderFichier(int nb)
{
	int i;
	for(i=0;i<nb;i++)
	{
		char s[40] = {'t','o','u','r','/','J','o','u','e','u','r',i + '0','.','t','x','t','\0'};
		unlink(s);
		
		}

	}
