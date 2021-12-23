#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"
#include "singleplayer.h"
#include "tetramino.h"

void singlePlayerLoop() {

	int            i             = 1;
	int            inputColumn   = 0;
	int            inputTetr     = 0;
	const wchar_t *selectedTetr  = nullptr;
	int            points        = 0;
	int            inputRotation = 0;
	wchar_t        screen[SCREEN_HEIGHT][SCREEN_WIDTH];

	/**
	 * Indice rispetto a allTetramino per indicare i tetramini disponibili al giocatore
	 */
	unsigned char runtimeTetraminos[INITIAL_TETRAMINOS];

	setup(screen, runtimeTetraminos);

	clearScreen(screen);

	/* loop 1 */
	while (!gameShouldEnd(screen, runtimeTetraminos)) {

		drawRemainingTetraminos(runtimeTetraminos);

		printf("Scegli il tetramino\n");
		inputTetr = getIntStdin(0, INITIAL_TETRAMINOS);

		if (runtimeTetraminos[inputTetr] == INVALID_TETRAMINO) {
			printf("Il tetramino n. %d è già stato usato, sceglierne un'altro!\n", inputTetr);
			continue;
		}

		printf("Scegli la rotazione, da 0 a 3\n");
		inputRotation = getIntStdin(0, 4);

		selectedTetr = allTetraminos[runtimeTetraminos[inputTetr]];

		drawSingleTetramino(runtimeTetraminos[inputTetr], inputRotation);

		printf("\n\nScegli la colonna\n");
		inputColumn = getIntStdin(0, SCREEN_WIDTH);

		if (!insert(runtimeTetraminos[inputTetr], screen, inputColumn, inputRotation)) {
			/* fallimento */
			replaceTempTetr(L' ', screen);

			printf("il tetramino selezionato non può essere posizionato dove richiesto\n");

			continue;
		}

		runtimeTetraminos[inputTetr] = INVALID_TETRAMINO;

		fall(screen);
		replaceTempTetr(selectedTetr[1], screen);

		points += calcPoints(clearLines(screen));

		drawScreen(screen);
		printf("punti -> %d\n\n", points);
	}

	printf("Gioco finto!\npunti -> %d", points);
}

bool gameShouldEnd(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]) {
	int  i                  = 0;
	int  j                  = 0;
	bool finishedTetraminos = true;
	int  selectedTetramino  = INVALID_TETRAMINO;
	int  column             = 0;
	int  rot                = 0;

	for (i = 0; i < INITIAL_TETRAMINOS; ++i) {
		if (runtimeTetraminos[i] != INVALID_TETRAMINO) {
			finishedTetraminos = 0;
			break;
		}
	}

	if (finishedTetraminos) {
		printf("Finiti i tetramini!\n");
		return true;
	}

	for (i = 0; i < INITIAL_TETRAMINOS; ++i) {
		selectedTetramino = runtimeTetraminos[i];
		if (selectedTetramino == INVALID_TETRAMINO) {
			continue;
		}
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			column = j;
			for (rot = 0; rot < 4; ++rot) {
				if (insert(selectedTetramino, screen, column, rot)) {
					replaceTempTetr(L' ', screen);
					return false;
				}
				replaceTempTetr(L' ', screen);
			}
		}
	}

	printf("non c'è più spazio per i tetramini\n");
	return true;
}

void setup(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]) {

	unsigned i = 0;
	unsigned temp;

	setupLocale();

	temp = (unsigned)(time(0));
	srand(temp);

	for (i = 0; i < INITIAL_TETRAMINOS; i++) {
		runtimeTetraminos[i] = (char)(i % NUM_TETRAMINOS);
	}
}

void cleanup() {
}

int clearLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	int i    = 0;
	int j    = 0;
	int temp = 1;

	int res = 0;

	for (i = 0; i < SCREEN_HEIGHT; ++i) {
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			if (screen[i][j] == L' ') {
				temp = 0;
				break;
			}
		}
		if (temp == 1) {
			wmemset(screen[i], L' ', SCREEN_WIDTH);
			fixLines(screen, i);
			++res;
		}
		temp = 1;
	}

	return res;
}

void fixLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int row) {
	int i = 0;
	for (i = row; i > 0; --i) {
		wmemcpy(screen[i], screen[i - 1], SCREEN_WIDTH);
	}

	wmemset(&screen[0][0], L' ', SCREEN_WIDTH);
}
