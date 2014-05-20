
#include <stdio.h>   /* scanf, printf, ... */
#include <stdlib.h>  /* srand, rand, ...   */
#include <string.h>  /* strcpy (to, from)  */
#include <time.h>    /* time para srand    */
#include <stdbool.h> /* bool, true, false  */
#include <math.h>    /* sin, cos, ...      */

#include "jogador.h"
#include "extra.h"
#include "item.h"
#include "batalha.h"
#include "musica.h"

/*----------------------------------------------------------------------------*
 *------------------------ IMPLEMENTAÇÂO DAS FUNÇÔES -------------------------*
 *----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Cuida dos eventos de batalha, recebendo do usuário uma ação ou
 * calculando aleatoriamente uma para o computador. As iterações ocorrem
 * até que um dos jogadores tenha HP <= 0.
 *---------------------------------------------------------------------------*/

void batalha(Jogador eu, Jogador foe)
{
	/* Toca a música especificada indefinidamente */
	tocaMusica("ffvi.wav");

	while (eu.stat.hp > 0 && foe.stat.hp > 0) {
		/* Exibe barras de vida na tela */
		lifebar(eu);
		lifebar(foe);

		/* Loop até chegar a vez de um personagem. O (+1) nesses dois
		   casos impede o personagem de nunca jogar caso SPD == 0. */
		while (eu.atb < MAX_ATB && foe.atb < MAX_ATB) {
			eu.atb += eu.stat.spd + 1;
			foe.atb += foe.stat.spd + 1
		}

		if (eu.atb >= MAX_ATB) {
			eu.atb -= MAX_ATB;
			do {
				printf("\nSua vez! Digite 1 para atacar,\n"
				 	   "2 para carregar o golpe ou 3 para defender: ");
				scanf("%d", &eu.acao);

				if (eu.acao == 2 && eu.potencia == MAX_POW) {
					puts("\n>Limite atingido! Impossível carregar mais.");
					eu.acao = 0;
				}
			} while (eu.acao < 1 || eu.acao > 3);

			turno(&eu, &foe);
		}
		else { /* (foe.atb >= MAX_ATB) */
			congela(1);
			foe.atb -= MAX_ATB;

			do foe.acao = randomInteger(1, 3);
			while (foe.potencia == MAX_POW && foe.acao == 2);

			turno(&foe, &eu);
		}
	}

	/* Encerra a execução da música */
	paraMusica();

	/* Exibe resultado da batalha */
	lifebar(eu);
	lifebar(foe);
	printf("\n> %s foi aniquilado.\n", 
		(eu.stat.hp <= 0) ? eu.nome : foe.nome);

	printf("\n***** Você %s! *****\n\n", 
		(eu.stat.hp > 0) ? "ganhou" : "perdeu");
}

/*----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * Determina o resultado da ação escolhida por 'x', sendo 'y' o oponente 
 * de 'x'. Aqui são feito os cálculos envolvendo dano, carregamento e defesa.
 */

void turno(Jogador *x, Jogador *y)
{
	int dano, i;

	puts("\n----------------------------------------------------\n");

	/* Desfaz os efeitos da defesa no turno anterior */
	x->defendido = false;

	switch (x->acao) {
		/* Atacar */
		case 1: 
			printf("> %s ataca", x->nome);
			for (i = 0; i < 3; i++) {
				printf(".");
				fflush(stdout); /* evita que o buffer 'trave' */
				congela(1);
			}

			if (acerto(x->stat.agi, y->stat.agi)) {
				dano = x->stat.atk - y->stat.def;
				if (y->defendido) dano -= y->stat.def;

				/* Evita dano 0 ou que 'cura' o oponente */
				if (dano <= 0) dano = 1; 

				dano *= x->potencia;
				dano += randomInteger((-dano)/5, dano/5);

				if (critico(x->stat.luck)) {
					dano *= 2;
					printf(" CRÍTICO!");
					fflush(stdout);
					congela(1);
				}

				y->stat.hp -= dano;
				if (y->stat.hp < 0) y->stat.hp = 0; /* HP nunca negativo */

				printf("\nTira %d de vida.\n", dano);
			}
			else printf("\n%s se esquivou!\n", y->nome);

			x->potencia = 1;
			break;

		/* Carregar */
		case 2:
			printf("> %s carrega energia.\nO dano agora é x%d!\n", 
				x->nome, ++(x->potencia));
			break;

		/* Defender */
		case 3:
			printf("> %s defende-se. DEF foi dobrada!\n", x->nome);
			if (x->stat.hp < x->stat.maxHp) {
				puts("Recupera 1 de vida!");
				(x->stat.hp)++;
			}
			x->defendido = true;
	}

	puts("\n----------------------------------------------------");
	congela(1);
}

/*----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * A função recebe a AGI do atacante e do defensor e determina se o ataque
 * resultou num acerto. Sendo 'agiX' e 'agiY' as destrezas respectivas de
 * cada um, tal chance é 0% se agiX == 0, 80% se agiX == agiY e 100% caso
 * agiX >= 2*agiY. Valores intermediários são encontrados por meio das
 * funções seno e cosseno; logo, não é uma distribuição uniforme.
 *----------------------------------------------------------------------------*/

bool acerto(int agiX, int agiY)
{
	if (agiX >= 2*agiY) return true;

	int chance = (agiX <= agiY) ? sin((double) agiX/agiY * PI_2) * 80
							    : cos((double) agiX/agiY * PI_2) * (-20) + 80;
	#ifdef DEBUG
		printf(" (Chance: %d%%)", chance);
	#endif
	return (randomInteger(1, 100) <= chance);
}

/*----------------------------------------------------------------------------*/

/*-------------------------------------------------------s----------------
 * A função recebe um parâmetro sorte, baseado na LUCK do jogador que
 * estiver atacando, e determina randomicamente, por meio da constante
 * CRIT, se o golpe será crítico ou não.
 */

bool critico(int sorte)
{
	int chance = CRIT * (sorte + 10)/10.0;
	return (randomInteger(1, 100) <= chance);
}

/*-----------------------------------------------------------------------*
 * Desenha as barras de vida de um personagem em virtude da quantidade
 * de HP que ele possui no momento.
 */

void lifebar(Player x)
{
	int cont;

	printf("\n%s {x%d}", x.nome, x.potencia);
	if (x.defendido) printf(" [defendendo]");

	printf("\n%3d [", x.stat.hp);
	for (cont = 0; cont < x.stat.hp; cont++)
		printf("=");
	while (cont++ < x.stat.maxHp)
		printf(" ");
	printf("]\n");
}

/*-----------------------------------------------------------------------*
 * A função recebe um tempo, em segundos, e interrompe a
 * execução do programa pelo intervalo de tempo estipulado.
 */

void congela(float tempo) 
{
	int atual = clock();
	while (clock() < atual + (CLOCKS_PER_SEC * tempo)); /* não faça nada */
}
