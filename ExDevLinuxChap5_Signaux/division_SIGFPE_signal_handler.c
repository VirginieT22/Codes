/********************************
 * Fichier division_SIGFPE_signal_handler.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf
#include <stdlib.h>		// atoi, EXIT_SUCESS, EXIT_FAILURE
#include <signal.h>		// signal
#include <string.h>		// strsignal
#include <unistd.h>		// getpid, exit

void nouveauGestionnaire(int);

int main(int argc, char *argv[])
{
	int num, denom;
	// Pour récupérer la valeur retour de la primitive signal
	typedef void (*sighandler_t) (int);
	sighandler_t return_value_signal;

	if (argc != 3) {
		printf("Syntaxe : %s entier_nunerateur entier_denominateur \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	num = atoi(argv[1]);
	denom = atoi(argv[2]);

	return_value_signal = signal(SIGFPE, nouveauGestionnaire);
	if (return_value_signal == SIG_ERR) {
		fprintf(stderr, "Signal SIGFPE non capturé\n");
	}
	printf("Le résultat de %d/%d est %d, et le reste est %d.\n", num, denom,
	       num / denom, num % denom);
	exit(EXIT_SUCCESS);
}

  // Definition du nouveau gestionnaire de signal, celui-ci a pour paramètre le signal l'ayant déclenché
void nouveauGestionnaire(int numSignal)
{
	fprintf(stderr, "(%d) J'ai reçu le signal %s (%d), division par 0. \n",
		getpid(), strsignal(numSignal), numSignal);
}
