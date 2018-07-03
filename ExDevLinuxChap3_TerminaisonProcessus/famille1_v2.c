/********************************
 * Fichier famille1_v2.c
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
	pid_t pid_p2 = -1, pid_p3 = -1, pid_p4 = -1;

	printf("(PID : %d, PPID : %d) p1- Bonjour\n", getpid(), getppid());

	pid_p2 = fork();
	if (pid_p2 == 0) {	/* Code associé à p2 */
		printf("(PID : %d, PPID : %d) p2- Bonjour\n", getpid(), getppid());
		pid_p3 = fork();
		if (pid_p3 == 0) {	/* Code associé à p3 */
			printf("(PID : %d, PPID : %d) p3- Bonjour\n", getpid(), getppid());
			pid_p4 = fork();
			if (pid_p4 == 0) {	/* Code associé à p4 */
				printf("(PID : %d, PPID : %d) p4- Bonjour\n", getpid(),
				       getppid());
				sleep(10);
				printf("(PID : %d) Aurevoir. \n", getpid());
				exit(EXIT_SUCCESS);
			} else {	/* Code associé à p3 */
				waitpid(pid_p4, NULL, 0);
				printf("(PID : %d) débloqué par %d, Aurevoir. \n", getpid(),
				       pid_p4);
				exit(EXIT_SUCCESS);
			}
		} else {	/* Code associé à p2 */
			waitpid(pid_p3, NULL, 0);
			printf("(PID : %d) débloqué par %d, aurevoir. \n", getpid(), pid_p3);
			exit(EXIT_SUCCESS);
		}
	} else {		/* Code associé à p1 */
		waitpid(pid_p2, NULL, 0);
		printf("(PID : %d) Débloqué par %d, aurevoir. \n", getpid(), pid_p2);
		exit(EXIT_SUCCESS);
	}
}
