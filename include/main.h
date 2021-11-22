#pragma once

#include "constants.h"

struct IVec2 {
	int x, y;
};

/**
 * 0x2550 -> 0x256C
 * 0x2550 ═ ║ ╒ ╓ ╔ ╕ ╖ ╗ ╘ ╙ ╚ ╛ ╜ ╝ ╞ ╟ 
 * 0x2560 ╠ ╡ ╢ ╣ ╤ ╥ ╦ ╧ ╨ ╩ ╪ ╫ ╬ 
 */

/**
 * Indico con '#' il quadrato pieno e con '_' il quadrato vuoto
 * ogni tetramino e' nel proprio array, ma per la larghezza di un tetramino uso '/' per indicare un "a capo"
 * inoltre uso il carattere '*' per indicare la fine 
 */

/**
 * # # # # *
 */
char tetr_I[5] = {'#', '#', '#', '#', '*'};

/**
 * _ # _ /
 * # # # *
 */
char tetr_T[8] = {'_', '#', '_', '/',
				  '#', '#', '#', '*'};

/**
 * # # /
 * # # *
 */
char tetr_Q[6] = {'#', '#', '/',
				  '#', '#', '*'};

/**
 * # # # /
 * # _ _ *
 */
char tetr_L[8] = {'#', '#', '#', '/',
				  '#', '_', '_', '*'};

/**
 * # # _ /
 * _ # # *
 */
char tetr_S[8] = {'#', '#', '_', '/',
				  '_', '#', '#', '*'};

char *allTetraminos[NUM_TETRAMINOS] = {tetr_I, tetr_L, tetr_Q, tetr_S, tetr_T};

/**
 *Indice rispetto a allTetramino per indicare i tetramini disponibili al giocatore
 */
char runtimeTetraminos[INITIAL_TETRAMINOS];

const char *g_old_locale = nullptr;

char screen[screenWidth][screenHeight];

void setup();
void cleanup();
void drawScreen();
void clearScreen();
void drawRemainingTetraminos();

/**
 * Inserisce il tetramino dato alla posizione specificata nello schermo ed alla rotazione specificata
 * 
 * rotazione:
 * 1 -> su
 * 2 -> destra
 * 3 -> giu
 * 4 -> sinistra
 */
void insert(char *tetramino, struct IVec2 pos, int rot);

/**
 * Ritorna 1 se pos risiede nei limiti dello schermo 0 altrimenti
 */
int checkBounds(struct IVec2 pos);