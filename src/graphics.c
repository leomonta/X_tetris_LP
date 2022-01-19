#include "graphics.h"

#include <stdio.h>

void drawRemainingTetraminos(unsigned char *runtimeTetraminos, unsigned int size) {
	unsigned       i           = 0;
	unsigned       j           = 0;
	unsigned       index       = 0;
	unsigned       rowIndex    = 0;
	unsigned       columnIndex = 0;
	const unsigned numCols     = 5;
	wchar_t const *currTetramino;
	unsigned char  temp;

	wchar_t row[2][25];

	/*

	dato che ogni tetramino occupa un massimo di 4*2
	faccio colonne grandi 5 (massima lunghezza + spazio)
	per un arbitrario numero di righe

	per fare ciò, prima 'stampo' i tetramini su un array, 
	dopo stampo l'array

			col1 col2 col3 col4 col5

	riga 1  #### #### #### #### #### <- sottoriga superiore
	        #### #### #### #### #### <- sottoriga inferiore

	riga 2  #### #### #### #### ####
	        #### #### #### #### ####

	riga 3  #### #### #### #### ####
	        #### #### #### #### ####

	riga 4  #### #### #### #### ####
	        #### #### #### #### ####
			^
			sottocolonna singola
	*/

	/* numero delle righe rispetto al numero di colonne */
	for (i = 0; i < size / numCols; ++i) {

		/* svuoto la riga */
		wmemset(&row[0][0], L' ', 25 * 2);

		/* per il numero di colonne in una singola riga */
		for (columnIndex = 0; columnIndex < numCols; ++columnIndex) {
			/* 
			offset negativo per scrivere alla posizione corretta della riga inferiore quando
			avviene il cambiamento della sottoriga
			 */
			unsigned relOrg = 0;

			temp = runtimeTetraminos[i * numCols + columnIndex];

			/* in caso di tetramino rimosso salta */
			if (temp == INVALID_TETRAMINO) {
				continue;
			}

			/* Ottengo la stringa del tetramino */
			currTetramino = allTetraminos[temp];

			/* Fa il loop per ogni carattere della stringa */
			for (index = 0, rowIndex = 0; currTetramino[index] != '*'; ++index) {

				/* 
				Se il carattere corrente è un 'a capo' -> '/' mi sposto sulla riga inferiore, aggiorno l'offet di sottocolonna
				altrimenti inserisce il carattere corrente 
				*/
				if (currTetramino[index] == '/') {
					rowIndex = 1;
					relOrg   = index + 1;
				} else {
					/* Se il carattere corrente e' '_' allora inserisci ' ' */
					row[rowIndex][columnIndex * 5 + index - relOrg] = currTetramino[index] == L'_' ? L' ' : currTetramino[index];
				}
			}
		}

		for (j = 0; j < 2; ++j) {
			for (index = 0; index < 25; ++index) {

				if (index % 5 == 0) {
					if (j == 0) {
						printf("%2d) ", index / 5 + i * 5);
					} else {
						printf("    ");
					}
				}

				printf("%lc ", row[j][index]);
			}

			printf("\n");
		}

		printf("\n\n");
	}
}

void drawScreen(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	char i, j;

	printf("╔═════════════════════╗\n");

	for (i = 0; i < SCREEN_HEIGHT; ++i) {
		printf("%lc ", L'║');
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			printf("%lc ", screen[i][j]);
		}
		printf("%lc", L'║');
		printf("\n");
	}
	printf("╠═════════════════════╣\n");
	printf("║ 0 1 2 3 4 5 6 7 8 9 ║\n");
	printf("╚═════════════════════╝\n");
}

void multiDrawScreen(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH], int pointsG1, int pointsG2) {

	char i, j;

	printf("╔═════════════════════╗    ╔═════════════════════╗\n");
	printf("║     Giocatore 1     ║    ║     Giocatore 2     ║\n");
	printf("╠═════════════════════╣    ╠═════════════════════╣\n");

	for (i = 0; i < SCREEN_HEIGHT; ++i) {
		printf("%lc ", L'║');
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			printf("%lc ", screenG1[i][j]);
		}
		printf("%lc    %lc ", L'║', L'║');
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			printf("%lc ", screenG2[i][j]);
		}
		printf("%lc", L'║');
		printf("\n");
	}
	printf("╠═════════════════════╣    ╠═════════════════════╣\n");
	printf("║ 0 1 2 3 4 5 6 7 8 9 ║    ║ 0 1 2 3 4 5 6 7 8 9 ║\n");
	printf("╚═════════════════════╝    ╚═════════════════════╝\n\n");

	printf("Punti ->             %-5d                      %-5d\n\n", pointsG1, pointsG2); /* %5d dovrebbe agguingere il padding necessario ad allineare tutto*/
}

void clearScreen(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]) {

	wmemset(&screen[0][0], L' ', SCREEN_HEIGHT * SCREEN_WIDTH);
}

void drawSingleTetramino(int numTetramino, int rotation) {

	const wchar_t *curr = tetraminosRotation[rotation][numTetramino];

	while (*curr != L'*') {

		if (*curr == L'/') {
			printf("\n");
		} else {
			printf("%lc ", *curr == L'_' ? L' ' : *curr);
		}

		++curr;
	}
}