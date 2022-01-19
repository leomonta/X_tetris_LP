#include <wchar.h>
#include <time.h>
#include <stdlib.h>

#include "graphics.h"
#include "multiplayer.h"


int multiGameShouldEnd(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]) {
	return 0;
}

void multiPlayerLoop() {

	/* variabili per gestire gli input */
	int            inputColumn   = 0;
	int            inputTetr     = 0;
	const wchar_t *selectedTetr  = nullptr;
	int            inputRotation = 0;

	/* Variabili dei giocatori */
	int     pointsG1 = 0;
	int     pointsG2 = 0;
	wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH];
	wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH];

	/**
	 * Indice rispetto a allTetraminos per indicare i tetramini disponibili al giocatore
	 */
	unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X];

	multiSetup(runtimeTetraminos);

	clearScreen(screenG1);
	clearScreen(screenG2);

	while (!multiGameShouldEnd(screenG1, screenG2, runtimeTetraminos)) {
		/* code */
	}

}

void multiSetup(unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]) {

	unsigned i = 0;
	unsigned temp;

	temp = (unsigned)(time(0));
	srand(temp);

	for (i = 0; i < INITIAL_TETRAMINOS_2X; i++) {
		runtimeTetraminos[i] = (unsigned char)(rand() % NUM_TETRAMINOS);
	}
}