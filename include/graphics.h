#pragma once

#include "constants.h"

#include <wchar.h>

/**
 * Stampa a schermo i tetramini alla posizione corretta
 */
void drawScreen(wchar_t screen[SCREENHEIGHT][SCREENWIDTH]);

/**
 * Svuota lo schermo dai caratteri precedenti
 */
void clearScreen(wchar_t screen[SCREENHEIGHT][SCREENWIDTH]);

/**
 * Stampa i tetramini rimanenti in righe da 5
 */
void drawRemainingTetraminos(wchar_t *runtimeTetraminos);

/**
 * Stampa un singolo tetramino
 */
void drawSingleTetramino(const wchar_t *tetramino);