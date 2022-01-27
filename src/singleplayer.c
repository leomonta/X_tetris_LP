#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"
#include "singleplayer.h"
#include "tetramino.h"
#include "utils.h"

void singlePlayerLoop() {

	int     points = 0;
	wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];

	/*
	 * Indice rispetto a allTetraminos per indicare i tetramini disponibili al giocatore
	 */
	unsigned char runtimeTetraminos[INITIAL_TETRAMINOS];

	setup(runtimeTetraminos);

	clearScreen(screen);

	while (!gameShouldEnd(screen, runtimeTetraminos)) {

		playerTurn(screen, runtimeTetraminos, INITIAL_TETRAMINOS);

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

		/* Salta i tetramini gia' usati */
		if (selectedTetramino == INVALID_TETRAMINO) {
			continue;
		}

		for (j = 0; j < SCREEN_WIDTH; ++j) {
			for (rot = 0; rot < 4; ++rot) {

				/* Provo ad inserire il tetramino */
				if (insert(selectedTetramino, screen, j, rot)) {
					/* Successo, rimuovo il tetramino temporaneo ed esco */
					replaceTempTetr(L' ', screen);
					return false;
				}
				replaceTempTetr(L' ', screen);
			}
		}
	}

	printf("non c'e' piu' spazio per i tetramini\n");
	return true;
}

void setup(unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]) {

	unsigned i = 0;
	unsigned temp;

	temp = (unsigned)(time(0));
	srand(temp);

	for (i = 0; i < INITIAL_TETRAMINOS; i++) {
		runtimeTetraminos[i] = (unsigned char)(rand() % NUM_TETRAMINOS);
	}
}

int clearLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	int i      = 0;
	int j      = 0;
	int isFull = 1;

	int res = 0;

	for (i = 0; i < SCREEN_HEIGHT; ++i) {
		for (j = 0; j < SCREEN_WIDTH; ++j) {

			/* Se c'e' un carattere vuoto non e' una riga piena, esco dal loop segnalandolo con isFull = 0  */
			if (screen[i][j] == L' ') {
				isFull = 0;
				break;
			}
		}
		if (isFull == 1) {

			/* Cancello la riga, aggiorno il conteggio di linee cancellate e sposto tutti i tetramini sopra la linea cancellata in basso */
			wmemset(screen[i], L' ', SCREEN_WIDTH);
			fixLines(screen, i);
			++res;
		}
		isFull = 1;
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
