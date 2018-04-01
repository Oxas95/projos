#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "deck.h"
#include "lire_ecrire.h"

Joueur jouer(Joueur j,int pipefd[]){
	int buf;
	read(pipefd[0],&buf,1);
	if(j.score < j.valStop){
			
	}
	return j;
}

int miseCroissante(Joueur j){
	if(j.fluctuation == 1 && j.nb_jeton >= j.mise_prec * 2)
		return j.mise_prec * 2;
	
	else if(j.nb_jeton >= j.mise){
		return j.mise;
	}
	
	else return j.nb_jeton;
}

int miseDescendante(Joueur j){
	if(j.fluctuation == 0 && j.nb_jeton >= j.mise_prec / 2)
		return j.mise_prec / 2;
	
	else return j.mise;
}

int Mise(Joueur j){
	
	if (j.typeMise == CROISSANT){
		return miseCroissante(j);
	}
	
	else if (j.typeMise == DESCENDANT){
		return miseDescendante(j);
	}
	
	else if (j.typeMise == CSTE){
		return j.mise;
	}
	
	else {
		exit(3); // faire ecrire message pour mise inexistante
	}
	
}
