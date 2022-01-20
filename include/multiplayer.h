#pragma once

#include "constants.h"

void multiPlayerLoop();

void multiPlayerLoopAI();

void playerTurn(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * La Cpu esplora ogni possibilità per i tetramini, 
 * N tetramini * 4 rotazioni * 10(o meno) posizioni.
 * Per ogni combinazione trova:
 * 	il punto più alto risultante
 * 	il punto più basso in cui poter mettere il tetramino
 * 	quante righe vengono eliminate
 * 	
 */
void AITurn(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * Ritorna -1 se sono finiti i tetramini false se il gioco può continuare, 1 se ha vinto il giocatore 1, 2 se ha vinto il giocatore 2
 * Se uno dei due giocatori non ha più spazio nel campo vinco il giocatore opposto
 * Se i tetramino finiscono non posso sapere qui giocatore ha vinto, quindi ritorno una variabile un valore specifico
 */
int multiGameShouldEnd(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

void multiSetup(unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

int multiClearLines(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH]);

void multiFixLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int line);

void multiInvertLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int count);