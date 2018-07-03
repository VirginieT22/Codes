/********************************
 * Fichier tirage_aleatoire_avec_tableau_pid.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int i;
	long int N;
	pid_t tableau_pid[255], valeur_pid_retourne;
	if (argc - 1 != 1) {
		fprintf(stderr, "Usage : %s <NOMBRE>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	N = strtol(argv[1], (char **)NULL, 10);

	if (N <= 0 || N > 255) {
		fprintf(stderr, "<NOMBRE> doit être dans ]0,255]\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < N; i++) {
		tableau_pid[i] = fork();
		if (tableau_pid[i] == 0) {
			sleep(1);
			exit(EXIT_SUCCESS);
		}
	}

	valeur_pid_retourne = wait(NULL);
	i = 0;
	while (i < 255 && valeur_pid_retourne != tableau_pid[i]) {
		i = i + 1;
	}
	printf("valeur : %d\n", i);
	for (i = 0; i < N - 1; i++) {
		wait(NULL);
	}
	exit(EXIT_SUCCESS);
}
