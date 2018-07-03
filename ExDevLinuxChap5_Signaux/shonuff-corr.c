/********************************
 * Fichier shonuff-corr.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

FILE *file;
pid_t pid_fils;
int piste = 1;
int position_titre = 0;
int i, j;

char titres[][47] = {
	"The Rockafeller Skank (2006 Digital Remaster)",
	"Praise You",
	"Brimful Of Asha (Norman Cook Remix)",
	"Weapon Of Choice (2006 Digital Remaster)",
	"Gangster Trippin",
	"I See You Baby (Fatboy Slim Remix)",
	"Wonderful Night",
	"Right Here, Right Now",
	"Going Out Of My Head",
	"Sunset (Bird Of Prey)",
	"Everybody Loves A Carnival"
};

void numero_piste()
{
	file = fopen("FatBoySlimGreatestHits.txt", "a");	// Ouvre le fichier nomm'e "FatBoySlimGreatestHits.txt". L'option "a" permet d'ecrire `a la fin du fichier (sans en effacer le contenu du fichier)
	fprintf(file, "%d - ", piste);
	fclose(file);
	piste++;
}

void titre()
{
	file = fopen("FatBoySlimGreatestHits.txt", "a");
	fprintf(file, "%s \n", titres[position_titre]);
	fclose(file);
	position_titre++;
}

void autre_traitement(useconds_t i)
{
	// Fonction simulant le temps pass'e par le processus pour un autre traitement
	usleep(i);
}

int main()
{
	// Creates and truncates the file FatBoySlimGreatestHits.txt
	file = fopen("FatBoySlimGreatestHits.txt", "w");	// Ouvre le fichier nomm'e "FatBoySlimGreatestHits.txt". L'option "w" permet de supprimer le contenu actuel du fichier.
	fclose(file);

	pid_fils = fork();

	if (pid_fils == 0) {	// FILS : affiche les numéros de piste
		signal(SIGUSR2, numero_piste);	// <- Affectation gestionnaire : lance numero_piste() dès que recoit SIGUSR2
		for (i = 0; i < 11; i++) {
			autre_traitement(22000);
			pause();	// <- Se met en pause (en attendant SIGUSR2)
			if (kill(getppid(), SIGUSR1)) {
				perror("erreur kill(getppid(),SIGUSR1)");
				return 1;
			};	// <- Envoie le signal SIGUSR1 au pere pour le d'ebloquer
		}
		exit(EXIT_SUCCESS);
	} else {		// PERE : affiche les titres
		signal(SIGUSR1, titre);	// <- Affectation gestionnaire : lance titre() dès que recoit SIGUSR1
		for (j = 0; j < 11; j++) {
			printf("Traitement : %d/11\n", j + 1);
			autre_traitement(36000);
			if (kill(pid_fils, SIGUSR2) == -1) {
				perror("erreur kill(pid_fils,SIGUSR2)");
				return 1;
			};	// <- Envoie le signal SIGUSR2 au fils pour le d'ebloquer
			pause();	// <- Se met en pause (en attendant SIGUSR1)
		}
		wait(NULL);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
}
