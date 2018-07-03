/********************************
 * Fichier handlers.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <sys/types.h>		// getpid
#include <signal.h>		// signal
#include <string.h>		// strsignal
#include <stdio.h>		// fprintf
#include <unistd.h>		// getpid

// Definition du nouveau gestionnaire de signal, celui-ci a pour paramètre le signal l'ayant déclenché
void nouveauGestionnaire(int numSignal)
{
	fprintf(stderr,
		"(%d) J'ai reçu le signal %s (%d), mais je n'abopte pas le comportement par défaut qui lui est associé. \n",
		getpid(), strsignal(numSignal), numSignal);
}

//Affectation du nouveau gestionnaire à tous les signaux possibles
void affectationGestionnaires()
{

	int numSignal;

	// Pour récupérer la valeur retour de la primitive signal
	typedef void (*sighandler_t) (int);
	sighandler_t return_value_signal;

	// Pour chaque signal
	for (numSignal = 1; numSignal < 32; numSignal++)
		// Associer (si possible) le nouveau gestionnaire de signal
		// NB : les signaux SIGSTOP (19) et SIGKILL (9) ne peuvent pas être capturés
		return_value_signal = signal(numSignal, nouveauGestionnaire);
	if (return_value_signal == SIG_ERR) {
		fprintf(stderr, "Signal %s (%d) non capturé\n", strsignal(numSignal),
			numSignal);
	}
}

// Procédure (ré-)affectant le comportement par défaut à la réception de chaque signal
void razGestionnaires()
{
	int numSignal;
	for (numSignal = 1; numSignal < 32; numSignal++) {
		signal(numSignal, SIG_DFL);
	}
	// En echec pour SIGSTOP et SIGKILL mais sans conséquence fonctionnelle pour notre programme
}
