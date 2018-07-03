/********************************
 * Fichier famille5.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		/* stderr, stdout, fprintf */
#include <unistd.h>		/* fork */
#include <sys/wait.h>		/* wait */
#include <stdlib.h>		/* exit */

void cascade(int n)
{
	pid_t fils_gauche = -1, fils_droit = -1;
	if (n > 0) {
		fils_gauche = fork();
		if (fils_gauche != 0) {	/* Code père */
			printf("Bonjour, je suis %d et mon père est %d.\n", getpid(),
			       getppid());
			fils_droit = fork();
			if (fils_droit == 0) {	/* Code fils droit */
				printf
				    ("Bonjour, je suis %d et mon père est %d. Je lance cascada(%d)\n",
				     getpid(), getppid(), n - 1);
				cascade(n - 1);
			} else {	/* Code père */
				wait(NULL);	// Attente des fils
				wait(NULL);	// gauche et droit
			}
		} else {	/* Code fils gauche */
			printf("Bonjour, je suis %d et mon père est %d.\n", getpid(),
			       getppid());
			sleep(10);
			exit(EXIT_SUCCESS);
		}
	}
}

int main(void)
{
	cascade(4);
	exit(EXIT_SUCCESS);
}
