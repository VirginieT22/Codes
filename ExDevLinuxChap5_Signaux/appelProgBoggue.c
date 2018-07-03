/********************************
 * Fichier appelProgBoggue.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf
#include <stdlib.h>		// EXIT_SUCCESS
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
	if (p_etudiant(&a, d) == false) {
		printf("-> p_etudiant a passé le test\n");
	} else {
		printf("-> p_etudiant n'a pas a passé le test\n");
	}

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
