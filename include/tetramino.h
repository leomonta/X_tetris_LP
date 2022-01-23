#pragma once

#include <stdbool.h>
#include <wchar.h>

#include "constants.h"

/**
 * Fa cadere i teramini fluttuanti, segnati da '@', fino al punto piu' basso che possono
 */
void fall(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Rimpiazza i tetramini temporanei segnati da '@' con il wchar_t dato come parametro
 */
void replaceTempTetr(wchar_t replaceWith, wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Inserisce il tetramino dato alla posizione specificata nello schermo ed alla rotazione specificata
 * Ritorna
 * true(1)  -> l'operazione ha avuto successo
 * false(0) -> l'operazione non puo' essere effettuata
 * 
 * rotazione:
 * 0 -> 0°   in senso orario
 * 1 -> 90°  in senso orario
 * 2 -> 180° in senso orario
 * 3 -> 270° in senso orario
 */
bool insert(int numTetramino, wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int column, int rot);

/**
 * Date delle coordinate ritorna de rientrano tra i limit del campo 10 * 15
 */
bool checkBounds(int column, int row);

/**
 * Gestisce il turno di un giocatore controllando gli input da tastiera e raccogliendo i dati per svolgere la mossa selezionata 
 */
void playerTurn(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char *runtimeTetraminos, int size);