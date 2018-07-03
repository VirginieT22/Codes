/********************************
 * Fichier twice.c
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
	int status_premier_fils_fini = EXIT_SUCCESS;	/* Pour récupérer la valeur retour du premier fils */
	int status_second_fils_fini = EXIT_SUCCESS;	/* Pour récupérer la valeur retour du premier fils */
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
	wait(&status_premier_fils_fini);
	wait(&status_second_fils_fini);
	if (WIFEXITED(status_premier_fils_fini)
	    && WIFEXITED(status_second_fils_fini)
	    &&
	    ((WEXITSTATUS(status_premier_fils_fini) != EXIT_SUCCESS
	      || WEXITSTATUS(status_premier_fils_fini) != EXIT_SUCCESS)))
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
	// Pour consulter la valeur de errno, utiliser la commande echo $? après l'exécution du programme
}
