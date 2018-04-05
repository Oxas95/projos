#include "lire_ecrire.h"
#include "deck.h"
typedef struct {
	pid_t pid;
	int main[20];
	deck_t deck;
	int score;
}Banque;

void action_banque(int(*pipefd)[2],Plateau jeu);
