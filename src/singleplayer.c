#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"
#include "singleplayer.h"
#include "tetramino.h"
#include "utils.h"

void singlePlayerLoop() {

	int            inputColumn   = 0;
	int            inputTetr     = 0;
	const wchar_t *selectedTetr  = nullptr;
	int            inputRotation = 0;

	int     points = 0;
	wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];

	/**
	 * Indice rispetto a allTetraminos per indicare i tetramini disponibili al giocatore
	 */
	unsigned char runtimeTetraminos[INITIAL_TETRAMINOS];

	setup(runtimeTetraminos);

	clearScreen(screen);

	/* loop 1 */
	while (!gameShouldEnd(screen, runtimeTetraminos)) {

		playerTurn(screen, runtimeTetraminos);

		points += calcPoints(clearLines(screen));

		drawScreen(screen);
		printf("punti -> %d\n\n", points);
	}

	printf("Gioco finto!\npunti -> %d", points);
}

void playerTurn(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]) {

	int            inputColumn   = 0;
	int            inputTetr     = 0;
	int            inputRotation = 0;
	const wchar_t *selectedTetr  = nullptr;

	while (1) {

		/* presento tutti i tetramini disponibili con relativi indici */
		drawRemainingTetraminos(runtimeTetraminos, INITIAL_TETRAMINOS);

		printf("Scegli il tetramino\n");
		inputTetr = getIntStdin(0, INITIAL_TETRAMINOS);

		if (runtimeTetraminos[inputTetr] == INVALID_TETRAMINO) {
			printf("Il tetramino n. %d è già stato usato, sceglierne un'altro!\n", inputTetr);
			continue;
		}

		/* il numero intero indica quante volta il tetramino deve essere girato in senso orario */
		printf("Scegli la rotazione, da 0 a 3\n");
		inputRotation = getIntStdin(0, 4);

		selectedTetr = allTetraminos[runtimeTetraminos[inputTetr]];

		/* stampo il singolo tetramino ruotato correttamente per mostrarlo all'utente */
		drawSingleTetramino(runtimeTetraminos[inputTetr], inputRotation);

		printf("\n\nScegli la colonna\n");
		inputColumn = getIntStdin(0, SCREEN_WIDTH);

		/**
		 * Provo a inserire il tetramino nella posizione specificata.
		 * In caso di successo faccio cadere il tetramino e lo rimuovo dalla lista di tetramini disponibili
		 * In caso di fallimento comunico l'errore e ricomincio il ciclo
		 */

		if (!insert(runtimeTetraminos[inputTetr], screen, inputColumn, inputRotation)) {
			/* fallimento */
			replaceTempTetr(L' ', screen);

			printf("il tetramino selezionato non può essere posizionato dove richiesto\n");

			/* riparti da inizio ciclo senza cambiare il turno */
			continue;
		}

		break;
	}

	/* rimuovo il tetramino dalla lista di quelli disponibili */
	runtimeTetraminos[inputTetr] = INVALID_TETRAMINO;

	/* faccio cadere il tetramino appena inserito, segnato come @, fino al punto più basso */
	fall(screen);
	/* poi sostituisco i segnalini @ con i caratteri corretti */
	replaceTempTetr(selectedTetr[1], screen);
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
