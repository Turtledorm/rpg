
#include <stdio.h>   /* scanf, printf, ... */
#include <stdlib.h>  /* EXIT_SUCCESS  */

#include "atributos.h"
#include "batalha.h"
#include "item.h"

/*----------------------------------------------------------------------------*
 *----------------------------------- MAIN -----------------------------------*
 *----------------------------------------------------------------------------*/

int main()
{
	Jogador eu, foe;
	
	criaJogador(&eu); 
	geraOponente(&foe);
	inicializa(&eu, &foe);
	batalha(eu, foe);
	
	return EXIT_SUCCESS;
}
