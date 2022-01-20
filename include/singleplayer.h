#pragma once

#include <stdbool.h>

#include "constants.h"

void singlePlayerLoop();

void playerTurn(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]);

/**
 * Ritorna true se non ci sono più tetramini utilizzabili o se non c'è più posto per essi
 */
bool gameShouldEnd(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]);

/**
 * Inizializza i tetramini iniziali
 */
void setup(unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]);

/**
 * Cancella le righe piene e ritorna il numero di righe cancellate
 */
int clearLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Sposta le linee minori (quindi sopra) del valore dato di uno in giù
 * eliminando lo spazio vuoto
 */
void fixLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int row);
