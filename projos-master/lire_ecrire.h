#include "joueur.h"

typedef struct {
	int nbJoueur,nbDecks,nbMains;
} Plateau;

Plateau init_jeu();

void init_joueurs(Joueur j[], int taille_tab);

void print(const char* string);

void ecrire_fichier(Joueur j,Main banque,int totalBanque);
