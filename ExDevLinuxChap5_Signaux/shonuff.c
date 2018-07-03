/********************************
 * Fichier shonuff.c
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

char titres[][47] = { "The Rockafeller Skank (2006 Digital Remaster)", "Praise You",
	"Brimful Of Asha (Norman Cook Remix)", "Weapon Of Choice (2006 Digital Remaster)",
	"Gangster Trippin", "I See You Baby (Fatboy Slim Remix)", "Wonderful Night",
	"Right Here, Right Now", "Going Out Of My Head", "Sunset (Bird Of Prey)",
	"Everybody Loves A Carnival"
};

void numero_piste()
{
	file = fopen("FatBoySlimGreatestHits.txt", "a");
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
	// Fonction simulant le temps passé par le processus pour un autre traitement
	usleep(i);
}

int main()
{
	file = fopen("FatBoySlimGreatestHits.txt", "w");
	fclose(file);
	pid_fils = fork();

	if (pid_fils == 0) {
		for (i = 0; i < 11; i++) {
			autre_traitement(22000);
			numero_piste();
		}
		exit(EXIT_SUCCESS);
	} else {
		for (j = 0; j < 11; j++) {
			printf("Traitement : %d/11\n", j + 1);
			autre_traitement(36000);
			titre();
		}
		wait(NULL);
		wait(NULL);
		printf
		    ("Traitement terminé : consultez le fichier FatBoySlimGreatestHits.txt \n");
		exit(EXIT_SUCCESS);
	}
}
