#include <stdio.h>

#include "multiplayer.h"
#include "singleplayer.h"
#include "utils.h"

int main() {

	/* salva il vecchio locale per ristabilirlo in seguito*/
	char *old_locale = setupLocale();

	printf("Seleziona la modalita' di gioco\n1) Giocatore singolo\n2) Due giocatori\n3) CPU vs CPU\n");

	switch (getIntStdin(1, 4)) {
	case 1:
		singlePlayerLoop();
		break;

	case 2:
		printf("Contro chi vuoi giocare?\n1) Un altro giocatore locale\n2) CPU\n");

		multiPlayerLoop(0, getIntStdin(1, 3) == 2);

		break;

	case 3:

		multiPlayerLoop(1, 1);
	}

	printf("\n");

	cleanupLocale(old_locale);

	return 0;
}