#include "joueur.h"

typedef struct {
	int nbJoueur,nbDecks,nbMains;
	Joueur* joueur;
} Plateau;

Plateau init_jeu();

int lire_entier(int fd);

void ecrire_fichier();
