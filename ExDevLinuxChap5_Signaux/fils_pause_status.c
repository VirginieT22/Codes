/********************************
 * Fichier fils_pause_status.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <sys/types.h>		// getpid
#include <unistd.h>		// pause, fork, exit, getpid
#include <stdio.h>		// fprintf
#include <sys/wait.h>		// wait
#include <stdlib.h>		// exit
#include <string.h>		// strsignal

void nouveauGestionnaire(int);

int main(void)
{
	pid_t pid_fils;
	pid_t return_value_wait;
	int status;

	//Création du processus fils
	pid_fils = fork();

	if (pid_fils == 0) {	// Code affecté au fils
		signal(SIGUSR1, nouveauGestionnaire);	// Gestionnaire capturant les signaux SIGUSR1
		fprintf(stdout,
			"Je suis le fils, mon PID est %d. Envoyez-moi un signal !\n",
			getpid());
		pause();
		fprintf(stdout, "Merci à vous, je vous quitte\n");
		exit(EXIT_SUCCESS);
	} else {		// Code affecté au père, man 2 wait
		do {
			return_value_wait = waitpid(pid_fils, &status, WUNTRACED | WCONTINUED);
			if (return_value_wait == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}

			if (WIFEXITED(status)) {
				printf("child exited, status=%d\n", WEXITSTATUS(status));
			} else if (WIFSIGNALED(status)) {
				printf("child killed by signal %d\n", WTERMSIG(status));
			} else if (WIFSTOPPED(status)) {
				printf("child stopped by signal %d\n", WSTOPSIG(status));
			} else if (WIFCONTINUED(status)) {
				printf("child continued\n");
			}
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
		exit(EXIT_SUCCESS);
	}
}

// Definition du nouveau gestionnaire de signal, celui-ci a pour paramètre le signal l'ayant déclenché
void nouveauGestionnaire(int numSignal)
{
	fprintf(stderr, "(%d) J'ai capturé le signal %s (%d). \n", getpid(),
		strsignal(numSignal), numSignal);
}
