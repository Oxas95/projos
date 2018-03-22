NOM=DEMONTI Pierre

#Edition de liens

lv21: Main.o deck.o lire_ecrire.o joueur.o banque.o
	gcc -g -Wall Main.o deck.o lire_ecrire.o joueur.o banque.o -o lv21

#Compilation:

deck.o: deck.c deck.h 
	gcc -c -Wall deck.c

lire_ecrire.o: lire_ecrire.c
	gcc -c -g -Wall lire_ecrire.c
	
Main.o: Main.c deck.h lire_ecrire.h
	gcc -c -g -Wall Main.c

joueur.o: joueur.c deck.h lire_ecrire.h
	gcc -c -g -Wall joueur.c

banque.o: banque.c deck.h 
	gcc -c -g -Wall banque.c
	
	
clean:
	rm -f deck.o
	rm -f lire_ecrire.o
	rm -f Main.o
	rm -f joueur.o
	rm -f banque.o
	rm -f lv21
	
	
