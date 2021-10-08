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

	char i, j;
	for (i = 0; i < screenWidth; ++i) {
		for (j = 0; j < screenHeight; ++j) {
			screen[i][j] = '_';
		}
	}
}

void drawScreen() {
	char i, j;
	for (i = 0; i < screenWidth; ++i) {
		for (j = 0; j < screenHeight; ++j) {
			printf("%c", screen[i][j]);
		}
		printf("\n");
	}
}