#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "deck.h"
#include "lire_ecrire.h"
#include "joueur.h"
#include "banque.h"


int main()
{
	int fd1=0,fd2=0,fd3=0,fd4=0;
	pid_t bank_pid=getpid();
	pid_t pid[4];
	//int pipefd1[2],pipefd2[2],pipefd3[2],pipefd4[2]; A rajouter pour faire les pipe
	int pipefd[4][2];
	Joueur joueur1=init_joueur(joueur1,fd1);
	Joueur joueur2=init_joueur(joueur2,fd2);
	Joueur joueur3=init_joueur(joueur3,fd3);
	Joueur joueur4=init_joueur(joueur4,fd4);
	
	for(int a=0;a<4;a++)
	{
		if(pipe(pipefd[a])==-1)
		{

			exit(3);
			}
		
		}
	
	pid[0]=fork();
	for(int i=1;i<4;i++)
	{
		if(pid[i-1])
		{
			pid[i]=fork();
			
			}

		}
	
	if(getpid()==bank_pid) // si on est dans la banque, on crée un deck et on mélange
	{
		initDeckLib();
	int money_bank=0;
	deck_t *deck ;
	int carte;
	deck=initDeck(P32,2);
	shuffleDeck(deck);
		
		for(int i=0;i<4;i++)//pour les quatres joueurs on tire deux cartes et on envoie au pipe leurs valeurs 
			{
				for(int j=0;j<2;j++)
				{
					carte=drawCard(deck);
					write(pipefd[j][1],&carte,sizeof(int));
				}
			
			}
		drawCard(deck);drawCard(deck);//deux cartes pour la banque
		}
	
	// les quatres joueurs jouent c'est-à-dire misent et piochent.Il faudra rajouter une boucle while
	
	if (getpid()==pid[0])
	{
		jouer(joueur1,pipefd[0]);
		
		}
	if (getpid()==pid[1])
	{
		jouer(joueur2,pipefd[1]);
		
		}
		if (getpid()==pid[2])
	{
		jouer(joueur3,pipefd[2]);
		
		}
		if (getpid()==pid[3])
	{
		jouer(joueur4,pipefd[3]);
		
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
