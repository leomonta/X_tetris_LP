#pragma once

#include "constants.h"

void multiPlayerLoop();

/**
 * Ritorna -1 se sono finiti i tetramini false se il gioco può continuare, 1 se ha vinto il giocatore 1, 2 se ha vinto il giocatore 2
 * Se uno dei due giocatori non ha più spazio nel campo vinco il giocatore opposto
 * Se i tetramino finiscono non posso sapere qui giocatore ha vinto, quindi ritorno una variabile un valore specifico
 */
int multiGameShouldEnd(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

void multiSetup(unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

int multiClearLines();

void multiFixLines();