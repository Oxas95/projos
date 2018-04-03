#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "deck.h"
#include "lire_ecrire.h"

void action_joueurs(Joueur j, int pipefd[2], int nbMains){
	int i,k;
	for (i = 0; i < nbMains; i++){
		mise(&j);
		j.nbJetons -= j.mise;
		write(pipefd[0],&j.mise,sizeof(int));
		
		for (k = 0; k < 21; k++)//initialisation de la main a vide
			j.main.tab[k] = 0;
		j.main.sommet = 0;
		
		read(pipefd[1],&j.main.tab[j.main.sommet++],sizeof(int)); //recuperation de la 1ere carte
		read(pipefd[1],&j.main.tab[j.main.sommet++],sizeof(int)); //recuperation de la 2eme carte
		
		j = jouer(j, pipefd);
		
		
	}
}

Joueur jouer(Joueur j,int pipefd[]){
	int carte;
	while(j.score < j.valStop){
		j.action = PIOCHER;
		write(pipefd[0],&j.action,sizeof(int)); // envoie son choix
		read(pipefd[1],&j.main.tab[sommet++],sizeof(int)); //reçois la carte
	}
	
	j.action = RESTER;
	write(pipefd[0],&j.action,sizeof(int)); // envoie son choix
	
	return j;
}

int miseCroissante(Joueur j){
	if(j.fluctuation == 0){
		return (j.mise_base > j.nbJetons)? j.nbJetons : j.mise_base;
	}
	else return (j.mise * 2 > j.nbJetons)? j.nbJetons : j.mise *2 ;
}

int miseDescendante(Joueur j){
	if(j.fluctuation == 0){
		return (j.mise_base > j.nbJetons)? j.nbJetons : j.mise_base;
	}
	else return (j.mise / 2 > j.nbJetons)? j.nbJetons : j.mise / 2;
}

void Mise(Joueur* j){
	
	if (j->typeMise == CROISSANT){
		j->mise = miseCroissante(*j);
	}
	
	else if (j->typeMise == DESCENDANT){
		j->mise = miseDescendante(*j);
	}
	
	else if (j->typeMise == CSTE){
		j->mise (j.mise > j.nbJetons)? j.nbJetons : j.mise;
	}
	
	else {
		exit(3); // faire ecrire message pour mise inexistante
	}
	
}
