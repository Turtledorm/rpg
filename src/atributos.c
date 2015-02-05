
#include <stdio.h>   /* scanf, printf, ... */
#include <stdlib.h>  /* srand, rand, ...   */
#include <string.h>  /* strcpy (to, from)  */
#include <time.h>    /* time para srand    */
#include <ctype.h>   /* toupper            */
#include <stdbool.h> /* bool, true, false  */

#include "atributos.h"
#include "extra.h"

/*----------------------------------------------------------------------------*
 *------------------------ IMPLEMENTAÇÂO DAS FUNÇÔES -------------------------*
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * Cuida da criação do personagem jogável, recebendo do usuário o nome e
 * a distribuição dos atributos. Caso sejam gastos mais pontos que
 * o máximo 'STAT', o programa solicita que o processo seja refeito.
 *----------------------------------------------------------------------------*/

void criaJogador(Jogador *eu)
{
	int *atr, pontos, i;
	char resposta;
	char *atrib[NUM_ATRIB] = {"HP", "ATK", "DEF", "AGI", "SPD", "LUCK"};

	do {
		printf("\nDigite o nome do seu personagem: ");
		scanf(" %[^\n]", eu->nome);

	   	printf("\nBem-vindo(a), %s!\n"
	   		   "Deseja continuar com esse nome (S/N)? ", eu->nome);
	   	scanf(" %c", &resposta);

	} while (toupper(resposta) == 'N');

	/* 'atr' é um ponteiro para a estrutura eu->status */
	atr = (int *) &eu->status;

	do {
		/* Antes de começarmos, zeramos os atributos */
		for (i = 0; i < NUM_ATRIB; i++) 
			*(atr + i) = 0;
		pontos = STAT;

		/* Encerra-se o loop quando todos os pontos tiverem sido gastos OU 
		 * todos os atributos recebidos sem que o saldo fique negativo. */
		for (i = 0; i < NUM_ATRIB && pontos > 0; i++) {
			do {
				printf("\n%d de %d pontos restantes.\n"
					   "Quantos pontos para %s? ", pontos, STAT, atrib[i]);
				scanf("%d", atr + i);

				if (*(atr + i) < 0) 
					puts("Apenas valores positivos!");
				
			} while (*(atr + i) < 0);
			
			pontos -= *(atr + i);
		}

		if (pontos < 0)
			puts("Você gastou mais pontos do que possui!");
		else { 
			printf("\n<~ %s ~>\n"
				   "-----------\n", eu->nome);
			for (i = 0; i < NUM_ATRIB; i++)
				printf("%4s = %2d\n", atrib[i], *(atr + i));

			printf("\nDigite 'R' para refazer ou "
				   "qualquer outra tecla para continuar: ");
			getchar(); /* limpa buffer */
			scanf("%c", &resposta);
		}
	} while (toupper(resposta) == 'R' || pontos < 0);    
}

/*------------------------------------------------------------------------------
 * Gera aleatoriamente os atributos do oponente.
 * Os atributos encontram-se no intervalo [STAT/5 ± STAT/10].
 *----------------------------------------------------------------------------*/

void geraOponente(Jogador *foe)
{
	int *atr, i, low, high;

	srand(time(NULL));
	strcpy(foe->nome, "Goblin");

	low  = STAT/5 - STAT/10;
	high = STAT/5 + STAT/10;

	/* Aqui são percorridos os atributos contidos em foe->status, e
	   randomicamente associados os respectivos valores */
	atr = (int *) &foe->status;
	for (i = 0; i < NUM_ATRIB; i++)
		*(atr + i) = randomInteger(low, high);

	#ifdef DEBUG
		printf("\n HP = %2d, ATK = %2d,  DEF = %2d\n"
				 "AGI = %2d, SPD = %2d, LUCK = %2d\n",
				foe->status.maxHp, foe->status.atk, foe->status.def, 
				foe->status.agi,   foe->status.spd, foe->status.luck);
	#endif
}

/*------------------------------------------------------------------------------
 * Inicializa alguns atributos e parâmetros dos jogadores. 
 *----------------------------------------------------------------------------*/

void inicializa(Jogador *eu, Jogador *foe)
{
	eu->status.hp = eu->status.maxHp;
	foe->status.hp = foe->status.maxHp;
	eu->atb = foe->atb = foe->acao = 0;
	eu->potencia = foe->potencia = 1;
	eu->defendido = foe->defendido = false;
}

/*----------------------------------------------------------------------------*/
