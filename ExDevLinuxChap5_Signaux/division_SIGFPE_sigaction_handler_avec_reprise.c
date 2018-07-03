/********************************
 * Fichier division_SIGFPE_sigaction_handler_avec_reprise.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// fprintf
#include <stdlib.h>		// atoi, EXIT_SUCESS, EXIT_FAILURE
#include <signal.h>		// signal
#include <string.h>		// strsignal
#include <unistd.h>		// getpid, exit
#include <setjmp.h>
#include <limits.h>

static jmp_buf context;

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

	struct sigaction sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = nouveauGestionnaire;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGFPE, &sa, NULL);

	if (setjmp(context)) {
		/* If this one was on setjmp's block,
		 * it would need to be volatile, to
		 * make sure the compiler reloads it.
		 */
		sigset_t ss;

		/* Make sure to unblock SIGFPE, according to POSIX it
		 * gets blocked when calling its signal handler.
		 * sigsetjmp()/siglongjmp would make this unnecessary.
		 */
		sigemptyset(&ss);
		sigaddset(&ss, SIGFPE);
		sigprocmask(SIG_UNBLOCK, &ss, NULL);

		goto skip;
	}

	printf("Le résultat de %d/%d est %d, et le reste est %d.\n", num, denom,
	       num / denom, num % denom);
 skip:

	printf("FIN.\n");
	exit(EXIT_SUCCESS);
}

  // Definition du nouveau gestionnaire de signal, celui-ci a pour paramètre le signal l'ayant déclenché
void nouveauGestionnaire(int numSignal)
{
	fprintf(stderr, "(%d) J'ai reçu le signal %s (%d), division par 0. \n",
		getpid(), strsignal(numSignal), numSignal);
	longjmp(context, 1);
}
