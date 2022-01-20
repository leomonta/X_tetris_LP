#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>

#include "graphics.h"
#include "multiplayer.h"
#include "tetramino.h"
#include "utils.h"

void multiPlayerLoopAI() {

	/* variabili per gestire gli input */
	int winner = 0; /* indica il vincitore, 1 -> G1, 2 -> G2, 0 -> nessun ed il gioco continua, -1 -> dipende dal punteggio */

	/* Variabili dei giocatori */
	int     currTurn = 1;
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

	while (!(winner = multiGameShouldEnd(screenG1, screenG2, runtimeTetraminos))) {

		/**
		 * In base al turno stampo chi dovrebbe giocare questo turno e aggiorno il punteggio
		 * calcolo i punti da assegnare in base alle linee che sono state eliminate in questo turno 
		 */
		if (currTurn == 1) {
			printf(" --- Turno G1 --- \n\n");
			multiPlayerTurn(screenG1, runtimeTetraminos);
			pointsG1 += calcPoints(multiClearLines(screenG1, screenG2));
		} else {
			AITurn(screenG2, runtimeTetraminos);
			pointsG2 += calcPoints(multiClearLines(screenG2, screenG1));
		}

		/* mostro la situazione corrente per entrambi i giocatori */
		multiDrawScreen(screenG1, screenG2, pointsG1, pointsG2);

		getchar();

		/* passo continuamente da 0 a 1 */
		currTurn = !currTurn;
	}

	switch (winner) {
	case 1:
		printf("Vince il giocatore 1");
		break;

	case 2:
		printf("Vince il giocatore 2");
		break;

	case -1:
		if (pointsG1 > pointsG2) {
			printf("Vince il giocatore 1");
			break;
		}

		if (pointsG1 < pointsG2) {
			printf("Vince il giocatore 2");
			break;
		}

		printf("Pareggio");
		break;

	default:
		break;
	}
}

void multiPlayerLoop() {

	/* variabili per gestire gli input */
	int winner = 0; /* indica il vincitore, 1 -> G1, 2 -> G2, 0 -> nessun ed il gioco continua, -1 -> dipende dal punteggio */

	/* Variabili dei giocatori */
	int     currTurn = 1;
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

	while (!(winner = multiGameShouldEnd(screenG1, screenG2, runtimeTetraminos))) {

		/**
		 * In base al turno stampo chi dovrebbe giocare questo turno e aggiorno il punteggio
		 * calcolo i punti da assegnare in base alle linee che sono state eliminate in questo turno 
		 */
		if (currTurn == 1) {
			printf(" --- Turno G1 --- \n\n");
			multiPlayerTurn(screenG1, runtimeTetraminos);
			pointsG1 += calcPoints(multiClearLines(screenG1, screenG2));
		} else {
			printf(" --- Turno G2 --- \n\n");
			playerTurn(screenG2, runtimeTetraminos);
			pointsG2 += calcPoints(multiClearLines(screenG2, screenG1));
		}

		/* mostro la situazione corrente per entrambi i giocatori */
		multiDrawScreen(screenG1, screenG2, pointsG1, pointsG2);

		/* pausa per permettere di vedere bene la situazione sui due schermi */
		getchar();

		/* passo continuamente da 0 a 1 */
		currTurn = !currTurn;
	}

	switch (winner) {
	case 1:
		printf("Vince il giocatore 1");
		break;

	case 2:
		printf("Vince il giocatore 2");
		break;

	case -1:
		if (pointsG1 > pointsG2) {
			printf("Vince il giocatore 1");
			break;
		}

		if (pointsG1 < pointsG2) {
			printf("Vince il giocatore 2");
			break;
		}

		printf("Pareggio");
		break;

	default:
		break;
	}
}

