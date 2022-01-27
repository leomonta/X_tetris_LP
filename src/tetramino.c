#include <stdio.h>

#include "tetramino.h"

void fall(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	/*
	Dato che il metodo insert inserisci i tetramini dall'alto ho sempre la certezza che sulla prima riga c'e' un tetramino temporaneo.
	Quindi posso partire dall'alto a controllare se il tetamino può essere spostato verso il basso tenendo conto che:
	se trovo una riga vuota sono al di sotto del tetramino e quindi posso fermare il ciclo preventivamente
	posso abbassare il punto di inizio ogni volta che completo lo spostamento
	*/

	int i = 0;
	int j = 0;

	/* lavoro su una finestra alta 4 tetramini, visto che è l'altezza massima che un tetramino può avere */
	int start = 0;

	/* variabile di controllo per capire quando il tetramino è sceso al punto più basso */
	bool _exit = false;
	/* variabile di controllo per capire se ho trovato caratteri tetramini in una riga, se non ne ho trovato neanche uno ricomincia il loop */
	bool tempFound = false;

	while (!_exit) {

		/* controllo se l'intero tetramino ha uno spazio libero sotto di esso per essere spostato */
		for (i = start; i < SCREEN_HEIGHT && !_exit; ++i) {
			for (j = 0; j < SCREEN_WIDTH && !_exit; ++j) {

				/* Se sono su un carattere temporaneo */
				if (screen[i][j] == '@') {

					tempFound = true;

					/* Se sono all'ultima casella prima della base esco */
					if (i == SCREEN_HEIGHT - 1) {
						_exit = true;
						break;
					}
					/* Se la prossima cella non e' libera e non e' un'altro carattere temporaneo esco */
					if (screen[i + 1][j] != L' ' && screen[i + 1][j] != L'@') {
						_exit = true;
					}
				}
			}

			if (!tempFound) {
				/* se non ci sono tetramini temporanei in questa linea significa che non devo controllarne altri */
				break;
			}
			tempFound = false;
		}

		/* Se in questo ciclo non devo uscire posso spostare tutti i caratteri temporanei verso il basso */
		for (i = SCREEN_HEIGHT - 1; i >= start; --i) {
			for (j = 0; j < SCREEN_WIDTH && !_exit; ++j) {
				if (screen[i][j] == '@') {

					screen[i + 1][j] = '@';
					screen[i][j]     = ' ';
				}
			}
		}

		++start;
	}
}

void replaceTempTetr(wchar_t replaceWith, wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]) {

	int i, j;

	for (i = 0; i < SCREEN_HEIGHT; ++i) {
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			if (screen[i][j] == '@') {
				screen[i][j] = replaceWith;
			}
		}
	}
}

bool insert(int numTetramino, wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int column, int rot) {

	int currColumn = column;
	int currRow    = 0;

	/* Ottengo direttamente il tetramino corretto con la rotazione corretta */
	const wchar_t *currTetramino = tetraminosRotation[rot][numTetramino];

	/* '*' indica la fine del tetramino */
	while (*currTetramino != '*') {

		/* '/' indica un a capo*/
		if (*currTetramino == '/') {
			/* resetto dove devo iniziare a stampare sopo l'a capo */
			currColumn = column;
			++currRow;
		} else {

			if (*currTetramino != L'_') {

				/* Controllo se sto per rimpiazzare un tetramino gia' presente o fuori dallo schermo */
				if (screen[currRow][currColumn] != L' ' || !checkBounds(currColumn, currRow)) {
					/* Sto tentando di inserire un tetramino dove non c'e' spazio, ritorno false */
					return false;
				}

				screen[currRow][currColumn] = L'@';
			}

			/* Mi sposto a destra */
			++currColumn;
		}

		/* Prossimo carattere */
		++currTetramino;
	}

	return true;
}

bool checkBounds(int column, int row) {
	return (column >= 0 && column < SCREEN_WIDTH && row >= 0 && row < SCREEN_HEIGHT);
}

void playerTurn(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char *runtimeTetraminos, int size) {

	/* Variabili per gli input da tastiera */
	int inputColumn   = 0;
	int inputTetr     = 0;
	int inputRotation = 0;

	const wchar_t *selectedTetr = nullptr;

	/* In caso un input dato non sia valido ripeto da capo */
	while (1) {

		/* Presento tutti i tetramini disponibili con relativi indici */
		drawRemainingTetraminos(runtimeTetraminos, size);

		printf("Scegli il tetramino\n");
		inputTetr = getIntStdin(0, size);

		if (runtimeTetraminos[inputTetr] == INVALID_TETRAMINO) {
			printf("Il tetramino n. %d e' gia' stato usato, sceglierne un'altro!\n", inputTetr);
			continue;
		}

		/* Il numero intero indica quante volta il tetramino deve essere girato in senso orario */
		printf("Scegli la rotazione (in senso orario), da 0 a 3\n");
		inputRotation = getIntStdin(0, 4);

		/* Stampo il singolo tetramino ruotato correttamente per mostrarlo all'utente */
		drawSingleTetramino(runtimeTetraminos[inputTetr], inputRotation);

		printf("\n\nScegli la colonna\n");
		inputColumn = getIntStdin(0, SCREEN_WIDTH);

		/*
		 * Provo a inserire il tetramino nella posizione specificata.
		 * In caso di successo faccio cadere il tetramino e lo rimuovo dalla lista di tetramini disponibili
		 * In caso di fallimento comunico l'errore e ricomincio il ciclo
		 */

		if (!insert(runtimeTetraminos[inputTetr], screen, inputColumn, inputRotation)) {
			/* Fallimento */
			replaceTempTetr(L' ', screen);

			printf("il tetramino selezionato non puo' essere posizionato dove richiesto\n");

			/* Riparti da inizio ciclo senza cambiare il turno */
			continue;
		}

		break;
	}

	selectedTetr = allTetraminos[runtimeTetraminos[inputTetr]];

	/* Rimuovo il tetramino dalla lista di quelli disponibili */
	runtimeTetraminos[inputTetr] = INVALID_TETRAMINO;

	/* Faccio cadere il tetramino appena inserito, segnato come @, fino al punto piu' basso */
	fall(screen);

	/* Poi sostituisco i segnalini @ con il carattere corretto */
	replaceTempTetr(selectedTetr[1], screen);
}