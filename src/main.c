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
	int	  i	  = 1;
	IVec2 pos = {5, 6};

	setup();

	clearScreen();

	insert(tetr_T, pos, i);

	drawScreen();

	fall();

	printf("\n\n");

	drawScreen();

	pos.x = 0;

	printf("\n\n");

	insert(tetr_I, pos, 1);

	drawScreen();

	fall();

	printf("\n\n");

	drawScreen();

	printf("\n");
	i++;
	if (i > 4) {
		i = 1;
	}

	/* getchar(); */

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

void fall() {
	int i = 0;
	int j = 0;

	int _exit = 0;

	while (!_exit) {

		for (i = SCREENHEIGHT - 1; i >= 0 && !_exit; --i) {
			for (j = 0; j < SCREENWIDTH && !_exit; ++j) {
				if (screen[i][j] == '@') {
					if (i == SCREENHEIGHT - 1) {
						_exit = 1;
					}
					/* la prossima cella è libera? allora sposta! */
					if (screen[i + 1][j] != ' ') {
						_exit = 1;
					}
				}
			}

			for (j = 0; j < SCREENWIDTH && !_exit; ++j) {
				if (screen[i][j] == '@') {
					screen[i + 1][j] = '@';
					screen[i][j]	 = ' ';
				}
			}
		}
	}

	for (i = 0; i < SCREENHEIGHT; ++i) {
		for (j = 0; j < SCREENWIDTH; ++j) {
			if (screen[i][j] == '@') {
				screen[i][j] = '#';
			}
		}
	}
}

void drawScreen() {
	char i, j;

	for (i = 0; i < SCREENHEIGHT; ++i) {
		printf("%c", '<');
		for (j = 0; j < SCREENWIDTH; ++j) {
			printf("%c", screen[i][j]);
		}
		printf("%c", '>');
		printf("\n");
	}
}

void clearScreen() {

	char i, j;

	for (i = 0; i < SCREENHEIGHT; ++i) {
		for (j = 0; j < SCREENWIDTH; ++j) {
			screen[i][j] = ' ';
		}
	}
}

/**
 * rot 1 = su
 * rot 2 = destra
 * rot 3 = giù
 * rot 4 = sinistra
 */
void insert(char *tetramino, IVec2 pos, int rot) {

	IVec2 currPos = {0, 0};
	currPos.x = pos.y;
	currPos.y = pos.x;

	while (*tetramino != '*') {

		if (*tetramino == '/') {
			currPos.x = pos.y;
			++currPos.y;
		} else {
			screen[currPos.y][currPos.x] = *tetramino == '#' ? '@' : ' ';
			++currPos.x;
		}

		tetramino++;
	}

/* 
	struct IVec2 index	  = pos;
	int			 i		  = 0;
	char		 advanceX = 1;
	char		 advanceY = -1;

	int *pt_x = &index.x;
	int *pt_y = &index.y;

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
			screen[*pt_x][*pt_y] = tetramino[i] == '#' ? '@' : ' ';
			index.y += advanceY;
		}

		i++;
	} */
}

int boundCheck(IVec2 pos) {
	return pos.x < SCREENWIDTH && pos.x >= 0 && pos.y < SCREENHEIGHT && pos.y >= 0;
}

void drawRemainingTetraminos() {
	unsigned	   i		   = 0;
	unsigned	   j		   = 0;
	unsigned	   index	   = 0;
	unsigned	   col		   = 0;
	unsigned	   rowIndex	   = 0;
	unsigned	   columnIndex = 0;
	const unsigned numCols	   = 5;
	char *		   currTetramino;

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