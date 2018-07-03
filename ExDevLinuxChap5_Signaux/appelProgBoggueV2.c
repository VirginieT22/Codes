/********************************
 * Fichier appelProgBoggueV2.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf
#include <stdlib.h>		// exit, EXIT_SUCCESS
#include <unistd.h>		// fork
#include <sys/wait.h>		// wait
#include <string.h>		// strsignal

typedef int bool;
#define true 1
#define false 0

int p_etudiant(int *, int *);

int main(void)
{
	int a = 1, b = 2;
	int *c = &a, *d = NULL;

	printf("TEST 1\n");
	if (p_etudiant(&a, &b) == false) {
		printf("-> p_etudiant a passé le test\n");
	} else {
		printf("-> p_etudiant n'a pas a passé le test\n");
	}

	printf("TEST 2\n");
	if (p_etudiant(&a, c) == true) {
		printf("-> p_etudiant a passé le test\n");
	} else {
		printf("-> p_etudiant n'a pas a passé le test\n");
	}

	printf("TEST 3\n");
	// Test de la fonction avec un pointeur initialisé à NULL...
	// On test dans un fils si le programme étudiant lève une erreur de segmentation
	pid_t fils_test3 = fork();	// pour bien faire, il faudrait traiter le cas d'erreur de fork
	int status;
	if (fils_test3 == 0) {
		p_etudiant(&a, d);
		exit(EXIT_SUCCESS);
	}
	waitpid(fils_test3, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
		// p_etudiant s'est terminé normalement en particulier n'a pas été interrompu par un signal
		// On peut lancer le test 3 sans crainte
	{
		if (p_etudiant(&a, d) == false) {
			printf("-> p_etudiant a passé le test\n");
		} else {
			printf("-> p_etudiant n'a pas a passé le test\n");
		}
	}
	if (WIFSIGNALED(status)) {
		printf("Crash du programme sur test3 pour cause de %s\n",
		       strsignal(WTERMSIG(status)));
	};

	// Autres tests
	printf("AUTRES TESTS\n");
	printf("ICI SE TROUVERA LE CODE DE TOUS LES AUTRES TESTS FONCTIONNELS A PASSER\n");

	exit(EXIT_SUCCESS);
}

/* La fonction étudiant à tester, on ne doit pas modifier son code, on ne doit même pas avoir à l'inspecter pour lui faire passer les tests automatiques */
int p_etudiant(int *a, int *b)
{
	printf("Comparaison des adresses contenant %d et %d ", *a, *b);	// Aille, si l'un des pointeurs n'est pas initialisé, gare au segmentation fault
	if (a == b)
		return 1;
	else
		return 0;
}
