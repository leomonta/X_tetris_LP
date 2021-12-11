/* #include <locale.h> /* Usato per scrivere caratteri unicode */
#include <locale.h>
#include <math.h> /* pow */
#include <stdio.h>
#include <stdlib.h> /* Random */
#include <string.h> /* memset() */
#include <time.h>	/* Seme per il random */
#include <wchar.h>	/* Usato per scrivere caratteri unicode */

#include "constants.h"
#include "graphics.h"
#include "main.h"

int main() {
	int			   i			= 1;
	IVec2		   inputPos		= {0, 0};
	int			   inputTetr	= 0;
	const wchar_t *selectedTetr = nullptr;
	int			   points		= 0;
	wchar_t		   charToDraw;

	setup();

	clearScreen(screen);

	/* loop 1 */
	while (!gameShouldEnd()) {

		drawRemainingTetraminos(runtimeTetraminos);

		printf("Scegli il tetramino\n");
		inputTetr = getIntStdin(0, INITIAL_TETRAMINOS);

		if (runtimeTetraminos[inputTetr] == INVALID_TETRAMINO) {
			printf("Il tetramino n. %d è già stato usato, sceglierne un'altro!\n", inputTetr);
			continue;
		}

		selectedTetr = allTetraminos[runtimeTetraminos[inputTetr]];

		drawSingleTetramino(selectedTetr);

		printf("\n\nScegli la colonna\n");
		inputPos.x = getIntStdin(0, SCREEN_WIDTH);

		if (!insert(selectedTetr, inputPos, 1)) {
			/* fallimento */
			replaceTempTetr(L' ');

			printf("il tetramino selezionato non può essere posizionato dove richiesto\n");

			continue;
		}

		runtimeTetraminos[inputTetr] = INVALID_TETRAMINO;

		fall(inputPos);
		replaceTempTetr(selectedTetr[1]);

		points += calcPoints(clearLines());

		drawScreen(screen);
		printf("points -> %d\n\n", points);
	}

	return 0;
}

bool gameShouldEnd() {
	int	  i					 = 0;
	int	  j					 = 0;
	bool  finishedTetraminos = true;
	bool  spaceFinished		 = true;
	IVec2 pos				 = {0, 0};

	for (i = 0; i < INITIAL_TETRAMINOS; ++i) {
		if (runtimeTetraminos[i] != INVALID_TETRAMINO) {
			finishedTetraminos = 0;
			break;
		}
	}

	if (finishedTetraminos) {
		return true;
	}

	for (i = 0; i < INITIAL_TETRAMINOS; i++) {
		for (j = 0; j < SCREEN_WIDTH; j++) {
			pos.x = j;
			if (insert(allTetraminos[runtimeTetraminos[i]], pos, 0)) {
				spaceFinished = false;
				replaceTempTetr(L' ');
				break;
			}
		}
	}

	return spaceFinished;
}

void setup() {

	unsigned i = 0;
	unsigned temp;

	g_old_locale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "C.UTF-8");

	temp = (unsigned)(time(0));
	srand(temp);

	for (i = 0; i < INITIAL_TETRAMINOS; i++) {
		runtimeTetraminos[i] = (char)(i % NUM_TETRAMINOS);
	}
}

void cleanup() {
	setlocale(LC_ALL, g_old_locale);
}

void fall(IVec2 pos) {
	int i = 0;
	int j = 0;

	int _exit = 0;

	while (!_exit) {

		for (i = SCREEN_HEIGHT - 1; i >= 0 && !_exit; --i) {
			for (j = 0; j < SCREEN_WIDTH && !_exit; ++j) {
				if (screen[i][j] == '@') {
					if (i == SCREEN_HEIGHT - 1) {
						_exit = 1;
						break;
					}
					/* la prossima cella è libera? allora sposta! */
					if (screen[i + 1][j] != ' ' && screen[i + 1][j] != L'@') {
						_exit = 1;
					}
				}
			}
		}
		for (i = pos.y + 1; i >= pos.y; --i) {
			for (j = 0; j < SCREEN_WIDTH && !_exit; ++j) {
				if (screen[i][j] == '@') {
					screen[i + 1][j] = '@';
					screen[i][j]	 = ' ';
				}
			}
		}
		pos.y++;
	}
}

void replaceTempTetr(wchar_t replaceWith) {

	int i, j;

	for (i = 0; i < SCREEN_HEIGHT; ++i) {
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			if (screen[i][j] == '@') {
				screen[i][j] = replaceWith;
			}
		}
	}
}

bool insert(const wchar_t *tetramino, IVec2 pos, int rot) {

	IVec2 currPos = pos;

	while (*tetramino != '*') {

		if (*tetramino == '/') {
			currPos.x = pos.x;
			++currPos.y;
		} else {

			/* Sto per rimpiazzare un tetramino già presente o fuori dallo schermo*/
			if (screen[currPos.y][currPos.x] != L' ' || !checkBounds(currPos)) {
				return false;
			}

			screen[currPos.y][currPos.x] = *tetramino == (wchar_t)('_') ? (wchar_t)(' ') : L'@';
			++currPos.x;
		}

		tetramino++;
	}

	return true;
}

bool checkBounds(IVec2 pos) {
	return (pos.x < SCREEN_WIDTH && pos.x >= 0 && pos.y < SCREEN_HEIGHT && pos.y >= 0);
}

int clearLines() {
	int i	 = 0;
	int j	 = 0;
	int temp = 1;

	int res = 0;

	for (i = 0; i < SCREEN_HEIGHT; ++i) {
		for (j = 0; j < SCREEN_WIDTH; ++j) {
			if (screen[i][j] == L' ') {
				temp = 0;
				break;
			}
		}
		if (temp == 1) {
			wmemset(screen[i], L' ', SCREEN_WIDTH);
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
		wmemcpy(screen[i], screen[i - 1], SCREEN_WIDTH);
	}

	wmemset(&screen[0][0], L' ', SCREEN_WIDTH);
}

int calcPoints(int num) {
	/*2^(righe eliminate - 1) * 1.5f arrotondato per difetto*/
	return (int)(pow(2, num - 1) * 1.5);
}

void clearStdin() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {
	}
}

int getIntStdin(int lowBound, int highBound) {
	int retVal;
	int inputTetr;

	while (1) {

		printf("numero -> ");
		retVal = scanf("%d", &inputTetr);

		clearStdin();

		if (retVal == 1 && inputTetr >= lowBound && inputTetr <= highBound - 1) {
			break;
		}

		printf("Devi inserire un valore tra 0 e %d\n", highBound - 1);
	}

	return inputTetr;
}
