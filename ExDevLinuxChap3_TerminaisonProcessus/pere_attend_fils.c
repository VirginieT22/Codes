/********************************
 * Fichier pere_attend_fils.c
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
	pid_t wait_returned_value = -1;
	pid_fils = fork();	/* Création du processus fils */
	int i;

	if (pid_fils == 0) {
		/* Code affecté au fils */
		printf("(%d) Je suis le fils, j'effectue mon traitement \n", getpid());
		for (i = 0; i < 10; i++) {
			printf("(%d) ..\n", getpid());
			sleep(2);
		}
		printf("(%d) Je suis le fils, j'ai fini mon traitement \n", getpid());
		exit(EXIT_SUCCESS);
	} else {		/* Code affecté au père */
		printf("(%d) Je suis le père, j'attends mon fils. \n", getpid());
		wait_returned_value = wait(NULL);
		printf("(%d) Je suis le père, mon fils %d est terminé, et moi aussi... \n",
		       getpid(), wait_returned_value);
		exit(EXIT_SUCCESS);
	}
}
