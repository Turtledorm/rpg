
#include <stdlib.h>  /* system() */
#include <string.h>  /* strcpy(), strcat() */

#include "extra.h"

/*----------------------------------------------------------------------------*
 *------------------------ IMPLEMENTAÇÂO DAS FUNÇÔES -------------------------*
 *----------------------------------------------------------------------------*/

void tocaMusica(char nome[])
{
	char command[100];

	#ifdef __linux__
		strcpy(command, "while [ 1 ]; do aplay -q ");
		strcat(command, nome);
		strcat(command, "; done &");
		system(command);
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
