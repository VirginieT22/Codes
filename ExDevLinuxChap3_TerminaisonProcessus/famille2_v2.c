/********************************
 * Fichier famille2_v2.c
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
		exit(EXIT_SUCCESS);	/* FIN DU CODE ASSOCIE AU PROCESSUS TQ pid_fils==0 */
	}
}

int main(void)
{
	pid_t pid_fils = -1;
	pid_t wait_return_value = -1;
	int pid_de_p1 = getpid();	/* Cette variable contient le PID de p1 */
	int i = 0;

	printf("(PID : %d, PPID : %d) p1- Bonjour\n", getpid(), getppid());

	for (i = 0; i < 4; i++) {	/* 4 fois.. */
		if (getpid() == pid_de_p1) {	/* Code exécuté par p1 seulement car fork dans iteration */
			pid_fils = fork();	/* Créer un fils */
			if (pid_fils != 0) {	/* Code père */
				printf("(PID : %d) Création de %d\n", getpid(), pid_fils);
			} else {	/* Code fils pid_fils */
				printf("(PID : %d, PPID : %d) Bonjour et aurevoir\n", getpid(),
				       getppid());
				exit(EXIT_SUCCESS);	/* FIN DU CODE ASSOCIE AU PROCESSUS TQ pid_fils==0 */
			}
		}
	}

	/* Code exécuté par p1 seulement */
	for (i = 0; i < 4; i++) {
		wait_return_value = wait(NULL);
		printf("(PID : %d) débloqué par %d \n", getpid(), wait_return_value);
	}
	printf("(PID : %d) Aurevoir. \n", getpid());
	exit(EXIT_SUCCESS);
}
