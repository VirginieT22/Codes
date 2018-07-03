/********************************
 * Fichier shebang.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
/* _GNU_SOURCE permet l'utilisation de asprintf */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{

	char **commande;
	unsigned int i;

	commande = (char **)calloc((size_t) argc + 3, sizeof(char *));

	commande[0] = "/bin/bash";

	commande[1] = "-c";

	asprintf(&(commande[2]), "%s", argv[1]);
	for (i = 1; i < (unsigned int)argc; i++) {
		asprintf(&(commande[i + 2]), "%s", argv[i]);
	}

	execvp("/bin/bash", commande);

	return EXIT_FAILURE;

}
