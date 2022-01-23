#pragma once

#include "constants.h"

#include <wchar.h>

/**
 * Stampa i tetramini disponibili rimanenti in righe da 10
 */
void drawRemainingTetraminos(unsigned char *runtimeTetraminos, unsigned int size);

/**
 * Stampa a schermo i tetramini alla posizione corretta con una cornice
 */
void drawScreen(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Stampo lo schermo di entrambi i giocatori uno di fianco all'altro
 */
void multiDrawScreen(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Pulisce la matrice dello schermo mettendo tutti caratteri vuoti 
 */
void clearScreen(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Stampa un singolo tetramino da mostrare all'utente per conferma
 */
void drawSingleTetramino(int numTetramino, int rotation);