/********************************
 * Fichier wait_exit.c
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
	pid_t pid_fils = -1;
	pid_fils = fork();

	if (pid_fils == 0) {
		sleep(2);
		printf("Monsieur le Président, je vous fais une lettre\n");
		exit(EXIT_SUCCESS);
	} else {
		printf("que vous lirez peut-être si vous avez le temps\n");
		exit(EXIT_SUCCESS);
	}
}
