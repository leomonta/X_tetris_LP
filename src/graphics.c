#include "graphics.h"
#include "utf8.h"

#include <stdio.h>

void drawRemainingTetraminos(wchar_t *runtimeTetraminos) {
	unsigned	   i		   = 0;
	unsigned	   j		   = 0;
	unsigned	   index	   = 0;
	unsigned	   rowIndex	   = 0;
	unsigned	   columnIndex = 0;
	const unsigned numCols	   = 5;
	wchar_t const *currTetramino;

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
	for (i = 0; i < INITIAL_TETRAMINOS / numCols; ++i) {

		/* svuoto la riga */
		wmemset(&row[0][0], L' ', 25 * 2);

		/* per il numero di colonne in una singola riga */
		for (columnIndex = 0; columnIndex < numCols; ++columnIndex) {
			/* 
			offset negativo per scrivere alla posizione corretta della riga inferiore quando
			avviene il cambiamento della sottoriga
			 */
			unsigned relOrg = 0;

			/* Ottengo la stringa del tetramino */
			currTetramino = allTetraminos[runtimeTetraminos[i * numCols + columnIndex]];

			/* in caso di tetramino rimosso salta */
			if (currTetramino == nullptr) {
				continue;
			}

			/* Fa il loop per ogni carattere della stringa */
			for (index = 0, rowIndex = 0; currTetramino[index] != '*'; ++index) {

				/* 
				Se il carattere corrente è un 'a capo' -> '/' mi sposto sulla riga inferiore, aggiorno l'offet di sottocolonna
				altrimenti inserisce il carattere corrente 
				*/
				if (currTetramino[index] == '/') {
					rowIndex = 1;
					relOrg	 = index + 1;
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

				u8_printf("%lc ", row[j][index]);
				/*  printf("%c ", row[j][index] == L' ' ? ' ' : '#'); */
			}

			printf("\n");
		}

		printf("\n\n");
	}
}

void drawScreen(wchar_t screen[SCREENHEIGHT][SCREENWIDTH]) {
	char i, j;

	u8_printf("╔═════════════════════╗\n");

	for (i = 0; i < SCREENHEIGHT; ++i) {
		u8_printf("%lc ", L'║');
		for (j = 0; j < SCREENWIDTH; ++j) {
			u8_printf("%lc ", screen[i][j]);
		}
		u8_printf("%lc", L'║');
		printf("\n");
	}
	u8_printf("╚═════════════════════╝\n");
}

void clearScreen(wchar_t screen[SCREENHEIGHT][SCREENWIDTH]) {

	wmemset(&screen[0][0], L' ', SCREENHEIGHT * SCREENWIDTH);
}

void drawSingleTetramino(const wchar_t *tetramino) {

	wchar_t *curr = (wchar_t *)(tetramino);

	while (*curr != L'*') {

		if (*curr == L'/') {
			printf("\n");
		} else {
			u8_printf("%lc ", *curr == L'_' ? L' ': *curr);
		}

		++curr;
	}
}