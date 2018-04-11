#include <stdlib.h>
#include <stdio.h>
#include "banque.h"


static inline void init_tableau(int *tab,int taille){
	for(int i = 0;i < taille;i++){
		tab[i] = 0;
	}
}

Banque init_Banque(Plateau jeu){
	Banque b;
	b.main = init_main();
	deck_t *deck = initDeck(P52,jeu.nbDecks);
	b.d = *deck;
	b.score = 0;
	return b;
}

int prendreCarteDeck(deck_t *d){
	if(getDrawPileSize(d) == 0) shuffleDeck(d);
	return drawCard(d);
}

void discardAll(deck_t *d){
	
}

void action_banque(int(*ecriture)[2],int(*lecture)[2],Plateau jeu){
	initDeckLib();
	Banque b = init_Banque(jeu);
	
	int mise[jeu.nbJoueur];
	int score[jeu.nbJoueur];
	int blackjack[jeu.nbJoueur];
	shuffleDeck(&b.d);
	int i,j,carte, action;
	for (i = 0; i < jeu.nbMains; i++){
		init_tableau(blackjack,jeu.nbJoueur);
		
		for (j = 0; j < jeu.nbJoueur; j++){ //chaque joueur mise et la banque recoit la mise
			print("recuperation mise\n");
			read(lecture[j][0],mise + j,sizeof(int));
		}
		for (j = 0; j < jeu.nbJoueur ; j++){ //la banque envoie 1 carte a chaque joueur
			carte = prendreCarteDeck(&b.d);
			print("envoi carte 1\n");
			write(ecriture[j][1],&carte,sizeof(int));
		}
		for (j = 0; j < jeu.nbJoueur ; j++){ //la banque envoie une 2eme carte a chaque joueur
			carte = prendreCarteDeck(&b.d);
			print("envoi carte 2\n");
			write(ecriture[j][1],&carte,sizeof(int));
		}
		
		b.main.tab[b.main.sommet++] = prendreCarteDeck(&b.d);
		b.main.tab[b.main.sommet++] = prendreCarteDeck(&b.d); //ajout des 2 carte a la banque
		
		for (j = 0; j < jeu.nbJoueur; j++){ //chaque joueur demande a piocher ou rester
			print("jouer des joueurs (banque)\n");
			do{
				print("lecture action\n");
				read(lecture[j][0],&action,sizeof(int));
				if(action == PIOCHER){
					carte = prendreCarteDeck(&b.d);
					print("piocher lue, envoie carte\n");
					write(ecriture[j][1],&carte,sizeof(int));
				}		
			}while(action == PIOCHER);
			print("rester/blackjack lue\n");
			if(action == BLACKJACK) blackjack[i] = 1;
			
			//recevoir score
		}
		
		b = jouerBanque(b);
		
		print("calcul gains\n");
		printf("score banque : %d\n",b.score);
		
		if(b.main.sommet == 2 && b.score == 21){ //si la banque fais blackjack
			print("la banque a blackjack\n");
			for(j = 0; j < jeu.nbJoueur; j++){
				if(blackjack[j] != 1) mise[j] = 0; //tout ceux qui n'ont pas fais blackjack ont perdu
			}
		}
		else if(b.score > 21){ //si la banque a perdu
			print("la banque a perdu\n");
			for(j = 0; j < jeu.nbJoueur; j++){
				if (blackjack[i] == 1) mise[i] *= 3; //si un joueur fais blackjack il gagne le triple
				else if(score[i] < 22) mise[j] *= 2; //tout ceux qui n'ont pas perdu gagne le double de leur mise
				else mise[i] = 0; //ceux qui ont perdu perdent leur mise
			}
		}
		
		else if(b.score < 22 && b.score > 16){ //si la banque atteint 17 ou + sans perdre
			print("la banque n'a pas perdu\n");
			for(j = 0; j < jeu.nbJoueur; j++){
				if(score[i] < 22 && score[i] > b.score) mise[j] *= 2; //tout ceux qui n'ont pas perdu et vaincu la banque gagne le double de leur mise
				else if (blackjack[i] == 1) mise[i] *= 3; //si un joueur fais blackjack il gagne le triple
				else if(score[i] == b.score); //si la banque fais egalité avec le joueur il recupere sa mise
				else  mise[i] = 0; //ceux qui ont perdu perdent leur mise
				printf("%d %d %d\n",score[i] < 22 && score[i] > b.score,blackjack[i] == 1,score[i] == b.score);
			}
			
		}
		
		//envoi mise aux joueurs
		print("envoi des gains aux joueurs\n");
		for(j = 0; j < jeu.nbJoueur; j++) printf("gain du joueur %d : %d\n",j,mise[j]);
		
		//transfert ses resultats de partie
		print("envoi des resultats de la partie (score banque etc...)\n");
		
		print("cartes utilisés mis en défausse\n");
		//discardAll
		exit(0); // a virer !!
	}
	
}

Banque jouerBanque(Banque banque){
	int cpt = 0;
	int carte;
	while(banque.score < 17){
		carte = prendreCarteDeck(&banque.d);
		banque.main.tab[banque.main.sommet++] = carte;
		calculScore(banque.main.tab[banque.main.sommet - 1],&banque.score,&cpt);
	}
	return banque;
}
