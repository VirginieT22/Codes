/********************************
 * Fichier capture_signaux_3SIGINT_v2.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf
#include <signal.h>		// signal
#include <unistd.h>		// pause
#include <string.h>		// strsignal
#include <stdlib.h>		// exit

void capture2fois(int);

int nbSIGINT = 0;

int main(void)
{
	// Pour récupérer la valeur retour de la primitive signal
	typedef void (*sighandler_t) (int);
	sighandler_t return_value_signal;

	return_value_signal = signal(SIGINT, capture2fois);
	if (return_value_signal == SIG_ERR) {
		fprintf(stderr, "Signal SIGINT non capturé\n");
	}
	// Ligne suivante peu élégante mais permettant bien au programme de se plaçer systématiquement en attenrte d'un signal
	while (1)
		pause();
}

  // Definition du nouveau gestionnaire de signal, celui-ci a pour paramètre le signal l'ayant déclenché
void capture2fois(int numSignal)
{
	nbSIGINT++;
	fprintf(stderr, "(%d) Et de %d (%s) ... \n", getpid(), nbSIGINT, strsignal(numSignal));
	if (nbSIGINT == 2) {
		signal(SIGINT, SIG_DFL);
	}
}
