#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "deck.h"
#include "lire_ecrire.h"
#include "banque.h"


int main(int argc,char*argv[] ){	
	Plateau jeu = init_plateau();	//recupere les données du plateau
	Joueur j[jeu.nbJoueur]; init_joueurs(j,jeu.nbJoueur);
	pid_t bank_pid=getpid();
	pid_t pid[4];
	int pipefd[8][2];	
	for(int a = 0; a < 4; a++){
		if(pipe(pipefd[a]) == -1){ //crée les tubes
			exit(3);
		}
	}
	
	pid[0] = fork();
	for(int i = 1; i < 4; i++){  //crée les processus
		if(pid[i-1]){
			pid[i] = fork();
		}
	}
	
	if(getpid() == bank_pid){ // si on est dans la banque, on crée un deck et on mélange
	
		for(int i = 0; i < jeu.nbJoueur; i++){ //met en pause tous les processus
			kill(pid[i],SIGSTOP);
		}
	}
	
	
	/*			joueur1.pid=fork();
	if(joueur1.pid) joueur2.pid=fork();
	if(joueur2.pid) joueur3.pid=fork();
	if(joueur3.pid) joueur4.pid=fork();
	
	if
	initDeckLib();
	deck_t *deck ;
	int carte;
	deck=initDeck(P32,2);
	shuffleDeck(deck);
	
	joueur1.main[0]=drawCard((deck));joueur1.main[1]=drawCard((deck));
	joueur2.main[0]=drawCard((deck));joueur2.main[1]=drawCard((deck));
	joueur3.main[0]=drawCard((deck));joueur3.main[1]=drawCard((deck));
	joueur4.main[0]=drawCard((deck));joueur4.main[1]=drawCard((deck));
	
	
printCard((carte = drawCard(deck)));
	
	

	
	1er choix			
	 
	 
	 child_pid=fork();
	for(int i =0;(i<3&&child_pid);i++) // Boucle qui crée les processus fils en s'assurant d'être dans le père
		{
			
			child_pid=fork();
			
			}
	
		if (child_pid==0)
		{
		* jouer(getpid());
		* 
		* 
		* 
		* }
	
	
	
	
	
	
	

	2e choix
	while(1)
{	
	if (getpid()==joueur1.pid){jouer(joueur1,pipefd1);}
	else if (getpid()==joueur2.pid){jouer(joueur2,int pipefd2);}
	else if (getpid()==joueur3.pid){jouer(joueur3,int pipefd3);}
	else if (getpid()==joueur4.pid){jouer(joueur4,int pipefd4);}
	else 
	{
		if (joueur1.action==PIOCHER )
			{
			 joueur1.main=drawCard(deck);
			 }

		if (joueur2.action==PIOCHER )
			{
			 joueur2.main=drawCard(deck);
			 }
	
		if (joueur3.action==PIOCHER )
			{
			 joueur3.main=drawCard(deck);
			 }
	
		if (joueur4.action==PIOCHER )
			{
			 joueur4.main=drawCard(deck);
			 }
	}
	
	
	 
}


	
	
	
		removeDeck(deck);
	
	*/
	exit(0);
}
