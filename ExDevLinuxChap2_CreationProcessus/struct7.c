/********************************
 * Fichier struct7.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		/* stderr, stdout, fprintf */
#include <unistd.h>		/* fork */
#include <sys/wait.h>		/* wait */
#include <stdlib.h>		/* exit */

int main(void)
{
	if (fork() != -1)
		printf("Bonjour !\n");
	wait(NULL);
	exit(EXIT_SUCCESS);
}
