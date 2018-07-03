/********************************
 * Fichier capture_signaux_IGN.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf
#include <signal.h>		// signal
#include <unistd.h>		// pause
#include <string.h>		// strsignal

int main(void)
{
	int numSignal;

	// Pour récupérer la valeur retour de la primitive signal
	typedef void (*sighandler_t) (int);
	sighandler_t return_value_signal;

	// Pour chaque signal
	for (numSignal = 1; numSignal < 32; numSignal++)
		// Associer (si possible) un nouveau gestionnaire de signal consistant à ignorer le signal
		// NB : les signaux SIGSTOP (19) et SIGKILL (9) ne peuvent pas être capturés
		return_value_signal = signal(numSignal, SIG_IGN);
	if (return_value_signal == SIG_ERR) {
		fprintf(stderr, "Signal %s (%d) non capturé\n", strsignal(numSignal),
			numSignal);
	}
	// Ligne suivante peu élégante mais permettant au programme de se plaçer systématiquement en attente d'un signal
	while (1)
		pause();
}
