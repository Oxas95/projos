#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "deck.h"
#include "joueur.h"
#include "lire_ecrire.h"

Joueur jouer(Joueur j,int pipefd[])
{
	int buf;
	read(pipefd[0],&buf,1);
	
	
	
	return j;}

Joueur init_joueur(Joueur j,int fd)
{

	j.nb_jeton=lire_entier(fd);
	j.mise=lire_entier(fd);
	j.typeMise=lire_entier(fd); // remplacer par lire char ?
	j.valStop=lire_entier(fd);
	j.objJetons=lire_entier(fd);
	j.action=0;
	return j;
	}

int miseConstante(Joueur j)
{return j.mise;}

int miseCroissante(Joueur j)
{
	if(j.fluctuation==1&& j.nb_jeton>=j.mise_prec*2)
	return j.mise_prec*2;
	
	else if(j.nb_jeton>= j.mise)
	{ return j.mise;}
	
	else return j.nb_jeton;
	}

int miseDescendante(Joueur j)
{
	if(j.fluctuation==0&&j.nb_jeton>=j.mise_prec/2)
	return j.mise_prec/2;
	
	else return j.mise;
}

