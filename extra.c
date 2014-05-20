
#include <stdio.h>   /* scanf, printf, ... */
#include <stdlib.h>  /* srand, rand, ...   */

#include "extra.h"

/*----------------------------------------------------------------------------*
 *------------------------ IMPLEMENTAÇÂO DAS FUNÇÔES -------------------------*
 *----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * A função randomInteger devolve um inteiro aleatório entre low e high
 * inclusive, ou seja, no intervalo fechado <low..high>.
 * Vamos supor que 0 <= low <= high < INT_MAX.
 * O código foi copiado da biblioteca random de Eric Roberts. 
 */ 

int randomInteger(int low, int high)
{
	int k;
	double d;

	d = (double) rand() / ((double) RAND_MAX + 1);
	k = d * (high - low + 1);

	return (low + k);
}

/*-----------------------------------------------------------------------------
 * O parâmetro de mallocSafe é do tipo size_t.  
 * Em muitos computadores, size_t é equivalente a unsigned int.  
 * A função protege o programa contra falta de memória ao realizar malloc.
 *
 * Fonte: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
 */

void * mallocSafe(size_t nbytes)
{
    void *ptr;
    ptr = malloc(nbytes);

    if (ptr == NULL) {
        fprintf(stderr, "Socorro! malloc devolveu NULL!\n");
        exit(EXIT_FAILURE);
    }  
    return ptr;
}
