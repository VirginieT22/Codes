/********************************
 * Fichier simple_fork_wait.c
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
	pid_t pid_fils = -1;	/* Pour récupérer la valeur de retour de l'execution du fork */
	pid_fils = fork();

	printf("(%d) Ah si j'avais un franc cinquante (%d)\n", getpid(), pid_fils);
	wait(NULL);		/* Primitive étudiée plus tard */
	exit(EXIT_SUCCESS);	/* Sortie de programme non conseillée sous cette forme mais pour l'exemple ici */
}
