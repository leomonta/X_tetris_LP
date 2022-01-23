#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"
#include "multiplayer.h"
#include "tetramino.h"
#include "utils.h"

void multiPlayerLoop(bool AI) {

	/*
	 * indica il vincitore 
	 * 1 -> G1
	 * 2 -> G2
	 * 0 -> nessun ed il gioco continua
	 * -1 -> dipende dal punteggio 
	 */
	int winner = 0;

	/* Variabili dei giocatori */
	int     currTurn = 1;
	int     pointsG1 = 0;
	int     pointsG2 = 0;
	wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH];
	wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH];

	/*
	 * Indici rispetto a allTetraminos per indicare i tetramini disponibili al giocatore
	 */
	unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X];

	/* Riempi runtimeTetraminos di tetramini casuali */
	multiSetup(runtimeTetraminos);

	/* Svuota gli schermi da quello che c'era prima */
	clearScreen(screenG1);
	clearScreen(screenG2);

	/* Assegna e conmporaneamente controlla il vincitore */
	while (!(winner = multiGameShouldEnd(screenG1, screenG2, runtimeTetraminos))) {

		/*
		 * In base al turno:
		 * 
		 * Stampo chi dovrebbe giocare questo turno
		 * Svolgo il turno corretto
		 * Aggiorno il punteggio in base alle linee che sono state eliminate in questo turno 
		 * 
		 */
		if (currTurn == 1) {
			printf(" ------- Turno G1 ------- \n\n");
			playerTurn(screenG1, runtimeTetraminos, INITIAL_TETRAMINOS_2X);
			pointsG1 += calcPoints(multiClearLines(screenG1, screenG2));
		} else {

			if (AI) {
				printf(" ------- Turno AI ------- \n\n");
				AITurn(screenG2, runtimeTetraminos);
			} else {
				printf(" ------- Turno G2 ------- \n\n");
				playerTurn(screenG2, runtimeTetraminos, INITIAL_TETRAMINOS_2X);
			}

			pointsG2 += calcPoints(multiClearLines(screenG2, screenG1));
		}

		/* Mostro la situazione corrente per entrambi i giocatori */
		multiDrawScreen(screenG1, screenG2);
		printf("Punti ->             %-2d                        %-2d\n\n", pointsG1, pointsG2);

		/* Pausa per osservare la situazione */
		printf("Premi INVIO per continuare");
		getchar();

		/* Cambio il turno, oscillando da 1 a 0 */
		currTurn = !currTurn;
	}

	/* Annuncio il vincitore in base alla situazione  */
	switch (winner) {
	case 1:
		printf("Vince il giocatore 1");
		break;

	case 2:
		if (AI) {
			printf("Vince la AI");
		} else {
			printf("Vince il giocatore 2");
		}
		break;

	case -1:
		if (pointsG1 > pointsG2) {
			printf("Vince il giocatore 1");
			break;
		}

		if (pointsG1 < pointsG2) {
			if (AI) {
				printf("Vince la AI");
			} else {
				printf("Vince il giocatore 2");
			}
			break;
		}

		printf("Pareggio");
		break;

	default:
		break;
	}
}

void AITurn(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]) {

	/* Variabili per scorrere tutte le opzioni possibili */
	int indexTetr         = 0;
	int column            = 0;
	int rot               = 0;
	int selectedTetramino = INVALID_TETRAMINO;

	/* Variabili per tenere conto della mossa migiore */
	int highScore    = 0;
	int currScore    = 0;
	int currStats[4] = {0, 0, 0, 0};

	/*
	 * Parametri da usare per inserire un singolo tetramino 
	 * 
	 * 0 -> indice rispetto a runtime tetramino
	 * 1 -> colonna in cui inserire il tetramino
	 * 2 -> rotazione del tetramino
	 */
	int selected[3] = {0, 0, 0};

	/* Faccio tre loop per passare tutti possibili tetramini per ogni rotazione per ogni colonna */
	for (indexTetr = 0; indexTetr < INITIAL_TETRAMINOS_2X; ++indexTetr) {

		selectedTetramino = runtimeTetraminos[indexTetr];

		/* Salta i tetramini non disponibli */
		if (selectedTetramino == INVALID_TETRAMINO) {
			continue;
		}

		for (column = 0; column < SCREEN_WIDTH; ++column) {
			for (rot = 0; rot < 4; ++rot) {

				/* Provo ad inserire il tetramino */
				if (insert(selectedTetramino, screen, column, rot)) {
					fall(screen);

					/* Il tetramino e' inseribile in questa posizione, quindi calcolo le statistiche utili alla CPU per fare le decisioni */
					multiCalcStats(screen, currStats);

					currScore = calcScore(currStats);

					if (currScore > highScore) {
						selected[0] = indexTetr;
						selected[1] = column;
						selected[2] = rot;
						highScore   = currScore;
					}
				}
				/* Elimino i tetramini temporanei('@') appena usati */
				replaceTempTetr(L' ', screen);
			}
		}
	}

	/* Ho ottenuto la mossa migliore, la eseguo */
	selectedTetramino = runtimeTetraminos[selected[0]];

	insert(selectedTetramino, screen, selected[1], selected[2]);

	/* Rimuovo il tetramino dalla lista di quelli disponibili */
	runtimeTetraminos[selected[0]] = INVALID_TETRAMINO;

	/* Faccio cadere il tetramino appena inserito, segnato come @, fino al punto piu' basso */
	fall(screen);

	/* Poi sostituisco i segnalini @ con il carattere corretto */
	replaceTempTetr(allTetraminos[selectedTetramino][1], screen);
}

