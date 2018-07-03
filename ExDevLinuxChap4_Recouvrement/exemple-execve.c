/********************************
 * Fichier exemple-execve.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		/* stderr, stdout, fprintf, perror */
#include <unistd.h>		/* exec */
#include <stdlib.h>		/* EXIT_FAILURE */

int main(void)
{
	char *arg[] = { "ps", "-j", "-a", "-r", (char *)NULL };
	fprintf(stdout, "Je vais executer ps -j -a -r\n");
	execve("/bin/ps", arg, NULL);
	/*
	 * La suite du code ne sera atteinte qu'en cas d'échec du
	 * recouvrement
	 */
	perror("Je suis du code executé en d'échec du recouvrement execve \n");
	exit(EXIT_FAILURE);
}