void multiPlayerTurn(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]) {

	int            inputColumn   = 0;
	int            inputTetr     = 0;
	int            inputRotation = 0;
	const wchar_t *selectedTetr  = nullptr;

	while (1) {

		/* presento tutti i tetramini disponibili con relativi indici */
		drawRemainingTetraminos(runtimeTetraminos, INITIAL_TETRAMINOS_2X);

		printf("Scegli il tetramino\n");
		inputTetr = getIntStdin(0, INITIAL_TETRAMINOS_2X);

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

void AITurn(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]) {

}

int multiGameShouldEnd(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]) {
	int  i                  = 0;
	int  j                  = 0;
	bool finishedTetraminos = true;
	int  selectedTetramino  = INVALID_TETRAMINO;
	int  rot                = 0;
	int  G1Full             = 1; /* indica se il campo del giocatore 1 ha spazio */

	for (i = 0; i < INITIAL_TETRAMINOS_2X; ++i) {
		if (runtimeTetraminos[i] != INVALID_TETRAMINO) {
			finishedTetraminos = 0;
			break;
		}
	}

	if (finishedTetraminos) {
		printf("Finiti i tetramini!\n");
		return -1;
	}

	for (i = 0; i < INITIAL_TETRAMINOS_2X; ++i) {
		selectedTetramino = runtimeTetraminos[i];
		/* salta i tetramini non presenti */
		if (selectedTetramino == INVALID_TETRAMINO) {
			continue;
		}

		/**
		 * provo ad inserire ogni tetramino in ogni posizione in ogni rotazione possibile, 
		 * se è possibile che succeda anche una volta significa che il gioco per questo giocatore può continuare
		 */

		/* G1 */
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			for (rot = 0; rot < 4; ++rot) {
				if (insert(selectedTetramino, screenG1, j, rot)) {
					replaceTempTetr(L' ', screenG1);
					G1Full = 0; /* il campo del G1 ha ancora spazio */
					/* salto il loop for esterno */
					j = SCREEN_WIDTH;
					i = INITIAL_TETRAMINOS_2X;
					break;
				}
				replaceTempTetr(L' ', screenG1);
			}
		}
	}

	/* se non c'è più spazio nel campo del G1, deve aver vinto il G2 */
	if (G1Full) {
		return 2;
	}

	for (i = 0; i < INITIAL_TETRAMINOS_2X; ++i) {
		selectedTetramino = runtimeTetraminos[i];
		/* salta i tetramini non presenti */
		if (selectedTetramino == INVALID_TETRAMINO) {
			continue;
		}

		/* G2 */
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			for (rot = 0; rot < 4; ++rot) {
				if (insert(selectedTetramino, screenG2, j, rot)) {
					replaceTempTetr(L' ', screenG2);
					return false; /* c'è spazio in entrambi i campi, il gioco continua */
				}
				replaceTempTetr(L' ', screenG2);
			}
		}
	}

	/* c'è spazio nel campo del G1, non c'è spazio nel campo del G2, vince G1*/
	return 1;
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

int multiClearLines(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH]) {

	int i    = 0;
	int j    = 0;
	int temp = 1;

	int res = 0;

	for (i = 0; i < SCREEN_HEIGHT; ++i) {
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			if (screenG1[i][j] == L' ') {
				temp = 0;
				break;
			}
		}
		if (temp == 1) {
			wmemset(screenG1[i], L' ', SCREEN_WIDTH);
			multiFixLines(screenG1, i);
			++res;
		}
		temp = 1;
	}

	if (res > 2) {
		multiInvertLines(screenG2, res);
	}
	return res;
}

void multiFixLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int line) {

	int i = 0;
	for (i = line; i > 0; --i) {
		wmemcpy(screen[i], screen[i - 1], SCREEN_WIDTH);
	}

	wmemset(&screen[0][0], L' ', SCREEN_WIDTH);
}

void multiInvertLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int count) {

	int i = 0;
	int j = 0;
	for (i = SCREEN_HEIGHT - count; i < SCREEN_HEIGHT; ++i) {
		for (j = 0; j < SCREEN_WIDTH; ++j) {

			if (screen[i][j] == L' ') {
				screen[i][j] = L'▩';
			} else {
				screen[i][j] = L' ';
			}
		}
	}
}