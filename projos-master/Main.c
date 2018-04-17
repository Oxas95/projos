#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "deck.h"
#include "banque.h"

//for(i = 0; i < jeu.nbJoueur; i++)		printf("numero : %d\tnbJetons : %d\tscore : %d\tmise : %d\tvalStop : %d\tobJeton : %d\n\n",j[i].numero,j[i].nbJetons,j[i].score,j[i].mise,j[i].valStop,j[i].objJetons);


int main(int argc,char*argv[] ){
	int a,i;
	Plateau jeu = init_jeu();	//recupere les données du plateau
	viderFichier(jeu.nbJoueur);
	Joueur j[jeu.nbJoueur]; init_joueurs(j,jeu.nbJoueur);
	pid_t bank_pid=getpid();
	pid_t pid[jeu.nbJoueur];
	int ecriture[jeu.nbJoueur][2];	
	int lecture[jeu.nbJoueur][2];	
	for(a = 0; a < jeu.nbJoueur; a++){
		if(pipe(lecture[a]) == -1){ //crée les tubes
			exit(3);
		}
		if(pipe(ecriture[a]) == -1){ //crée les tubes
			exit(3);
		}
	}
	
	for(i = 0; i < jeu.nbJoueur; i++){  //crée les processus
			if((pid[i] = fork()) == 0){
				action_joueurs(j[i],lecture[i],ecriture[i],jeu.nbMains);
				exit(0);
			}
				
		}
	
	action_banque(ecriture,lecture,jeu);
	for(i = 0; i < jeu.nbJoueur; i++)
		wait(NULL);
	
	for(i=0; i < jeu.nbJoueur; i++){
	close(lecture[i][0]);
	close(lecture[i][1]);
	close(ecriture[i][0]);
	close(ecriture[i][1]);
	


	}
	exit(0);
	
}

	

