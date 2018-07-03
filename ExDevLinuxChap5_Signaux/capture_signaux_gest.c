/********************************
 * Fichier capture_signaux_gest.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf
#include <signal.h>		// signal
#include <unistd.h>		// pause
#include <string.h>		// strsignal

void nouveauGestionnaire(int);

int main(void)
{
	int numSignal;

	// Pour récupérer la valeur retour de la primitive signal
	typedef void (*sighandler_t) (int);
	sighandler_t returnValueSignal;

	// Pour chaque signal
	for (numSignal = 1; numSignal < 32; numSignal++)
	  {
	    // Associer (si possible) le nouveau gestionnaire de signal
	    // NB : les signaux SIGSTOP (19) et SIGKILL (9) ne peuvent pas être capturés
	    returnValueSignal = signal(numSignal, nouveauGestionnaire);
	    if (returnValueSignal == SIG_ERR) {
	      fprintf(stderr, "Signal %d (%s) non capturé\n", numSignal, strsignal(numSignal));
	    }
	  }
	
	// Ligne suivante peu élégante mais permettant bien au programme de se plaçer systématiquement en attenrte d'un signal
	while (1)
	  pause();
}

  // Definition du nouveau gestionnaire de signal, celui-ci a pour paramètre le signal l'ayant déclenché
void nouveauGestionnaire(int numSignal)
{
	fprintf(stderr,
		"(%d) J'ai reçu le signal %d (%s), mais je n'abopte pas le comportement par défaut qui lui est associé. \n",
		getpid(), numSignal, strsignal(numSignal));
}
