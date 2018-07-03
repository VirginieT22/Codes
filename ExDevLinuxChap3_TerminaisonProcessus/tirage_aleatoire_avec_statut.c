/********************************
 * Fichier tirage_aleatoire_avec_statut.c
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
		if (fork() == 0) {
			sleep(1);
			exit(i);
		}
	}

	wait(&i);
	printf("valeur : %d\n", WIFEXITED(i) ? WEXITSTATUS(i) : -1);
	for (i = 0; i < N - 1; i++) {
		wait(NULL);
	}
	exit(EXIT_SUCCESS);
}
