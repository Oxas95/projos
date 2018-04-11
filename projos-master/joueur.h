#define PIOCHER 200
#define RESTER 201
#define BLACKJACK 221

#include <sys/types.h>
#include <unistd.h>

typedef enum{
	CSTE,
	CROISSANT,
	DESCENDANT
}Type_de_mise;

typedef struct{
	int tab[21]; // une main ne pourra pas excéder 21 cartes
	int sommet;

}Main;

Main init_main();


typedef struct{
	pid_t pid;
	int numero;
	Main main;
	int nbJetons;
	int score;
	int mise;
	int mise_base;
	Type_de_mise typeMise; 
	int valStop;
	int objJetons;
	int action; //PIOCHER ou RESTER 
	int fluctuation; //0 si a perdu au dernier tour, 1 si a gagné
}Joueur;

Joueur jouer(Joueur j,int ecriture[], int lecture[]);
	
void Mise(Joueur *j);

void action_joueurs(Joueur j, int ecriture[2], int lecture[2], int nbMains);

int calculScore(const int value, int *score, int *cpt);
