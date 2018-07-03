/********************************
 * Fichier capture_signaux_fils.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <sys/types.h>		// getpid
#include <signal.h>		// signal, kill
#include <unistd.h>		// pause, fork, exit, getpid
#include <stdio.h>		// fprintf
#include <stdlib.h>		// srand, rand
#include <time.h>		// time
#include "handlers.h"		// Voir handlers.c

int main(void)
{
	pid_t pid_pere;
	pid_t pid_fils;
	int i;

	pid_pere = getpid();

	affectationGestionnaires();	// Effectué avant la création du fils afin que le père soit opérationnel dès le début du code d'exécution du fils

	pid_fils = fork();

	if (pid_fils == 0) {	// Code affecté au fils
		razGestionnaires();	// Ré-affectation des comportements par défaut
		for (i = 0; i < 20; i++) {	// 20 fois
			sleep(1);
			// Envoi au père d'un signal tiré aléatoirement entre 1 et 31 (donc SIGKILL inclus)
			srand((unsigned int)time((time_t *) NULL));
			kill(pid_pere, (rand() % 31) + 1);
		}
		kill(pid_pere, SIGKILL);	// Le dernier signal est un SIGKILL pour terminer le père
		exit(EXIT_SUCCESS);
	} else {		// Code affecté au père
		// Ligne suivante peu élégante mais permettant bien au programme de se plaçer systématiquement en attenrte d'un signal
		while (1)
			pause();
	}
}
