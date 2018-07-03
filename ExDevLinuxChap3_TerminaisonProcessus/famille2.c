/********************************
 * Fichier famille2.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		/* stderr, stdout, fprintf */
#include <unistd.h>		/* fork */
#include <sys/wait.h>		/* wait */
#include <stdlib.h>		/* exit */

void code_creation_fils(pid_t pid_fils)
{
	if (pid_fils != 0) {	/* Code père */
		printf("(PID : %d) Création de %d\n", getpid(), pid_fils);
	} else {		/* Code fils pid_fils */
		printf("(PID : %d, PPID : %d) Bonjour et aurevoir\n", getpid(), getppid());
		exit(EXIT_SUCCESS);	/* FIN DU CODE ASSOCIE AU PROCESSUS
					 * TQ pid_fils==0 */
	}
}

int main(void)
{
	pid_t pid_fils1 = -1, pid_fils2 = -1, pid_fils3 = -1, pid_fils4 = -1;
	pid_t wait_return_value = -1;
	int i = 0;

	printf("(PID : %d, PPID : %d) p1- Bonjour\n", getpid(), getppid());

	pid_fils1 = fork();	/* Créer un fils (p2) */
	code_creation_fils(pid_fils1);

	pid_fils2 = fork();	/* Créer un autre fils (p3) */
	code_creation_fils(pid_fils2);

	pid_fils3 = fork();	/* Créer encore un fils (p4) */
	code_creation_fils(pid_fils3);

	pid_fils4 = fork();	/* Et encore un (p5) */
	code_creation_fils(pid_fils4);

	/* Code exécuté par p1 seulement */
	for (i = 0; i < 4; i++) {
		wait_return_value = wait(NULL);
		printf("(PID : %d) débloqué par %d \n", getpid(), wait_return_value);
	}
	printf("(PID : %d) Aurevoir. \n", getpid());
	exit(EXIT_SUCCESS);
}
