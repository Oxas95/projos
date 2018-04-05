#include <stdlib.h>
#include <stdio.h>
#include "deck.h"
#include "banque.h"


void init_tableau(int *tab,int taille)
{
	int i=0;
	for(i=0;i<taille;i++){
	
	tab[i]=0;
	
	}
}



void action_banque(int(*pipefd)[2],Plateau jeu){
	initDeckLib();
	deck_t* d;
	d=initDeck(P52,jeu.nbDecks);
	shuffleDeck(d);
	int i,j,carte, action;
	int mise[jeu.nbJoueur] ;init_tableau(mise,jeu.nbJoueur);
	Main b; //init main
	for (i = 0; i < 21; i++){
		b.tab[i] = 0;
	}
	b.sommet = 0;
	
	
	
	for (i = 0; i < jeu.nbMains; i++){
		for (j = 0; j < jeu.nbJoueur; j++){ //chaque joueur mise et la banque recoit la mise
			read(pipefd[j][1],mise + j,sizeof(int));
		}
		for (j = 0; j < jeu.nbJoueur ; j++){ //la banque envoie 1 cartes a chaque joueur
			carte = drawCard(d);
			write(pipefd[j][0],&carte,sizeof(int));
		}
		for (j = 0; j < jeu.nbJoueur ; j++){ //la banque envoie une 2eme cartes a chaque joueur
			carte = drawCard(d);
			write(pipefd[j][0],&carte,sizeof(int));
		}
		
		carte = drawCard(d);	b.tab[b.sommet++] = carte;
		carte = drawCard(d);	b.tab[b.sommet++] = carte; //ajout des 2 carte a la banque
		
		for (j = 0; j < jeu.nbJoueur; j++){ //chaque joueur demande a piocher ou rester
			read(pipefd[j][1],&action,sizeof(int));
			
			while(action == PIOCHER){
				read(pipefd[j][1],&action,sizeof(int));
				if(action == PIOCHER){
					carte = drawCard(d);
					write(pipefd[j][0],&carte,sizeof(int));
				}		
			}
			
		}
		
		
		
		
		
		
	}
	
}

Banque jouerBanque(Banque banque){
	
	
	
	return banque;
}



