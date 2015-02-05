
#ifndef _ITEM_H
#define _ITEM_H

#include <stdbool.h>

/*----------------------------------------------------------------------------*
 *------------------------- CONSTANTES E ESTRUTURAS --------------------------*
 *----------------------------------------------------------------------------*/

#define NUM_TIPOS 3

typedef struct item Item;
typedef struct mochila Mochila;
typedef enum tipo {
	DANO,
	EFEITO,
	STATUS
} Tipo;

struct item {
	char *nome;
	int alvo;
	int indice;
	Tipo tipo;
	bool percent;
	Status status;
};
   
struct mochila {
	Item item;
	int quant;
	Mochila *prox;
};

/*----------------------------------------------------------------------------*
 *-------------------------- PROTÓTIPOS DE FUNÇÔES ---------------------------*
 *----------------------------------------------------------------------------*/

void mochilaInit();
void mochilaAdd(Item item, int quant);
void mochilaDrop(int indice, int quant);
Mochila * mochilaFind(int indice);
void mochilaKill(int indice);
void mochilaFree(Mochila *morto);
void mochilaFreeAll();

#endif /* _ITEM_H */
