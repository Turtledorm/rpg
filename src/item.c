
#include <stdio.h>   /* scanf, printf, ... */
#include <stdlib.h>  /* free */

#include "atributos.h"
#include "extra.h"
#include "item.h"

/*----------------------------------------------------------------------------*
 *----------------------------- VARIÁVEIS GLOBAIS ----------------------------*
 *----------------------------------------------------------------------------*/

static Mochila *inventario;
static Mochila *fim;

/*----------------------------------------------------------------------------*
 *------------------------ IMPLEMENTAÇÂO DAS FUNÇÔES -------------------------*
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Um breve resumo do funcionamento de cada função:
 * mochilaInit: cria a fila (vazia), com cabeça, de itens da mochila/inventário
 * mochilaEmpty: verifica se o inventário está vazio
 * mochilaAdd: incrementa a quantidade de um determinado item
 * mochilaDrop: decrementa a quantidade de um determinado item
 * mochilaFind: procura pelo item no inventário, devolve NULL caso não encontre
 * mochilaKill: elimina um item do inventário
 * mochilaFree: libera a memória associada a um item
 * mochilaFreeAll: libera toda a memória usada e esvazia o inventário
 */

/*----------------------------------------------------------------------------*/

void mochilaInit()
{
	inventario = mallocSafe(sizeof (Mochila));
	inventario->prox = NULL;
	fim = inventario;
}

/*----------------------------------------------------------------------------*/

#define mochilaEmpty() (inventario->prox == NULL)

/*----------------------------------------------------------------------------*/

void mochilaAdd(Item item, int quant)
{
	Mochila *aux;
	aux = mochilaFind(item.indice);

	/* Caso item não esteja no inventário, criamos ele */
	if (aux == NULL) {
		Mochila *novo = mallocSafe(sizeof (Item));
		novo->quant = 0;
		fim->prox = novo;
		aux = fim = novo;
	}
	aux->quant += quant;
}

/*----------------------------------------------------------------------------*/

void mochilaDrop(int indice, int quant)
{
	Mochila *aux;
	aux = mochilaFind(indice);

	if (aux == NULL) {
		puts("Aviso: Item especificado não está na mochila!");
		return;
	}
	aux->quant -= quant;
	if (aux->quant <= 0)
		mochilaKill(indice);
}

/*----------------------------------------------------------------------------*/

Mochila * mochilaFind(int indice)
{
	Mochila *batedor;

	for (batedor = inventario->prox; batedor != NULL; batedor = batedor->prox)
		if (batedor->item.indice == indice)	return batedor;

	return NULL;
}

/*----------------------------------------------------------------------------*/

void mochilaKill(int indice)
{
	Mochila *frente, *tras;
	tras = inventario;
	frente = tras->prox;

	while (frente != NULL) {
		if (frente->item.indice == indice) {
			tras->prox = frente->prox;
			mochilaFree(frente);
			return;
		}
		tras = frente;
		frente = frente->prox;
	}
}

/*----------------------------------------------------------------------------*/

void mochilaFree(Mochila *morto)
{
	free(morto->item.nome);
	free(morto);
}

/*----------------------------------------------------------------------------*/

void mochilaFreeAll()
{
	Mochila *frente, *tras;
	tras = inventario;
	frente = tras->prox;

	while (frente != NULL) {
		mochilaFree(tras);
		tras = frente;
		frente = frente->prox;
	}
	inventario = fim = NULL;
}

/*----------------------------------------------------------------------------*/
