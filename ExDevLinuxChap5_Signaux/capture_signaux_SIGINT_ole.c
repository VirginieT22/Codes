/********************************
 * Fichier capture_signaux_SIGINT_ole.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf
#include <signal.h>		// signal
#include <unistd.h>		// pause, sleep
#include <string.h>		// strsignal
#include <stdlib.h>		// exit

void nouveau_gestionnaire(int);

int main(void)
{
	int i;

	// Pour récupérer la valeur retour de la primitive signal
	typedef void (*sighandler_t) (int);
	sighandler_t return_value_signal;

	// Affectation du nouveau gestionnaire
	return_value_signal = signal(SIGINT, nouveau_gestionnaire);
	if (return_value_signal == SIG_ERR) {
		fprintf(stderr, "Signal SIGINT non capturé\n");
	}
	
	// Travail courant du processus
	for (i = 1; i < 31; i++) {
	  printf("%d\n", i);
	  sleep(1);
	}
	exit(EXIT_SUCCESS);
}

// Definition du nouveau gestionnaire de signal, celui-ci a pour paramètre le signal l'ayant déclenché
void nouveau_gestionnaire(int numSignal)
{
	if (numSignal == SIGINT) {
		printf("Olé !\n");
	}
}
