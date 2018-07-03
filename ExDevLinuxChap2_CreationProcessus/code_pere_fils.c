/********************************
 * Fichier code_pere_fils.c
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

	if (pid_fils == 0)
	/* Code exécuté par le fils */
	{
		printf("(%d) Je suis Yvain, mon père est %d \n", getpid(), getppid());
		exit(EXIT_SUCCESS);
	} else { /* Code exécuté par le père */
		printf("(%d) Je suis Léodagan\n", getpid());
	}
	/* Code exécuté quand l'execution de fork n'est pas en échec */
	wait(NULL);		/* Primitive étudiée plus tard */
	exit(EXIT_SUCCESS);
}
