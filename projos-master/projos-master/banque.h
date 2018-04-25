#include "lire_ecrire.h"
#include "deck.h"

typedef struct {
	Main main;
	deck_t *d;
	int score;
}Banque;

void action_banque(int(*ecriture)[2], int(*lecture)[2],Plateau jeu);

Banque jouerBanque(Banque banque,int * cpt);
