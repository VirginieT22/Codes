/********************************
 * Fichier affiche_suite_entiers.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf
#include <unistd.h>		// sleep
#include <stdlib.h>		// exit

int main(void)
{
	int i;
	for (i = 1; i < 31; i++) {
		printf("%d\n", i);
		sleep(1);
	}
	exit(EXIT_SUCCESS);
}
