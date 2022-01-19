#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>

#include "graphics.h"
#include "multiplayer.h"
#include "tetramino.h"
#include "utils.h"

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
	int     turn     = 1;
	int     pointsG1 = 0;
	int     pointsG2 = 0;
	wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH];
	wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH];
	/**
	 * utilizzo un puntatore alla variabile points corretta
	 * ogni turno la imposto in modo che punti alla variabile del giocatore corretto
	 */
	int *currPoints;

	/**
	 * Indice rispetto a allTetraminos per indicare i tetramini disponibili al giocatore
	 */
	unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X];

	multiSetup(runtimeTetraminos);

	clearScreen(screenG1);
	clearScreen(screenG2);

	while (!multiGameShouldEnd(screenG1, screenG2, runtimeTetraminos)) {

		/* in base al turno stampo chi dovrebbe giocare questo turno e imposto al variabile currPoints */
		if (turn == 1) {
			currPoints = &pointsG1;
			printf(" --- Turno G1 --- \n");
		} else {
			currPoints = &pointsG2;
			printf(" --- Turno G2 --- \n");
		}

		/* presento tutti i tetramini disponibili con relativi indici */
		drawRemainingTetraminos(runtimeTetraminos, INITIAL_TETRAMINOS_2X);

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

		if (!insert(runtimeTetraminos[inputTetr], turn == 1 ? screenG1 : screenG2, inputColumn, inputRotation)) {
			/* fallimento */
			replaceTempTetr(L' ', turn == 1 ? screenG1 : screenG2);

			printf("il tetramino selezionato non può essere posizionato dove richiesto\n");

			/* riparti da inizio ciclo senza cambiare il turno */
			continue;
		}

		/* rimuovo il tetramino dalla lista di quelli disponibili */
		runtimeTetraminos[inputTetr] = INVALID_TETRAMINO;

		/* faccio cadere il tetramino appena inserito, segnato come @, fino al punto più basso */
		fall(turn == 1 ? screenG1 : screenG2);
		/* poi sostituisco i segnalini @ con i caratteri corretti */
		replaceTempTetr(selectedTetr[1], turn == 1 ? screenG1 : screenG2);

		/* calcolo i punti da assegnare in base alle linee che sono state eliminate in questo turno*/
		*currPoints += calcPoints(clearLines(turn == 1 ? screenG1 : screenG2));

		/* mostro la situazione corrente per entrambi i giocatori */
		multiDrawScreen(screenG1, screenG2, pointsG1, pointsG2);

		/* passo continuamente da 0 a 1 */
		turn = !turn;
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