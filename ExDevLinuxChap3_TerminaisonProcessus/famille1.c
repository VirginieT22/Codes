/********************************
 * Fichier famille1.c
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
	pid_t wait_return_value = -1;

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
			}
		}
	}
	/* Code dupliqué pour tous les processus (p1, p2, p3 et p4) */
	wait_return_value = wait(NULL);
	if (wait_return_value != -1) {
		printf("(PID : %d) débloqué par %d \n", getpid(), wait_return_value);
	}
	exit(EXIT_SUCCESS);
}
