#pragma once

#include "constants.h"

#include <wchar.h>

/**
 * Stampa a schermo i tetramini alla posizione corretta
 */
void drawScreen(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Stampo lo schermo di entrambi i giocatori uno di fianco all'altro, con relativo punteggio
 */
void multiDrawScreen(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH], int pointsG1, int pointsG2);

/**
 * Svuota lo schermo dai caratteri precedenti
 */
void clearScreen(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Stampa i tetramini rimanenti in righe da 5
 */
void drawRemainingTetraminos(unsigned char *runtimeTetraminos, unsigned int size);

/**
 * Stampa un singolo tetramino
 */
void drawSingleTetramino(int numTetramino, int rotation);