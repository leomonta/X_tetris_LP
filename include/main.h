#pragma once

#include "constants.h"

typedef struct IVec2 {
	int x, y;
} IVec2;

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

int gameShouldEnd();

/**
 * Inizializza i tetramini iniziali
 */
void setup();

/**
 * Usato per restaurare il locale precedente
 */
void cleanup();

/**
 * Fa cadere i teramini fluttuanti fino al punto più basso che possono
 */
void fall(IVec2 pos);

/**
 * Rimpiazza i tetramini temporanei segnati da '@' con il wchar dato come parametro
 */
void replaceTempTetr(wchar_t replaceWith);

/**
 * Inserisce il tetramino dato alla posizione specificata nello schermo ed alla rotazione specificata
 * ritorna 0 se l'operazione ha avuto successo, 1 in caso contrario
 * 
 * rotazione:
 * 1 -> su
 * 2 -> destra
 * 3 -> giu
 * 4 -> sinistra
 */
int insert(const wchar_t *tetramino, IVec2 pos, int rot);

/**
 * Ritorna 0 se pos risiede nei limiti dello schermo 1 altrimenti
 */
int checkBounds(IVec2 pos);

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
 * Calcola il numero di punti per riga elimincate insieme
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