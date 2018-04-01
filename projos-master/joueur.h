#define PIOCHER 200
#define RESTER 201

#include <sys/types.h>
#include <unistd.h>

typedef enum{
	CSTE;
	CROISSANT;
	DESCENDANT;
}Type_de_mise;

typedef struct{
	pid_t pid;
	int main[20];
	int nb_jeton;
	int score;
	int mise;
	int mise_prec;
	Type_de_mise typeMise; 
	int valStop;
	int objJetons;
	int action; //PIOCHER ou RESTER 
	int fluctuation; //0 si a perdu au dernier tour, 1 si a gagné
}Joueur;

Joueur jouer(Joueur j,int* pipefd);
	
int Mise(Joueur j);
