/********************************
 * Fichier exemple_msystem.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int my_system(char *cmd)
{
	int status;

	if (fork() == 0) {
		char *tab[10];
		char *token = strtok(cmd, " \n");
		int i = 0;
		while (token != NULL) {
			tab[i] = token;
			token = strtok(NULL, " \n");
			i = i + 1;
		}
		tab[i] = NULL;

		execvp(tab[0], tab);
	} else {
		wait(&status);
	}
	return status;
}

int main()
{
	char cmd[150];

	fgets(cmd, sizeof(cmd) / sizeof(char), stdin);
	my_system(cmd);

	exit(EXIT_SUCCESS);
}
