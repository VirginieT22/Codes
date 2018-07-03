/********************************
 * Fichier revise_tes_tables_signal.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf, scanf
#include <stdlib.h>		// atoi, EXIT_SUCESS, EXIT_FAILURE, srand, rand
#include <signal.h>		// signal
#include <string.h>		// strsignal
#include <unistd.h>		// getpid, exit
#include <time.h>		// time
#include <unistd.h>		// alarm

// Variables déclarée globalement afin que la procédure gestionnaire y accéde
int a, b, solution;
// Affichage de la réponse "juste"
void affiche_reponse();
// Nouveau gestionnaire de signal à affectuer à SIGFPE
void nouveau_gestionnaire(int);

int main(int argc, char *argv[])
{
	int reponse;
	// Pour récupérer la valeur retour de la primitive signal
	typedef void (*sighandler_t) (int);
	sighandler_t return_value_signal;

	if (argc != 2) {
		printf("Syntaxe : %s sec \noù sec est le temps limite en secondes. \n",
		       argv[0]);
		exit(EXIT_FAILURE);
	}
	// Tirage aléatoire des deux nombres
	srand((unsigned int)time((time_t *) NULL));
	a = rand() % 11;
	srand((unsigned int)(time((time_t *) NULL) + a));	// Nouvelle graine
	b = rand() % 11;
	solution = a * b;

	// Nouveau gestionnaire associé au signal SIGALRM
	return_value_signal = signal(SIGALRM, nouveau_gestionnaire);
	if (return_value_signal == SIG_ERR) {
		fprintf(stderr, "Erreur programme~:Signal SIGALRM non capturé\n");
	}
	// Nouveau gestionnaire associé au signal SIGINT
	return_value_signal = signal(SIGINT, nouveau_gestionnaire);
	if (return_value_signal == SIG_ERR) {
		fprintf(stderr, "Erreur programme~:Signal SIGINT non capturé\n");
	}
	// Armement de l'horloge
	alarm((unsigned int)atoi(argv[1]));	// attention, si argv[1] est 0 alors l'alarme est désactivée

	// Interrogation de l'utilisateur
	fprintf(stdout,
		"Quel est le résultat de %d x %d ? Tu as %d secondes pour répondre, c'est parti ! \n",
		a, b, atoi(argv[1]));

	// Attente et lecture de la réponse de l'utilisateur si le temps de réponse est strictement supérieur à 0
	if (atoi(argv[1]) != 0) {
		scanf("%d", &reponse);
	}
	// Tests de la réponse founie par l'utilisateur
	if ((atoi(argv[1]) != 0) && (reponse == solution)) {
		fprintf(stdout, "Bravo !\n");
	} else {
		fprintf(stdout, "Faux ! ");
		affiche_reponse();
	}

	exit(EXIT_SUCCESS);
}

// Affichage de la réponse
void affiche_reponse()
{
	fprintf(stdout, "La solution de %d x %d est : %d \n", a, b, solution);
}

// Nouveau gestionnaire de signal, celui-ci a pour paramètre le signal l'ayant déclenché
void nouveau_gestionnaire(int numSignal)
{
	// On aurait pu déclarer deux procédures gestionnaires différentes 
	switch (numSignal) {
	case SIGALRM:{
			fprintf(stdout,
				"Réception de %s -> Trop tard, temps limite écoulé \n",
				strsignal(numSignal));
			affiche_reponse();
			exit(EXIT_SUCCESS);	// L'utilisateur est en erreur mais pas le programme
			break;
		}
	case SIGINT:{
			fprintf(stdout, "Réception de %s -> Tu donnes ta langue au chat \n",
				strsignal(numSignal));
			affiche_reponse();
			exit(EXIT_SUCCESS);	// L'utilisateur est en erreur mais pas le programme
			break;
		}
	}
}
