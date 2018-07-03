/********************************
 * Fichier famille4.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		/* stderr, stdout, fprintf */
#include <unistd.h>		/* fork */
#include <sys/wait.h>		/* wait */
#include <stdlib.h>		/* exit */

void genere_sous_arbre()
{
	pid_t pid_p2 = -1, pid_p3 = -1;
	pid_p2 = fork();
	if (pid_p2 != 0) {	/* Code de p1 */
		printf("(PID : %d) Création de (p2) %d\n", getpid(), pid_p2);
	} else {		/* Code de p2 */
		pid_p3 = fork();
		if (pid_p3 != 0) {	/* Code de p2 */
			printf("(PID : %d) Création de (p3) %d\n", getpid(), pid_p3);
			wait(NULL);	// Attente de p3
			exit(EXIT_SUCCESS);
		} else {	/* Code de p3 */
			printf("(PID : %d, PPID : %d) (p3) Bonjour et aurevoir\n", getpid(),
			       getppid());
			sleep(10);
			exit(EXIT_SUCCESS);
		}
	}
}

int main(void)
{

	printf("(PID : %d, PPID : %d) (p1) Bonjour\n", getpid(), getppid());
	genere_sous_arbre();	// Premier sous arbre
	genere_sous_arbre();	// Deuxième sous arbre
	genere_sous_arbre();	// Troisième sous arbre

	/*  Code exécuté par p1 seulement : 3 fils à attendre */
	wait(NULL);
	wait(NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
