#include <stdlib.h>
#include <stdio.h>
#include "deck.h"
#include "banque.h"
#include "joueur.h"

void action_banque(int** pipefd,Plateau jeu){
	initDeckLib();
	deck_t* d;
	d=initDeck(P52,jeu.nbDecks);
	shuffleDeck(d);
	int i,j,carte, mise[jeu.nbJoueur] = {0}, action;
	
	Main b; //init main
	for (i = 0; i < 21; i++){
		b.tab[i] = 0;
	}
	sommet = 0;
	
	
	
	for (i = 0; i < jeu.nbMains; i++){
		for (j = 0; j < nbJoueur; j++){ //chaque joueur mise et la banque recoit la mise
			read(pipefd[j][1],mise + j,sizeof(int));
		}
		for (j = 0; j < ; j++){ //la banque envoie 1 cartes a chaque joueur
			carte = drawCard(d);
			write(pipefd[j][0],&carte,sizeof(int));
		}
		for (j = 0; j < ; j++){ //la banque envoie une 2eme cartes a chaque joueur
			carte = drawCard(d);
			write(pipefd[j][0],&carte,sizeof(int));
		}
		
		carte = drawCard(d);	b.tab[b.sommet++] = carte;
		carte = drawCard(d);	b.tab[b.sommet++] = carte; //ajout des 2 carte a la banque
		
		for (j = 0; j < nbJoueur; j++){ //chaque joueur demande a piocher ou rester
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
