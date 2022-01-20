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
		printf("Contro chi vuoi giocare?\n1) Un altro giocatore locale\n2) CPU");
		if (getIntStdin(1, 3) == 1) {

			multiPlayerLoop();
		} else {
			multiPlayerLoopAI();
		}

		break;
	}

	cleanupLocale(old_locale);
}