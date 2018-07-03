/********************************
 * Fichier appel_fork1.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		/* stderr, stdout, fprintf, perror */
#include <unistd.h>		/* fork */
#include <sys/wait.h>		/* wait */
#include <stdlib.h>		/* exit */

int main(void)
{
	pid_t pid_fils = -1;	/* Pour récupérer la valeur de
				 * retour de l'execution du fork */
	printf("(%d) Sing it' \n", getpid());
	pid_fils = fork();

	printf("(%d) We will we will rock you (%d)\n", getpid(), pid_fils);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
