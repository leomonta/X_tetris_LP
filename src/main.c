#include <stdio.h>

#include "multiplayer.h"
#include "singleplayer.h"
#include "utils.h"

int main() {

	char *old_locale = setupLocale();

	printf("Seleziona la modalita' di gioco\n1) Giocatore singolo\n2) Due giocatori\n");

	switch (getIntStdin(1, 3)) {
	case 1:
		singlePlayerLoop();
		break;

	case 2:
		multiPlayerLoop();
		break;
	}

	cleanupLocale(old_locale);
}