void multiCalcStats(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int result[4]) {

	int row    = 0;
	int column = 0;

	bool highestFound = false;
	/* Controllo per confermare se una riga e' completa */
	bool isEmpty = false;

	result[0] = 0;
	result[1] = 0;
	result[2] = 0;
	result[3] = 0;

	for (row = 0; row < SCREEN_HEIGHT; ++row) {
		for (column = 0; column < SCREEN_WIDTH; ++column) {

			if (screen[row][column] == L' ') {

				/* Ho trovato uno spazio, la riga non e' piena */
				isEmpty = true;

				if (isAHole(screen, row, column)) {
					++result[3];

					/* Se non e' un buco significa che sopra ha solo spazi liberi, quindi puo' essere il punto piu' basso accessibile */
				} else {
					/* Se row + 1 == SCREEN_HEIGHT significa che sono alla base del campo, quindi una posizione valida */
					if (row + 1 == SCREEN_HEIGHT || screen[row + 1][column]) {
						result[1] = row + 1 > result[1] ? row + 1 : result[1];
					}
				}

				/* Se questo e' uno spazio vuoto, non puo' essere il punto piu' alto */
				continue;
			}

			/* Il punto piu' alto e' semplicemente il primo carattere non vuoto che trovo visto che controllo dall'alto al basso*/
			if (screen[row][column] != L' ') {

				if (!highestFound) {
					result[0]    = row;
					highestFound = true;
				}
			}
		}

		/* Controllo se ho una linea piena */
		if (!isEmpty) {
			++result[2];
		}
		isEmpty = false;
	}
}

int calcScore(int stats[4]) {
	return stats[0] * HIGH_WEIGHT + stats[1] * LOW_WEIGHT + stats[2] * LINES_WEIGHT + stats[3] * HOLES_WEIGHT + abs(stats[1] - stats[0]) * DIFF_WEIGHT;
}

bool isAHole(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int row, int column) {

	/* Avanzo verso l'alto, se trovo un tetramino allora questo e' un buco */
	for (row; row > 0; --row) {
		if (screen[row][column] != L' ') {
			return true;
		}
	}

	return false;
}

int multiGameShouldEnd(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]) {

	int  i                  = 0;
	int  j                  = 0;
	bool finishedTetraminos = true;
	int  selectedTetramino  = INVALID_TETRAMINO;
	int  rot                = 0;
	int  G1Full             = 1; /* Indica se il campo del giocatore 1 ha spazio */

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

		/* Salta i tetramini non presenti */
		if (selectedTetramino == INVALID_TETRAMINO) {
			continue;
		}

		/*
		 * Provo ad inserire ogni tetramino in ogni posizione e in ogni rotazione possibile
		 * Se e' possibile che succeda anche una volta significa che il gioco per questo giocatore puo' continuare
		 */

		/* G1 */
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			for (rot = 0; rot < 4; ++rot) {

				/* Provo ad inserire il tetramino */
				if (insert(selectedTetramino, screenG1, j, rot)) {

					/*
					 * Successo 
					 * il campo del G1 ha ancora spazio quindi posso controllare il campo del G2
					 * spingo gli indici oltre i limiti per uscire dal loop
					 */

					replaceTempTetr(L' ', screenG1);
					G1Full = 0;
					j      = SCREEN_WIDTH;
					i      = INITIAL_TETRAMINOS_2X;
					break;
				}
				replaceTempTetr(L' ', screenG1);
			}
		}
	}

	/* se non c'e' piu' spazio nel campo del G1, deve aver vinto il G2 */
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

				/* Provo ad inserire il tetramino */
				if (insert(selectedTetramino, screenG2, j, rot)) {

					/*
					 * Successo 
					 * il campo del G2 ha ancora spazio quindi il gioco puo' continuare per entrambi i giocatore 
					 * posso uscire direttamente dalla funzione
					 */

					replaceTempTetr(L' ', screenG2);
					return 0;
				}
				replaceTempTetr(L' ', screenG2);
			}
		}
	}

	/* c'e' spazio nel campo del G1, non c'e' spazio nel campo del G2, vince G1*/
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

	int i      = 0;
	int j      = 0;
	int isFull = 1;

	int res = 0;

	for (i = 0; i < SCREEN_HEIGHT; ++i) {
		for (j = 0; j < SCREEN_WIDTH; ++j) {

			/* Se c'e' un carattere vuoto non e' una riga piena, esco dal loop segnalandolo con isFull = 0  */
			if (screenG1[i][j] == L' ') {
				isFull = 0;
				break;
			}
		}

		if (isFull == 1) {

			/* Cancello la riga, aggiorno il conteggio di linee cancellate e sposto tutti i tetramini sopra la linea cancellata in basso */
			wmemset(screenG1[i], L' ', SCREEN_WIDTH);
			multiFixLines(screenG1, i);
			++res;
		}
		isFull = 1;
	}

	/* Se sono state cancellate abbastanza righe inverto quelle del G2 */
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
	/* Parto da count righe dal basso e anvazo verso il basso */
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