/********************************
 * Fichier famille3.c
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
	pid_t pid_p2 = -1, pid_p3 = -1, pid_p4 = -1, pid_p5 = -1, pid_p6 = -1;

	printf("(PID : %d, PPID : %d) p1- Bonjour\n", getpid(), getppid());

	pid_p2 = fork();
	if (pid_p2 != 0) {	/* Code p1 */
		printf("(PID : %d) Création de %d (p2)\n", getpid(), pid_p2);
	} else {		/* Code de p2 */
		pid_p3 = fork();
		if (pid_p3 != 0) {	/* Code de p2 */
			printf("(PID : %d) Création de %d (p3)\n", getpid(), pid_p3);
			wait(NULL);	// Attente de p3 par p2
			exit(EXIT_SUCCESS);	// Fin de code de p2
		} else {	/* Code de p3 */
			pid_p4 = fork();
			if (pid_p4 != 0) {	/* Code de p3 */
				printf("(PID : %d) Création de %d (p4)\n", getpid(), pid_p4);
				wait(NULL);	// Attente de p4 par p3
				exit(EXIT_SUCCESS);	// Fin de code de p3
			} else {	/* Code de p4 */
				printf("(PID : %d, PPID : %d) Bonjour et aurevoir\n", getpid(),
				       getppid());
				sleep(10);
				exit(EXIT_SUCCESS);
			}
		}
	}

	/* Code exécuté par p1 seulement */
	pid_p5 = fork();
	if (pid_p5 != 0) {	/* Code de p1 */
		printf("(PID : %d) Création de (p5) %d\n", getpid(), pid_p5);
	} else {		/* Code de p5 */
		printf("(PID : %d, PPID : %d) Bonjour et aurevoir\n", getpid(), getppid());
		sleep(10);
		exit(EXIT_SUCCESS);
	}

	/* Code exécuté par p1 seulement */
	pid_p6 = fork();
	if (pid_p6 != 0) {	/* Code de p1 */
		printf("(PID : %d) Création de (p6) %d\n", getpid(), pid_p6);
	} else {		/* Code de p5 */
		printf("(PID : %d, PPID : %d) Bonjour et aurevoir\n", getpid(), getppid());
		sleep(10);
		exit(EXIT_SUCCESS);
	}

	/*  Code exécuté par p1 seulement : 3 fils à attendre */
	wait(NULL);
	wait(NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
