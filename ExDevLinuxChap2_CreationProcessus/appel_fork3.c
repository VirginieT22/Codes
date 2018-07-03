/********************************
 * Fichier appel_fork3.c
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
	pid_t pid_fils1 = -1;
	pid_t pid_fils2 = -1;

	pid_fils1 = fork();
	pid_fils2 = fork();

	printf("(%d) Do you do you Saint-Tropez (%d) (%d)\n", getpid(), pid_fils1, pid_fils2);
	wait(NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
