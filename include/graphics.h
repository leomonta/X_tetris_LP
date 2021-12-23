#pragma once

#include "constants.h"

#include <wchar.h>

/**
 * Stampa a schermo i tetramini alla posizione corretta
 */
void drawScreen(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Svuota lo schermo dai caratteri precedenti
 */
void clearScreen(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Stampa i tetramini rimanenti in righe da 5
 */
void drawRemainingTetraminos(unsigned char *runtimeTetraminos);

/**
 * Stampa un singolo tetramino
 */
void drawSingleTetramino(int numTetramino, int rotation);