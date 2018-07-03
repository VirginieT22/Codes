/********************************
 * Fichier twiceV2.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		/* stderr, stdout, fprintf */
#include <unistd.h>		/* exec */
#include <stdlib.h>		/* EXIT_SUCCESS, EXIT_FAILURE */
#include <sys/wait.h>		/* wait */

int main(int argc, char *argv[])
{
	pid_t pid_fils = -1;	/* Pour récupérer la valeur retour de l'execution du fork */

	if (argc < 2) {
		fprintf(stderr,
			"Utiliser la syntaxe suivante : ./twice nom_commande [options] [arguments]. Par exemple ./twice ps aj");
		exit(EXIT_FAILURE);
	}
	pid_fils = fork();

	if (pid_fils == 0) {	/* Code affecté au premier processus fils */
		execvp(argv[1], &argv[1]);
		exit(EXIT_FAILURE);	// Cette ligne de code ne serait atteinte qu'en cas d'échec du recouvrement du code du fils
	}
	/* Code affecté au père */
	execvp(argv[1], &argv[1]);
	// Les lignes de code suivantes ne serait atteintes qu'en cas d'échec du recouvrement du code du père
	wait(NULL);		// Et oui, le père ne peut attendre son fils que si le recouvrement de son propre code a échoué...
	exit(EXIT_FAILURE);
}
