#include <stdio.h>

#include "constants.h"
#include "main.h"

int main() {

	setup();
	screen[8][8] = '#';

	drawScreen();

	return 0;
}

void setup() {

	struct IVec2 pos = {1, 1};
	char		 i, j;

	for (i = 0; i < screenWidth; ++i) {
		for (j = 0; j < screenHeight; ++j) {
			screen[i][j] = '_';
		}
	}

	insert(tetr_L, pos);
}

void drawScreen() {
	char i, j;

	for (i = 0; i < screenWidth; ++i) {
		printf("%c", 126);
		for (j = 0; j < screenHeight; ++j) {
			printf("%c", screen[i][j]);
		}
		printf("%c", 186);
		printf("\n");
	}
}

void insert(char *tetramino, struct IVec2 pos) {

	struct IVec2 index = pos;
	int			 i	   = 0;

	while (tetramino[i] != '*') {

		if (tetramino[i] == '/') {
			index.x = pos.x;
			index.y++;
		} else {
			screen[index.y][index.x] = tetramino[i];
			index.x++;
		}

		i++;
	}
}

int boundCheck(struct IVec2 pos) {
	return pos.x < screenWidth && pos.x >= 0 && pos.y < screenHeight && pos.y >= 0;
}