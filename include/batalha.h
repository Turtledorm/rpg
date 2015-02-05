
#ifndef _BATALHA_H
#define _BATALHA_H

/*----------------------------------------------------------------------------*
 *-------------------------------- CONSTANTES --------------------------------*
 *----------------------------------------------------------------------------*/

#define MAX_ATB 256 /* Quando ATB >= ATBMAX, o personagem escolhe uma ação */
#define CRIT      5 /* Chance de acontecer um crítico */
#define MAX_POW   5 /* Carregamento máximo possível para um personagem */

#define PI_2 1.570796326794896 /* usado para sin() e cos() */

/*----------------------------------------------------------------------------*
 *-------------------------- PROTÓTIPOS DE FUNÇÔES ---------------------------*
 *----------------------------------------------------------------------------*/

void lifebar(Jogador x);
void batalha(Jogador eu, Jogador foe);
void turno(Jogador *x, Jogador *y);

bool acerto(int agiX, int agiY);
bool critico(int sorte);

void congela(float tempo);

#endif /* _BATALHA_H */
