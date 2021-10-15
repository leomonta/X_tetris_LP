#include <locale.h>
#include <stdio.h>
#include <wchar.h>

#include "constants.h"
#include "main.h"

/*0x2550 -> 0x256C
0x2550 ═ ║ ╒ ╓ ╔ ╕ ╖ ╗ ╘ ╙ ╚ ╛ ╜ ╝ ╞ ╟ 
0x2560 ╠ ╡ ╢ ╣ ╤ ╥ ╦ ╧ ╨ ╩ ╪ ╫ ╬ 
*/

int main() {

	setup();

	drawScreen();

	cleanup();
	return 0;
}

void setup() {

	struct IVec2 pos = {11, 11};
	char		 i, j;

	g_old_locale = setlocale(LC_ALL, NULL);

	setlocale(LC_ALL, "C.UTF-8");

	for (i = 0; i < screenWidth; ++i) {
		for (j = 0; j < screenHeight; ++j) {
			screen[i][j] = ' ';
		}
	}

	insert(tetr_L, pos);
}

void cleanup() {
	setlocale(LC_ALL, g_old_locale);
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

void insert(char *tetramino, struct IVec2 pos) {

	struct IVec2 index = pos;
	int			 i	   = 0;

	while (boundCheck(index) && tetramino[i] != '*') {

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