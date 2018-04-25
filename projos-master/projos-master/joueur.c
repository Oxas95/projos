#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "deck.h"
#include "lire_ecrire.h"

Main init_main(){ // initialise la main avec un tableau vide et le sommet à 0;
	Main m;
	int i = 0;
	for(i = 0 ; i < 21; i++){
		m.tab[i] = 0;
	}
	m.sommet = 0;
	return m;
}



void action_joueurs(Joueur j, int ecriture[2], int lecture[2], int nbMains){
	int i,cpt = 0,totalBanque, continuer = 1;
	Main banque;
	

	for (i = 0; (i < nbMains); i++){
		printf("numero : %d\tnbJetons : %d\tscore : %d\tmise : %d\tvalStop : %d\tobJeton : %d\n",j.numero,j.nbJetons,j.score,j.mise,j.valStop,j.objJetons);
		Mise(&j);j.gain = 0;
		j.nbJetons -= j.mise;
		printf("mise\n");
		write(ecriture[1],&j.mise,sizeof(int));
		j.main=init_main();
		printf("recuperation carte 1\n");
		read(lecture[0],&j.main.tab[j.main.sommet++],sizeof(int)); //recuperation de la 1ere carte
		calculScore(j.main.tab[j.main.sommet - 1],&j.score,&cpt);
		printf("recuperation carte 2\n");
		read(lecture[0],&j.main.tab[j.main.sommet++],sizeof(int)); //recuperation de la 2eme carte
		calculScore(j.main.tab[j.main.sommet - 1],&j.score,&cpt);
		printf("jouer\n");
		j = jouer(j, ecriture,lecture,&cpt);
	
		write(ecriture[1],&j.score,sizeof(int));printf("Joueur :%d,score envoyé:%d\n",j.numero,j.score);// les joueurs envoient leurs scores
		read(lecture[0],&j.gain,sizeof(int));j.nbJetons+=j.gain;//récupère les gains
		print("reception du gain\n");
		//récupération résultat banque
		print("reception données de la banque\n");
		read(lecture[0],&banque,sizeof(Main));
		read(lecture[0],&totalBanque,sizeof(int));
		
		//Fin de la main, écriture du fichier 
		ecrire_fichier(j,banque,totalBanque); //mettre les infos de la banque
		j.score = 0; cpt = 0;
		/*if ( j.nbJetons == 0 || j.nbJetons > j.objJetons ){
			continuer = 0;
			write(ecriture[1],&continuer,sizeof(int));
		}*/
		//exit(0); // a virer !!
	}

	close(lecture[0]);
	close(lecture[1]);
	close(ecriture[0]);
	close(ecriture[1]);

}

int calculScore(const int value, int *score, int *cpt) {
	int val = value % 13;
		 if(val == 0) {*score += 11; (*cpt)++;}
	else if(val == 9)  *score += 10;
	else if(val == 10) *score += 10;
	else if(val == 11) *score += 10;
	else if(val == 12) *score += 10;
	else  *score += ((value % 13) + 1);

	if(*score > 21){
		if(*cpt > 0){
			(*cpt)--;
			*score -= 10;
		}
	}
	if(score < 0) exit(5);
	return (*score <= 21);
}

Joueur jouer(Joueur j,int ecriture[], int lecture[],int *cpt){
	while(j.score <= j.valStop){
		printf("Joueur: %d  score : %d\n",j.numero,j.score);
		j.action = PIOCHER;
		print("envoi pioche\n");
		write(ecriture[1],&j.action,sizeof(int)); // envoie son choix
		print("recois carte\n");
		read(lecture[0],&j.main.tab[j.main.sommet++],sizeof(int)); //reçois la carte
		calculScore(j.main.tab[j.main.sommet - 1],&j.score,cpt);
	}
	if(j.main.sommet == 2 && j.score == 21) j.action = BLACKJACK;
	else j.action = RESTER;
	print("envoie rester\n");
	write(ecriture[1],&j.action,sizeof(int)); // envoie son choix
	
	return j;
}

int miseCroissante(Joueur j){
	if(j.fluctuation == 0){
		return (j.mise_base > j.nbJetons)? j.nbJetons : j.mise_base;
	}
	else return (j.mise * 2 > j.nbJetons)? j.nbJetons : j.mise * 2 ;

}

int miseDescendante(Joueur j){
	if(j.fluctuation == 0){
		return (j.mise_base > j.nbJetons)? j.nbJetons : j.mise_base;
	}
	else return (j.mise /2 > j.nbJetons)? j.nbJetons : j.mise/2;
}

void Mise(Joueur* j){
	
	if (j->typeMise == CROISSANT){
		j->mise = miseCroissante(*j);
	}
	
	else if (j->typeMise == DESCENDANT){
		j->mise = miseDescendante(*j);
	}
	
	else if (j->typeMise == CSTE){
	(j->mise > j->nbJetons)? j->mise=j->nbJetons : j->mise;
	}
	
	else {
		print("Ce type de mise n'est pas pris en compte\n");
		exit(3); // faire ecrire message pour mise inexistante
	}
	
}
