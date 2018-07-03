/********************************
 * Fichier twiceV1.c
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
	pid_t pid_fils1 = -1;	/* Pour récupérer la valeur retour de l'exécution du premier fork */
	pid_t pid_fils2 = -1;	/* Pour récupérer la valeur retour de l'exécution du deuxième fork */

	if (argc < 2) {
		fprintf(stderr,
			"Utiliser la syntaxe suivante : ./twice nom_commande [options] [arguments]. Par exemple ./twice ps aj");
		exit(EXIT_FAILURE);
	}
	pid_fils1 = fork();

	if (pid_fils1 == 0) {	/* Code affecté au premier processus fils */
		execvp(argv[1], &argv[1]);
		// La ligne suivante ne sera atteinte qu'en cas d'échec du recouvrement ci-dessus
		exit(EXIT_FAILURE);
	}
	pid_fils2 = fork();

	if (pid_fils2 == 0) {	/* Code affecté au second processus fils */
		execvp(argv[1], &argv[1]);
		// La ligne suivante ne sera atteinte qu'en cas d'échec du recouvrement ci-dessus
		exit(EXIT_FAILURE);
	}
	/* Code affecté au père */
	wait(NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
