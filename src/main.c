/* #include <locale.h> /* Usato per scrivere caratteri unicode */
#include <math.h> /* pow */
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
	int	  i			   = 1;
	IVec2 inputPos	   = {0, 0};
	int	  inputTetr	   = 0;
	char *selectedTetr = nullptr;
	int	  points	   = 0;

	setup();

	clearScreen();

	/* loop 1 */
	while (1) {

		drawRemainingTetraminos();
		printf("Scegli il tetramino\nnumero -> ");

		scanf("%d", &inputTetr);
		printf("riga -> ");
		scanf("%d", &inputPos.x);
		printf("colonna -> ");
		scanf("%d", &inputPos.y);

		selectedTetr = allTetraminos[runtimeTetraminos[inputTetr]];

		insert(selectedTetr, inputPos, 1);

		fall();

		points = calcPoints(clearLines());

		drawScreen();
		printf("points -> %d\n\n", points);
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

		for (i = SCREENHEIGHT - 2; i >= 0 && !_exit; --i) {
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
		printf("%c ", '<');
		for (j = 0; j < SCREENWIDTH; ++j) {
			printf("%c ", screen[i][j]);
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

	IVec2 currPos = pos;

	while (*tetramino != '*') {

		if (*tetramino == '/') {
			currPos.x = pos.x;
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
	unsigned	   rowIndex	   = 0;
	unsigned	   columnIndex = 0;
	const unsigned numCols	   = 5;
	char *		   currTetramino;

	char row[2][25];

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
		memset(row, ' ', 25 * 2);

		/* per il numero di colonne in una singola riga */
		for (columnIndex = 0; columnIndex < numCols; ++columnIndex) {
			/* 
			offset negativo per scrivere alla posizione corretta della riga inferiore quando
			avviene il cambiamento della sottoriga
			 */
			unsigned relOrg = 0;

			/* Ottengo la stringa del tetramino */
			currTetramino = allTetraminos[runtimeTetraminos[i + columnIndex]];

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
					row[rowIndex][columnIndex * 5 + index - relOrg] = currTetramino[index] == '_' ? ' ' : currTetramino[index];
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

				printf("%s ", row[j][index] == '#' ? "#" : " ");
			}
			printf("\n");
		}

		printf("\n\n");
	}
}

int clearLines() {
	int i	 = 0;
	int j	 = 0;
	int temp = 1;

	int res = 0;

	for (i = 0; i < SCREENHEIGHT; ++i) {
		for (j = 0; j < SCREENWIDTH; ++j) {
			if (screen[i][j] == ' ') {
				temp = 0;
				break;
			}
		}
		if (temp == 1) {
			memset(screen[i], ' ', SCREENWIDTH);
			fixLines(i);
			++res;
		}
		temp = 1;
	}

	return res;
}

void fixLines(int row) {
	int i = 0;
	for (i = row; i > 0; --i) {
		memcpy(screen[i], screen[i - 1], SCREENWIDTH);
	}

	memset(&screen, ' ', SCREENWIDTH);
}

int calcPoints(int num) {
	/*2^(righe eliminate - 1) * 1.5f arrotondato per difetto*/
	return (int)(pow(2, num - 1) * 1.5);
}