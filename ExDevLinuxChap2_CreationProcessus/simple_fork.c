/********************************
 * Fichier simple_fork.c
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
	pid_t pid_fils = -1;	/* Variable utilisée pour
				 * récupérer la valeur de retour de
				 * l'execution du fork */
	pid_fils = fork();
	/*
	 * Sortie du programme en cas d'echec d'execution du fork (p.e. table
	 * des PCB pleine)
	 */
	if (pid_fils == -1) {
		perror("Echec du fork\n");
		exit(EXIT_FAILURE);
	}
	/* Code exécuté quand l'execution de fork n'est pas en échec */
	printf("(%d) All you need is love \n", getpid());
	sleep(15);		/* Suspension du processus pendant 15 sec */
	exit(EXIT_SUCCESS);
}
