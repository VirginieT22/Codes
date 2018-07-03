/********************************
 * Fichier revise_tes_tables_sigaction.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf, scanf
#include <stdlib.h>		// atoi, EXIT_SUCESS, EXIT_FAILURE, srand, rand
#include <signal.h>		// sigacion, sigemptyset
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
	struct sigaction new_action;
	int return_value_sigaction;

	// Remplissage de la structure sigaction pour ne nouveau gestionnaire
	new_action.sa_handler = nouveau_gestionnaire;	// nouveau gestionnaire de signal
	sigemptyset(&(new_action.sa_mask));	// liste des signaux bloqués pendant l'exécution de sa_handler
	sigaddset(&(new_action.sa_mask), SIGALRM);
	sigaddset(&(new_action.sa_mask), SIGINT);
	new_action.sa_flags = 0;	// Pas de configuration particulière des flags

	if (argc != 2) {
		printf("Syntaxe : %s sec \noù sec est le temps limite en secondes. \n",
		       argv[0]);
		exit(EXIT_FAILURE);
	}
	// Tirage aléatoire des deux nombres
	srand((unsigned int)(time((time_t *) NULL)));
	a = rand() % 11;
	srand((unsigned int)(time((time_t *) NULL)));	// Nouvelle graine
	b = rand() % 11;
	solution = a * b;
	// Nouveau gestionnaire associé au signal SIGALRM
	return_value_sigaction = sigaction(SIGALRM, &new_action, NULL);	// Pas de sauvegarde de l'ancienne action
	if (return_value_sigaction != 0) {
		fprintf(stderr, "Signal SIGALRM non capturé\n");
	}
	// Nouveau gestionnaire associé au signal SIGALRM
	return_value_sigaction = sigaction(SIGINT, &new_action, NULL);	// Pas de sauvegarde de l'ancienne action
	if (return_value_sigaction != 0) {
		fprintf(stderr, "Signal SIGINT non capturé\n");
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

// Definition du nouveau gestionnaire de signal, celui-ci a pour paramètre le signal l'ayant déclenché
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
