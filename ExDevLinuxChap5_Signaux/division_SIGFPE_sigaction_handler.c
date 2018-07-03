/********************************
 * Fichier division_SIGFPE_sigaction_handler.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf
#include <stdlib.h>		// atoi, EXIT_SUCESS, EXIT_FAILURE
#include <string.h>		// strsignal
#include <unistd.h>		// getpid, exit
#include <signal.h>		// sigacion, sigemptyset

void nouveauGestionnaire(int);

int main(int argc, char *argv[])
{
	int num, denom;
	struct sigaction new_action;
	struct sigaction old_action;
	int return_value_sigaction;

	// Remplissage de la structure sigaction pour ne nouveau gestionnaire
	new_action.sa_handler = nouveauGestionnaire;	// nouveau gestionnaire de signal
	sigemptyset(&(new_action.sa_mask));	// liste des signaux bloqués pendant l'exécution de sa_handler, vidée
	sigaddset(&(new_action.sa_mask), SIGFPE);	// Implicitement effectué par défaut
	new_action.sa_flags = SA_RESTART;	/*FIXME : version Virginie SA_RESETHAND qui pose un pb de definition de constante unsigned stockée dans un signed */

	if (argc != 3) {
		printf("Syntaxe : %s entier_nunerateur entier_denominateur \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	num = atoi(argv[1]);
	denom = atoi(argv[2]);

	return_value_sigaction = sigaction(SIGFPE, &new_action, &old_action);
	if (return_value_sigaction != 0) {
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
