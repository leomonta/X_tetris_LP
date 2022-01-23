#include <stdio.h>

#include "multiplayer.h"
#include "singleplayer.h"
#include "utils.h"

int main() {

	/* salva il vecchio locale per ristabilirlo in seguito*/
	char *old_locale = setupLocale();

	printf("Seleziona la modalita' di gioco\n1) Giocatore singolo\n2) Due giocatori\n");

	switch (getIntStdin(1, 3)) {
	case 1:
		singlePlayerLoop();
		break;

	case 2:
		printf("Contro chi vuoi giocare?\n1) Un altro giocatore locale\n2) CPU\n");

		multiPlayerLoop(getIntStdin(1, 3) == 2);

		break;
	}

	printf("\n");

	cleanupLocale(old_locale);

	return 0;
}