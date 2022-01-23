#include "graphics.h"

#include <stdio.h>

void drawRemainingTetraminos(unsigned char *runtimeTetraminos, unsigned int size) {
	unsigned       rowIndex    = 0;  /* indice di Riga, scorre le N righe trovate da  size(numero totale tetramini) / numCols */
	unsigned       columnIndex = 0;  /* indice di Colonna, scorre da 0 a numCols, usato per stampare nell'array e sullo schermo */
	unsigned       index       = 0;  /* indice per scorrere la stringa del tetramino */
	unsigned       minorRow    = 0;  /* indice di sottoriga, usato per stampare nell'array e sullo schermo */
	const unsigned numCols     = 10; /* massimo numero di colonne per righe*/
	const unsigned columnWidth = 5;  /* larghezza di ogni colonna */
	wchar_t const *currTetramino;
	unsigned char  temp;

	wchar_t row[2][10 * 5];

	/**
	 *
	 *	dato che ogni tetramino occupa un massimo di 4*2
	 *	faccio colonne grandi 5 (massima lunghezza + spazio)
	 *	per un arbitrario numero di righe
	 *
	 *	per fare cio', prima 'stampo' i tetramini su un array, 
	 *	dopo stampo l'array
	 *
	 *			col0 col1 col2 col3 col4 col5 col6 col7 col8 col9
	 *
	 *	riga 1  #### #### #### #### #### #### #### #### #### #### <- sottoriga superiore (0)
	 *			#### #### #### #### #### #### #### #### #### #### <- sottoriga inferiore (1)
	 *
	 *	riga 2  #### #### #### #### #### #### #### #### #### ####
	 *			#### #### #### #### #### #### #### #### #### ####
	 *
	 *	riga 3  #### #### #### #### #### #### #### #### #### ####
	 *			#### #### #### #### #### #### #### #### #### ####
	 *
	 *	riga 4  #### #### #### #### #### #### #### #### #### ####
	 *			#### #### #### #### #### #### #### #### #### ####
	 *			^
	 *			sottocolonna singola
	 */

	/* numero delle righe rispetto al numero di colonne */
	for (rowIndex = 0; rowIndex < size / numCols; ++rowIndex) {

		/* svuoto la riga */
		wmemset(&row[0][0], L' ', numCols * columnWidth * 2);

		/* per il numero di colonne in una singola riga */
		for (columnIndex = 0; columnIndex < numCols; ++columnIndex) {
			/**
			 * Scostamento dall'inizio della colonna dove stampare
			 */
			unsigned offset = 0;

			/* ottenfo l'indice del tetramino */
			temp = runtimeTetraminos[rowIndex * numCols + columnIndex];

			/* in caso di tetramino rimosso salta */
			if (temp == INVALID_TETRAMINO) {
				continue;
			}

			/* Ottengo la stringa del tetramino */
			currTetramino = allTetraminos[temp];

			/* Fa il loop per ogni carattere della stringa del tetramino */
			for (index = 0, minorRow = 0; currTetramino[index] != L'*'; ++index, ++offset) {

				/**
				 * Se il carattere corrente e' un 'a capo' -> '/' mi sposto sulla sottoriga inferiore, aggiorno l'offet di sottocolonna
				 * altrimenti inserisco il carattere corrente 
				 */
				if (currTetramino[index] == L'/') {
					minorRow = 1;  /* mi sposto sulla sottoriga inferiore */
					offset   = -1; /* correggo il ++offset del ciclo for*/
				} else {

					/**
					 * row[minorRow]			-> accedo alla sottoriga corretta
					 * columnIndex * columWidth -> mi posiziono all'inizio della sottocolonna corretta
					 * + offset					-> mi sposto di quanti caratteri ho stampato dopo l'inizio / a capo
					 * 
					 * Se il carattere corrente e' '_' allora inserisci ' '
					 */
					row[minorRow][columnIndex * columnWidth + offset] = currTetramino[index] == L'_' ? L' ' : currTetramino[index];
				}
			}
		}

		/* Stampo l'array a schermo */
		for (minorRow = 0; minorRow < 2; ++minorRow) {
			for (columnIndex = 0; columnIndex < columnWidth * numCols; ++columnIndex) {

				if (columnIndex % columnWidth == 0) {
					if (minorRow == 0) {
						printf("%2d) ", columnIndex / 5 + rowIndex * numCols);
					} else {
						printf("    ");
					}
				}

				printf("%lc ", row[minorRow][columnIndex]);
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

void multiDrawScreen(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH]) {

	char i, j;

	printf("╔═════════════════════╗    ╔═════════════════════╗\n");
	printf("║     Giocatore 1     ║    ║     Giocatore 2     ║\n");
	printf("╠═════════════════════╣    ╠═════════════════════╣\n");

	for (i = 0; i < SCREEN_HEIGHT; ++i) {
		/* campo G1 */
		printf("%lc ", L'║');
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			printf("%lc ", screenG1[i][j]);
		}

		/* campo G2 */
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
}

void clearScreen(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	wmemset(&screen[0][0], L' ', SCREEN_HEIGHT * SCREEN_WIDTH);
}

void drawSingleTetramino(int numTetramino, int rotation) {

	const wchar_t *curr = tetraminosRotation[rotation][numTetramino];

	/* '*' significa fine tetramino */
	while (*curr != L'*') {

		/* '/' significa a capo */
		if (*curr == L'/') {
			printf("\n");
		} else {
			/* al posto di '_' stampa ' ' */
			printf("%lc ", *curr == L'_' ? L' ' : *curr);
		}

		/* prossimo carattere */
		++curr;
	}
}