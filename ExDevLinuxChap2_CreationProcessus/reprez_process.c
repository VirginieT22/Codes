/********************************
 * Fichier reprez_process.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		/* printf */
#include <unistd.h>		/* fork */
#include <stdlib.h>		/* EXIT_SUCCESS, EXIT_FAILURE */

int main(void)
{
	pid_t pid_fils = -1;
	int a = 4;
	int b = 3;
	pid_fils = fork();
	a = 5;
	printf("All you need is love\n");
	printf("a==%d b==%d pid_fils==%d\n", a, b, pid_fils);
	exit(EXIT_SUCCESS);
}
