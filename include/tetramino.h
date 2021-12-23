#pragma once

#include <stdbool.h>
#include <wchar.h>

#include "constants.h"

/**
 * Fa cadere i teramini fluttuanti fino al punto più basso che possono
 */
void fall(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Rimpiazza i tetramini temporanei segnati da '@' con il wchar dato come parametro
 */
void replaceTempTetr(wchar_t replaceWith, wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Inserisce il tetramino dato alla posizione specificata nello schermo ed alla rotazione specificata
 * ritorna true se l'operazione ha avuto successo, false in caso contrario
 * 
 * rotazione:
 * 0 -> 0°   in senso orario
 * 1 -> 90°  in senso orario
 * 2 -> 180° in senso orario
 * 3 -> 270° in senso orario
 */
bool insert(int numTetramino, wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int column, int rot);

bool checkBounds(int column, int row);