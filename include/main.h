#pragma once

#include <stdbool.h>

#include "constants.h"

/**
 * Indico con un carattere il quadrato pieno e con '_' il quadrato vuoto
 * ogni tetramino e' nel proprio array, ma per la larghezza di un tetramino uso '/' per indicare un "a capo"
 * inoltre uso il carattere '*' per indicare la fine 
 */

/**
 * Indice rispetto a allTetramino per indicare i tetramini disponibili al giocatore
 */
unsigned char runtimeTetraminos[INITIAL_TETRAMINOS];

const char *g_old_locale = nullptr;

wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];

/**
 * Ritorna true se non ci sono più tetramini utilizzabili o se non c'è più posto per essi
 */
bool gameShouldEnd();

/**
 * Inizializza i tetramini iniziali
 */
void setup();

/**
 * Usato per restaurare il locale precedente
 */
void cleanup();

/**
 * Cancella le righe piene e ritorna il numero di righe cancellate
 */
int clearLines();

/**
 * Sposta le linee minore (quindi sopra) al valore dato di uno un giù
 * eliminando lo spazio vuoto
 */
void fixLines(int row);

/**
 * Calcola il numero di punti per riga eliminate insieme
 */
int calcPoints(int num);

/**
 * Rimuove tutti i caratteri presenti nel buffer dell'stdin
 */
void clearStdin();

/**
 * Riceve un input da tastiera e controlla la sua validità rispetto ai bound dati per parametro
 */
int getIntStdin(int lowBound, int HighBound);