#pragma once

#include <stdbool.h>

#include "utils.h"
#include "constants.h"


void singlePlayerLoop();

/**
 * Ritorna true se non ci sono più tetramini utilizzabili o se non c'è più posto per essi
 */
bool gameShouldEnd(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]);

/**
 * Inizializza i tetramini iniziali
 */
void setup(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]);

/**
 * Usato per restaurare il locale precedente
 */
void cleanup();

/**
 * Cancella le righe piene e ritorna il numero di righe cancellate
 */
int clearLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Sposta le linee minore (quindi sopra) al valore dato di uno un giù
 * eliminando lo spazio vuoto
 */
void fixLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int row);
