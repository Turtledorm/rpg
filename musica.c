
#include <stdlib.h>  /* system() */

#include "extra.h"

/*----------------------------------------------------------------------------*
 *------------------------ IMPLEMENTAÇÂO DAS FUNÇÔES -------------------------*
 *----------------------------------------------------------------------------*/

void tocaMusica(char nome[])
{
	#ifdef __linux__ 
		system("while [ 1 ]; do aplay -q " nome "; done &");
	#elif __WINDOWS__
		system(nome);
	#endif
}

/*----------------------------------------------------------------------------*/

void paraMusica()
{
	#ifdef __linux__ 
		system("killall -g aplay &");
	#elif __WINDOWS__ 
		system("taskkill /IM wmplayer.exe");
	#endif
}

/*----------------------------------------------------------------------------*/
