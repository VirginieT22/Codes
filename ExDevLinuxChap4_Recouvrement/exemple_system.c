/********************************
 * Fichier exemple_system.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char cmd[150];

	fgets(cmd, sizeof(cmd) / sizeof(char), stdin);
	system(cmd);

	exit(EXIT_SUCCESS);
}
