CC     = gcc
CFLAGS = -g -Wall -ansi -O2 -pedantic -Wno-unused-result
RM     = rm
#-------------------------------------------------------------------

rpg: main.o atributos.o batalha.o item.o extra.o musica.o
	$(CC) main.o atributos.o batalha.o item.o extra.o musica.o -o rpg -lm

main.o: main.c atributos.h batalha.h item.h extra.h
	$(CC) $(CFLAGS) -c main.c 

atributos.o: atributos.c atributos.h extra.h
	$(CC) $(CFLAGS) -c atributos.c  

batalha.o: batalha.c batalha.h atributos.h item.h extra.h musica.h
	$(CC) $(CFLAGS) -c batalha.c

item.o: item.c item.h atributos.h extra.h
	$(CC) $(CFLAGS) -c item.c

extra.o: extra.c extra.h
	$(CC) $(CFLAGS) -c extra.c

musicaa.o: musicaa.c musicaa.h
	$(CC) $(CFLAGS) -c musicaa.c

clean: 
	rm -f *.o 
