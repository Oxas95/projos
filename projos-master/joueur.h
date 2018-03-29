#define PIOCHER 200
#define RESTER 201
#define CROISSANT '+'
#define DESCENDANT '-'
#define CSTE '*'

#include <sys/types.h>
#include <unistd.h>

typedef struct{
	pid_t pid;
	int main[20];
	int nb_jeton;
	int score;
	int mise;
	int mise_prec;
	char typeMise; //0 pour constant,1 pour croissant, 2 pour descendante
	int valStop;
	int objJetons;
	int action; //PIOCHER ou RESTER 
	int fluctuation; //0 si a perdu au dernier tour, 1 si a gagné
	}Joueur;
	
	Joueur jouer(Joueur j,int* pipefd);
	Joueur init_joueur(Joueur j,int fd);
	int Mise(Joueur j);
