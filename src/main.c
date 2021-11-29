/* #include <locale.h> /* Usato per scrivere caratteri unicode */
#include <stdio.h>
#include <stdlib.h> /* Random */
#include <string.h> /* memset() */
#include <time.h>	/* Seme per il random */
#include <wchar.h>	/* Usato per scrivere caratteri unicode */

#include "constants.h"
#include "main.h"

/**
 * 0x2550 -> 0x256C
 * 0x2550 ═ ║ ╒ ╓ ╔ ╕ ╖ ╗ ╘ ╙ ╚ ╛ ╜ ╝ ╞ ╟ 
 * 0x2560 ╠ ╡ ╢ ╣ ╤ ╥ ╦ ╧ ╨ ╩ ╪ ╫ ╬ 
 * 0x25a0 ■ □ ▢ ▣ ▤ ▥ ▦ ▧ ▨ ▩ 
 */

int main() {
	int			 i	 = 1;
	IVec2 pos = {5, 6};

	setup();

	clearScreen();

	insert(tetr_T, pos, i);
	screen[5][6] = '@';

	drawRemainingTetraminos();
	drawScreen();

	printf("\n");
	i++;
	if (i > 4) {
		i = 1;
	}

	getchar();

	cleanup();
	return 0;
}

void setup() {

	unsigned i = 0;

/* 	g_old_locale = setlocale(LC_ALL, NULL); */
	srand(time(0));

	for (i = 0; i < INITIAL_TETRAMINOS; i++) {
		runtimeTetraminos[i] = (char)(rand() % NUM_TETRAMINOS);
	}
	runtimeTetraminos[0] = 2;

/* 	setlocale(LC_ALL, "C.UTF-8"); */
}

void cleanup() {
/* 	setlocale(LC_ALL, g_old_locale); */
}

void drawScreen() {
	char i, j;

	for (i = 0; i < screenWidth; ++i) {
		printf("%c", '<');
		for (j = 0; j < screenHeight; ++j) {
			printf("%c", screen[i][j]);
		}
		printf("%c", '>');
		printf("\n");
	}
}

void clearScreen() {

	char i, j;

	for (i = 0; i < screenWidth; ++i) {
		for (j = 0; j < screenHeight; ++j) {
			screen[i][j] = ' ';
		}
	}
}

void insert(char *tetramino, IVec2 pos, int rot) {

	struct IVec2 index	  = pos;
	int			 i		  = 0;
	char		 advanceX = 1;
	char		 advanceY = 1;

	int *pt_x = nullptr;
	int *pt_y = nullptr;

	switch (rot) {
	case 1:
		pt_x	 = &index.y;
		pt_y	 = &index.x;
		advanceY = -1;
		break;

	case 2:
		pt_x = &index.x;
		pt_y = &index.y;
		break;

	case 3:
		pt_x	 = &index.y;
		pt_y	 = &index.x;
		advanceX = -1;
		break;

	case 4:
		pt_x	 = &index.x;
		pt_y	 = &index.y;
		advanceX = -1;
		advanceY = -1;
	}

	while (boundCheck(index) && tetramino[i] != '*') {

		if (tetramino[i] == '/') {
			index.y = pos.y;
			index.x += advanceX;
		} else {
			screen[*pt_x][*pt_y] = tetramino[i];
			index.y += advanceY;
		}

		i++;
	}
}

int boundCheck(IVec2 pos) {
	return pos.x < screenWidth && pos.x >= 0 && pos.y < screenHeight && pos.y >= 0;
}

void drawRemainingTetraminos() {
	unsigned i			 = 0;
	unsigned j			 = 0;
	unsigned index		 = 0;
	unsigned col		 = 0;
	unsigned rowIndex	 = 0;
	unsigned columnIndex = 0;
	unsigned numCols	 = 5;
	char *	 currTetramino;

	char row[50][2];

	for (i = 0; i < INITIAL_TETRAMINOS / numCols; ++i) {

		memset(row, ' ', 50 * 2);

		for (rowIndex = 0, j = 0; j < numCols; ++j) {
			unsigned relOrg = 0;

			/* Ottengo la stringa del tetramino */
			currTetramino = allTetraminos[runtimeTetraminos[i + j]];

			/* Fa il loop per ogni carattere della stringa */
			for (index = 0, columnIndex = 0; currTetramino[index] != '*'; ++index) {

				/* 
				 Se il carattere corrente è un 'a capo' -> '/' non fa niente,
				 altrimenti inserisce il carattere corrente 
				*/
				if (currTetramino[index] == '/') {
					columnIndex = 1;
					relOrg		= index + 1;
				} else {
					/* Se il carattere corrente e' '_' allora inserisci ' ' */
					row[rowIndex * 5 + index - relOrg][columnIndex] = currTetramino[index] == '_' ? ' ' : currTetramino[index];
				}
			}

			rowIndex++;
		}

		for (col = 0; col < 2; ++col) {
			for (index = 0; index < 50; ++index) {
				printf("%s", row[index][col] == '#' ? "#" : " ");
			}
			printf("\n");
		}

		printf("\n\n");
	}
}