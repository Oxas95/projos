#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "deck.h"
#include "banque.h"

int main(int argc,char*argv[] ){
	int a,i;
	Plateau jeu = init_jeu();	//recupere les données du plateau
	viderFichier(jeu.nbJoueur);
	Joueur j[jeu.nbJoueur]; init_joueurs(j,jeu.nbJoueur);
	int ecriture[jeu.nbJoueur][2];	
	int lecture[jeu.nbJoueur][2];	
	for(i = 0; i < jeu.nbJoueur; i++){
		if(pipe(lecture[i]) == -1){ //crée les tubes
			exit(1);
		}
		if(pipe(ecriture[i]) == -1){ //crée les tubes
			exit(1);
		}
	}
	
	for(i = 0; i < jeu.nbJoueur; i++){  //crée les processus
		do{
			a = fork();
		}while(a == -1);
		if(a == 0){
			action_joueurs(j[i],lecture[i],ecriture[i],jeu.nbMains);
			print("joueur a quitté\n");
			exit(0);
		}
				
	}
	
	action_banque(ecriture,lecture,jeu);
	for(i = 0; i < jeu.nbJoueur; i++)
		wait(NULL);
	
	for(i = 0; i < jeu.nbJoueur; i++){
		close(lecture[i][0]);
		close(lecture[i][1]);
		close(ecriture[i][0]);
		close(ecriture[i][1]);
	}
	print("banque a quitté\n");
	exit(0);
	
}

	

