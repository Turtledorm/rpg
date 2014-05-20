
#ifndef _ATRIBUTOS_H
#define _ATRIBUTOS_H

/*----------------------------------------------------------------------------*
 *-------------------------------- CONSTANTES --------------------------------*
 *----------------------------------------------------------------------------*/

#define NAME       32  /* Tamanho do vetor que guarda o nome de um personagem */
#define STAT      120  /* Pontos a serem distribuídos nos atributos */
#define NUM_ATRIB   6  /* Quantidade de atributos fixos de cada personagem */

/*----------------------------------------------------------------------------*
 *-------------------------------- ESTRUTURAS --------------------------------*
 *----------------------------------------------------------------------------*/

typedef struct status Status;
typedef struct jogador Jogador;

struct status {
	int maxHp; /* HP máximo  */  
	int atk;   /* Ataque     */
	int def;   /* Defesa     */
	int agi;   /* Agilidade  */
	int spd;   /* Velocidade */
	int luck;  /* Sorte      */
	int hp;    /* HP atual   */
};

struct jogador {
	char nome[NAME];
	Status status;
	int level;
	int atb;  
	int acao;
	int potencia;
	bool defendido;
};

/* Observação: 'SPD' é usado para determinar com que frequência um personagem 
 * age na batalha. O atributo 'SPD' dos dois personagens é somado continuamente
 * em 'ATB' até que o de alguém ultrapasse o 'ATBMAX', podendo então agir. Depois
 * disso, o 'ATB' daquele personagem é reduzido em 'ATBMAX' e o processo recomeça.
 *
 * 'AGI' representa tanto a acurácia quanto esquiva do personagem. Quando um 
 * ataque é feito, a 'AGI' do atacante e do defensor são comparadas. Quanto mais
 * distante estiver um valor do outro, maior (ou menor) será a chance de acerto.
 * -------------------------------------------------------------------------- */

/*----------------------------------------------------------------------------*
 *-------------------------- PROTÓTIPOS DE FUNÇÔES ---------------------------*
 *----------------------------------------------------------------------------*/

void criaJogador(Jogador *eu);
void geraOponente(Jogador *foe);
void inicializa(Jogador *eu, Jogador *foe);

#endif /* _ATRIBUTOS_H */
