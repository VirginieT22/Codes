/********************************
 * Fichier appel_ls_execv.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		/* stderr, stdout, fprintf */
#include <unistd.h>		/* exec */
#include <stdlib.h>		/* EXIT_FAILURE */
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid_fils = -1;	/* Pour récupérer la valeur de
				 * retour de l'execution du fork */
	pid_fils = fork();

	if (pid_fils == 0) {	// Code associé au processus fils
		char *cmd[] = { "ls", "-l", "-h", (char *)NULL };
		execvp("/bin/ls", cmd);
		/* La suite du code ne sera atteinte qu'en cas d'échec du recouvrement */
		fprintf(stdout, "Echec du recouvrement\n");
		exit(EXIT_FAILURE);
	}
	// La suite du code est nécessairement exécuté par le processus père seulement
	wait(NULL);		// Le processus père attend son fils
	fprintf(stdout, "Sortie du programme\n");
	exit(EXIT_SUCCESS);
}
