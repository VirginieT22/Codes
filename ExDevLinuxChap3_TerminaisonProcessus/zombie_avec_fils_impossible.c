/********************************
 * Fichier zombie_avec_fils_impossible.c
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
	pid_t pid_fils = -1;	/* Pour récupérer la valeur de
				 * retour de l'execution du fork
				 * créant le processus fils */
	pid_t pid_fils_du_fils = -1;	/* Pour récupérer la valeur
					 * de retour de l'execution
					 * du fork créant le
					 * processus fils du fils */
	pid_t wait_returned_value = -1;	/* Pour récupérer le
					 * valeur retour du wait
					 * du père */
	int i = 0;

	pid_fils = fork();	/* Création du processus fils */

	if (pid_fils == 0) {
		/* Code affecté au fils */
		printf("(%d) Je suis le fils, mon père est %d \n", getpid(), getppid());
		/* Création du fils du fils */
		pid_fils_du_fils = fork();

		if (pid_fils_du_fils == 0) {
			/* Code affecté au fils du fils */
			for (i = 0; i < 6; i++) {
				printf("(%d) Je suis le fils du fils. Mon père est %d \n",
				       getpid(), getppid());
				sleep(2);
			}
			exit(EXIT_SUCCESS);
		}
		/* Suite du code affecté au fils */
		for (i = 0; i < 2; i++) {
			printf("(%d) Fils ..\n", getpid());
			sleep(2);
		}
		printf("(%d) Je suis le fils, je termine mon code, je deviens un zombie.\n",
		       getpid());
		exit(EXIT_SUCCESS);
	}
	/* Code affecté au père */
	printf
	    ("(%d) Je suis le pere, j'effectue mon traitement qui dure longtemps avant de prendre en compte la terminaison de mon fils %d \n",
	     getpid(), pid_fils);
	for (i = 0; i < 6; i++) {
		printf("(%d) Père ..\n", getpid());
		sleep(2);
	}
	wait_returned_value = wait(NULL);
	printf("(%d) Père : j'ai pris en compte la terminaison de mon fils %d\n", getpid(),
	       wait_returned_value);
	exit(EXIT_SUCCESS);
}
