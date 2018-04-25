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
	while(string[cpt] != '\0')cpt++;
	return cpt;
}

void print(const char* string){ 
	int fd = STDOUT_FILENO;
	write(fd,string,taille_chaine(string));
}

static inline void ecrire_numero_carte(SE_FICHIER f,const int value){
	int i = (value % 13) + 1;
	SE_ecritureCaractere(f,i + '0');
}

void ecrire_carte(SE_FICHIER f,const int value) {
	//if (value == 52) { print ("J*"); return; }
	int val = value % 13;
	if(val == 0) SE_ecritureCaractere(f,'A');
	else if(val == 9)SE_ecritureCaractere(f,'X');
	else if(val == 10) SE_ecritureCaractere (f,'J');
	else if(val == 11) SE_ecritureCaractere (f,'Q');
	else if(val == 12) SE_ecritureCaractere (f,'K');
	else ecrire_numero_carte(f,value);

}

char* nomFic(int val){
	int nombreChiffreVal = nombreChiffre(val);
	char* s = malloc((17 + nombreChiffreVal) * sizeof(char));
	char* nombre = itoa(val);
	s[0] = 't',s[1] = 'o',s[2] = 'u',s[3] = 'r',s[4] = '/',s[5] = 'J',s[6] = 'o',
	s[7] = 'u',s[8] = 'e',s[9] = 'u',s[10] = 'r',s[12 + nombreChiffreVal - 1] = '.',
	s[13 + nombreChiffreVal - 1] = 't',s[14 + nombreChiffreVal - 1] = 'x',
	s[15 + nombreChiffreVal - 1] = 't',s[16 + nombreChiffreVal - 1] = '\0';
	for(int i = 0; i < nombreChiffreVal; i++){
		s[11 + i] = nombre[i];
	}
	
	free(nombre);
	return s;
}

void ecrire_fichier(Joueur j,Main banque,int totalBanque){
	int i = 0; SE_FICHIER f;
	char* s = nomFic(j.numero);
	
	f = SE_ouverture(s,ADD); free(s);
	if(f.descripteur == -1) exit(10);
	for(i = 0; i < j.main.sommet; i++){// écrit toutes les cartes de la main + voir si <=
		ecrire_carte(f,j.main.tab[i]);
	}
	SE_ecritureCaractere(f,';');
	SE_ecritureEntier(f,j.score);
	SE_ecritureCaractere(f,';');
	for(i = 0; i < banque.sommet; i++){// écrit toutes les cartes de la banque
		ecrire_carte(f,banque.tab[i]);

	}
	SE_ecritureCaractere(f,';');	
	SE_ecritureEntier(f,totalBanque);
	SE_ecritureCaractere(f,';');
	SE_ecritureEntier(f,j.mise);
	SE_ecritureCaractere(f,';');
	SE_ecritureEntier(f,j.gain);// à remplacer par le gain
	SE_ecritureCaractere(f,';');
	SE_ecritureEntier(f,j.nbJetons);
	SE_ecritureCaractere(f,';');
	SE_ecritureCaractere(f,'\n');
	SE_fermeture(f);
}

void viderFichier(int nbJoueur){
	int i;
	char *s = NULL;
	for(i = 0;i < nbJoueur; i++){
		s = nomFic(i);
		unlink(s);
		free(s); s = NULL;
	}
}
