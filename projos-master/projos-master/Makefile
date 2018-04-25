NOM=DEMONTI Pierre

#Edition de liens

lv21: tour Main.o deck.o lire_ecrire.o joueur.o banque.o se_fichier.o
	gcc -g -Wall Main.o deck.o lire_ecrire.o joueur.o banque.o se_fichier.o -o lv21

#Compilation:

deck.o: deck.c 
	gcc -c -Wall deck.c deck.h 

lire_ecrire.o: lire_ecrire.c
	gcc -c -g -Wall lire_ecrire.c lire_ecrire.h se_fichier.h
	
Main.o: Main.c
	gcc -c -g -Wall Main.c banque.h deck.h

joueur.o: joueur.c 
	gcc -c -g -Wall joueur.c lire_ecrire.h deck.h 

banque.o: banque.c 
	gcc -c -g -Wall banque.c deck.h banque.h

se_fichier.o: se_fichier.c
		gcc -c -g -Wall se_fichier.c se_fichier.h

tour:
	rm -fr tour
	mkdir tour

clean:
	rm -f *.o
	rm -f lv21
	rm -fr tour
	rm -f *.gch

run:
	reset
	./lv21
	
	
	
