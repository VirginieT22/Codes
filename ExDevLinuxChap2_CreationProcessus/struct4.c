/********************************
 * Fichier struct4.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		/* stderr, stdout, fprintf */
#include <unistd.h>		/* fork */
#include <sys/wait.h>		/* wait */
#include <stdlib.h>		/* exit */

int main(void)
{
	int i;
	int j = 0;
	for (i = 0; i < 2; i++) {
		fork();
		j++;
		printf("Bonjour ! (moi :%d, mon pere : %d), j=%d\n", getpid(), getppid(), j);
	}
	printf("Bonjour ! (moi :%d, mon pere : %d), j=%d\n", getpid(), getppid(), j);
	wait(NULL);
	exit(0);
}
