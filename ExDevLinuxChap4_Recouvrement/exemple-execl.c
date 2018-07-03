/********************************
 * Fichier exemple-execl.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		/* stderr, stdout, fprintf */
#include <unistd.h>		/* exec */
#include <stdlib.h>		/* EXIT_FAILURE */

int main(void)
{

	fprintf(stdout, "Je vais lancer ps -j -a -r\n");
	execl("/bin/ps", "ps", "-j", "-a", "-r", (char *)NULL);
	/*
	 * La suite du code ne sera atteint qu'en cas d'échec du
	 * recouvrement
	 */
	perror("Je suis du code n'étant executé qu'en cas d'erreur\n");
	exit(EXIT_FAILURE);
}
