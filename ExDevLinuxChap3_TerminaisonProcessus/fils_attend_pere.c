/********************************
 * Fichier fils_attend_pere.c
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
	int i;
	pid_fils = fork();	/* Création du processus fils */

	if (pid_fils == 0) {
		/* Code affecté au fils */
		printf("(%d) Je suis le fils, bonjour et aurevoir. \n", getpid());
		exit(EXIT_SUCCESS);
	} else {		/* Code affecté au père */
		printf("(%d) Je suis le pere, j'effectue mon traitement \n", getpid());
		for (i = 0; i < 10; i++) {
			printf("(%d) ..\n", getpid());
			sleep(2);
		}
		wait_returned_value = wait(NULL);
		printf
		    ("(%d) Je suis le père, mon fils %d est terminé depuis longtemps, et moi aussi maintenant... \n",
		     getpid(), wait_returned_value);
		exit(EXIT_SUCCESS);
	}
}
