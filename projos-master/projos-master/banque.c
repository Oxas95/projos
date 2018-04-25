#include <stdlib.h>
#include <stdio.h>
#include "banque.h"


static inline void init_tableau(int *tab,int taille, int val){
	for(int i = 0;i < taille;i++){
		tab[i] = val;
	}
}

Banque init_Banque(Plateau jeu){
	Banque b;
	deck_t *deck = initDeck(P52,jeu.nbDecks);
	b.d = *deck;
	b.score = 0;
	return b;
}

void remplirDeck(deck_t *d){
	card_t *tmp = d->drawPile;
	d->drawPile = d->discardPile;
	d->discardPile = tmp;
}

int prendreCarteDeck(deck_t *d){
	if(getDrawPileSize(d) == 0){
		remplirDeck(d);
		shuffleDeck(d);
	}
	if(getDrawPileSize(d) == 0) exit(10);
	return drawCard(d);
}

void discardAll(deck_t *d){
	while(d->handCards != NULL){
		discardCard(d,d->handCards->value);
	}
		
}

void decaleTableauPipe(int(*ecriture)[2],int (*lecture)[2],int joueur,int nbJoueur){
	for(int i = joueur; i < nbJoueur - 1 ; i++){
		ecriture[i][0]=ecriture[i+1][0];ecriture[i][1]=ecriture[i+1][1];
		lecture[i][0]=lecture[i+1][0];lecture[i][1]=lecture[i+1][1];
	}

}

void action_banque(int(*ecriture)[2],int(*lecture)[2],Plateau jeu){
	initDeckLib();
	Banque b = init_Banque(jeu);
	int mise[jeu.nbJoueur]; int continuer[jeu.nbJoueur];
	int score[jeu.nbJoueur];
	int blackjack[jeu.nbJoueur];
	shuffleDeck(&b.d);
	int i,j,carte, action,cpt,fin = 1;
	
	for (i = 0; i < jeu.nbMains && fin; i++){
		
		init_tableau(blackjack,jeu.nbJoueur,0);
		b.main = init_main(); 
		init_tableau(score,jeu.nbJoueur,0);
		init_tableau(mise,jeu.nbJoueur,0);
		init_tableau(continuer,jeu.nbJoueur,1);
		cpt = 0; b.score = 0;
		
		for (j = 0; j < jeu.nbJoueur; j++){ //chaque joueur mise et la banque recoit la mise
			print("recuperation mise\n");
			if(continuer[j])read(lecture[j][0],mise + j,sizeof(int));
		}
		for (j = 0; j < jeu.nbJoueur ; j++){ //la banque envoie 1 carte a chaque joueur
			carte = prendreCarteDeck(&b.d);
			print("envoi carte 1\n");
			if(continuer[j])write(ecriture[j][1],&carte,sizeof(int));
		}
		for (j = 0; j < jeu.nbJoueur ; j++){ //la banque envoie une 2eme carte a chaque joueur
			carte = prendreCarteDeck(&b.d);
			print("envoi carte 2\n");
			if(continuer[j])write(ecriture[j][1],&carte,sizeof(int));
		}
		
		//La Banque pioche deux cartes
		b.main.tab[b.main.sommet++] = prendreCarteDeck(&b.d);
		calculScore(b.main.tab[b.main.sommet - 1],&b.score,&cpt);
		b.main.tab[b.main.sommet++] = prendreCarteDeck(&b.d); //ajout des 2 carte a la banque
		calculScore(b.main.tab[b.main.sommet - 1],&b.score,&cpt);
		
		//La banque fait le tour des joueurs et interagit avec eux
		for (j = 0; j < jeu.nbJoueur; j++){ //chaque joueur demande a piocher ou rester
			if(continuer[j]){
				print("un joueur joue, interaction avec banque\n");
				do{
					print("lecture action\n");
					read(lecture[j][0],&action,sizeof(int));
					if(action == PIOCHER){
						carte = prendreCarteDeck(&b.d);
						print("piocher lue, envoie carte\n");print("carte envoyé : ");printCard(carte); print("\n");
						write(ecriture[j][1],&carte,sizeof(int));
					}		
				}while(action == PIOCHER);
				
				print("rester/blackjack lue\n");
				if(action == BLACKJACK) blackjack[j] = 1;
				//recevoir score
				read(lecture[j][0],&score[j],sizeof(int));
			}
		}
		//La banque complète sa main
		b = jouerBanque(b,&cpt);
		
		print("calcul gains\n");
		if(b.main.sommet == 2 && b.score == 21){ //si la banque fais blackjack
			print("la banque a blackjack\n");
			for(j = 0; j < jeu.nbJoueur; j++){
				if(blackjack[j] != 1) mise[j] = 0; //tout ceux qui n'ont pas fais blackjack ont perdu
			}
		}
		else if(b.score > 21){ //si la banque a perdu
			print("la banque a perdu\n");
			for(j = 0; j < jeu.nbJoueur; j++){
				if (blackjack[j] == 1) mise[j] *= 3; //si un joueur fais blackjack il gagne le triple 
				else if(score[j] < 22) mise[j] *= 2; //tout ceux qui n'ont pas perdu gagne le double de leur mise
				else mise[j] = 0; //ceux qui ont perdu perdent leur mise 
			}
		}
		
		else if(b.score < 22 && b.score > 16){ //si la banque atteint 17 ou + sans perdre
			print("la banque n'a pas perdu\n");
			for(j = 0; j < jeu.nbJoueur; j++){
				if(score[j] < 22 && score[j] > b.score) mise[j] *= 2; //tout ceux qui n'ont pas perdu et vaincu la banque gagne le double de leur mise
				else if (blackjack[j] == 1) mise[j] *= 3; //si un joueur fais blackjack il gagne le triple 
				else if(score[j] == b.score); //si la banque fais egalité avec le joueur il recupere sa mise 
				else  mise[j] = 0; //ceux qui ont perdu perdent leur mise
			}
		}
		
		//envoi mise aux joueurs
		print("envoi des gains aux joueurs\n");
		for(j = 0; j < jeu.nbJoueur; j++) {
			if(continuer[j])write(ecriture[j][1],&mise[j],sizeof(int));
		}
		
		//transfert ses resultats de partie
		print("envoi des resultats de la partie (score banque etc...)\n");
		for(j = 0; j < jeu.nbJoueur; j++){
			if(continuer[j]){
				write(ecriture[j][1],&b.main,sizeof(Main));
				write(ecriture[j][1],&b.score,sizeof(int));
			}
		}
		
		print("cartes utilisés mis en défausse\n");
		discardAll(&b.d);
		
		fin = 0;
		for(j = 0;j < jeu.nbJoueur; j++){
			read(lecture[j][0],&continuer[j],sizeof(int));
			fin += continuer[j];
		}
	}
	
	//il y a un problème de pointeur quand l'on souhaite libérer la mémoire d'un deck
	//removeDeck(&b.d);
}

Banque jouerBanque(Banque banque,int * cpt){
	int carte;
	while(banque.score < 17){
		carte = prendreCarteDeck(&banque.d);
		banque.main.tab[banque.main.sommet++] = carte;
		calculScore(banque.main.tab[banque.main.sommet - 1],&banque.score,cpt);
	}
	return banque;
}
