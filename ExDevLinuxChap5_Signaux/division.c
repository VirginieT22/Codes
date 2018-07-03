/********************************
 * Fichier division.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf
#include <stdlib.h>		// atoi, EXIT_SUCESS, EXIT_FAILURE
#include <unistd.h>		// getpid, exit

void nouveauGestionnaire(int);

int main(int argc, char *argv[])
{
	int num, denom;

	if (argc != 3) {
		printf("Syntaxe : %s entier_nunerateur entier_denominateur \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	num = atoi(argv[1]);
	denom = atoi(argv[2]);

	printf("Le résultat de %d/%d est %d, et le reste est %d.\n", num, denom, num / denom,
	       num % denom);
	exit(EXIT_SUCCESS);
}
