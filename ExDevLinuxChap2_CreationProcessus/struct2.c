/********************************
 * Fichier struct2.c
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
	pid_t pid_fils1 = -1;
	pid_t pid_fils2 = -1;
	pid_fils1 = fork();
	pid_fils2 = fork();
	printf("Ah si j'avais un franc cinquante\n");
	printf("pid_fils1==%d pid_fils2==%d\n", pid_fils1, pid_fils2);
	exit(EXIT_SUCCESS);
}
