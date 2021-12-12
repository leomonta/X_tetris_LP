#include "tetramino.h"

void fall(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	int i       = 0;
	int j       = 0;
	int currRow = 0;

	bool _exit = 0;

	while (!_exit) {

		for (i = SCREEN_HEIGHT - 1; i >= 0 && !_exit; --i) {
			for (j = 0; j < SCREEN_WIDTH && !_exit; ++j) {
				if (screen[i][j] == '@') {
					if (i == SCREEN_HEIGHT - 1) {
						_exit = true;
						break;
					}
					/* la prossima cella è libera? allora sposta! */
					if (screen[i + 1][j] != ' ' && screen[i + 1][j] != L'@') {
						_exit = true;
					}
				}
			}
		}
		for (i = currRow + 1; i >= currRow; --i) {
			for (j = 0; j < SCREEN_WIDTH && !_exit; ++j) {
				if (screen[i][j] == '@') {
					screen[i + 1][j] = '@';
					screen[i][j]     = ' ';
				}
			}
		}
		currRow++;
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

bool insert(const wchar_t *tetramino, wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int column, int rot) {

	int currColumn = column;
	int currRow    = 0;

	while (*tetramino != '*') {

		if (*tetramino == '/') {
			currColumn = column;
			++currRow;
		} else {

			if (*tetramino != L'_') {

				/* Sto per rimpiazzare un tetramino già presente o fuori dallo schermo*/
				if (screen[currRow][currColumn] != L' ' || !checkBounds(currColumn, currRow)) {
					return false;
				}

				screen[currRow][currColumn] = L'@';
			}
			++currColumn;
		}

		++tetramino;
	}

	return true;
}

bool checkBounds(int column, int row) {
	return (column >= 0 && column < SCREEN_HEIGHT && row >= 0 && row < SCREEN_WIDTH);
}