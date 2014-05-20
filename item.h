
#ifndef _ITEM_H
#define _ITEM_H

/*----------------------------------------------------------------------------*
 *------------------------- CONSTANTES E ESTRUTURAS --------------------------*
 *----------------------------------------------------------------------------*/

#define NUM_TIPOS 3

typedef struct item Item;
typedef struct mochila Mochila;
typedef enum tipo Tipo;

struct item {
	char *nome;
	int alvo;
	Tipo tipo;
	bool percent;
	Status status;
};
   
struct mochila {
	Item item;
	int quant;
	Mochila *prox;
};

enum tipo {
	DANO,
	EFEITO,
	STATUS
};

/*----------------------------------------------------------------------------*
 *-------------------------- PROTÓTIPOS DE FUNÇÔES ---------------------------*
 *----------------------------------------------------------------------------*/

void mochilaInit();
void mochilaAdd(Item *p, int n);
void mochilaReduce(int indice, int n);
Mochila * mochilaFind(int indice);
void mochilaKill(int indice);
void mochilaFree(Mochila *morta);
void mochilaFreeAll();

#endif /* _ITEM_H */
