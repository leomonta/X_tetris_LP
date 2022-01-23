#pragma once

#include <stdbool.h>

#include "constants.h"

/**
 * Gestisce il gioco a giocatore singolo
 */
void singlePlayerLoop();

/**
 * Decide se la partita e' ancora giocabile e ritorna un vaore booleano appropriato
 * true(1)  -> non ci sono piu' tetramini utilizzabili o se non c'e' piu' spazio per inserirli nel campo
 * false(0) -> la partita e' ancora giocabile
 * 
 */
bool gameShouldEnd(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]);

/**
 * Inizializza il generatore di numeri casuali e sceglie i tetramini che saranno usati nella partita
 */
void setup(unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]);

/**
 * Cancella le righe piene e ritorna il numero di righe cancellate
 */
int clearLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Sposta in basso di una posizione tutte le linee da line in su
 * effettivamente cancellando la linea all'indice line
 */
void fixLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int row);
