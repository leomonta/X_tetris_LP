#pragma once

#include "constants.h"

typedef struct IVec2 {
	int x, y;
} IVec2;

/**
 * 0x2550 -> 0x256C
 * 0x2550 ═ ║ ╒ ╓ ╔ ╕ ╖ ╗ ╘ ╙ ╚ ╛ ╜ ╝ ╞ ╟ 
 * 0x2560 ╠ ╡ ╢ ╣ ╤ ╥ ╦ ╧ ╨ ╩ ╪ ╫ ╬ 
 * 0x25a0 ■ □ ▢ ▣ ▤ ▥ ▦ ▧ ▨ ▩ 
 */

/**
 * Indico con '#' il quadrato pieno e con '_' il quadrato vuoto
 * ogni tetramino e' nel proprio array, ma per la larghezza di un tetramino uso '/' per indicare un "a capo"
 * inoltre uso il carattere '*' per indicare la fine 
 */

/**
 * # # # # *
 */
wchar_t tetr_I[] = {L'▣', L'▣', L'▣', L'▣', L'*'};

/**
 * _ # _ /
 * # # # *
 */
wchar_t tetr_T[8] = {L'_', L'▤', L'_', L'/',
					 L'▤', L'▤', L'▤', L'*'};

/**
 * # # /
 * # # *
 */
wchar_t tetr_Q[6] = {L'▥', L'▥', L'/',
					 L'▥', L'▥', L'*'};

/**
 * # # # /
 * # _ _ *
 */
wchar_t tetr_L[8] = {L'▩', L'▩', L'▩', L'/',
					 L'▩', L'_', L'_', L'*'};

/**
 * # # # /
 * _ _ # *
 */
wchar_t tetr_J[8] = {L'▦', L'▦', L'▦', L'/',
					 L'_', L'_', L'▦', L'*'};

/**
 * # # _ /
 * _ # # *
 */
wchar_t tetr_Z[8] = {L'▨', L'▨', L'_', L'/',
					 L'_', L'▨', L'▨', L'*'};

/**
 * _ # # /
 * # # _ *
 */
wchar_t tetr_S[8] = {L'_', L'▧', L'▧', L'/',
					 L'▧', L'▧', L'_', L'*'};

wchar_t *allTetraminos[NUM_TETRAMINOS] = {tetr_I, tetr_L, tetr_J, tetr_Q, tetr_Z, tetr_S, tetr_T};

/**
 * Indice rispetto a all Tetramino per indicare i tetramini disponibili al giocatore
 */
wchar_t runtimeTetraminos[INITIAL_TETRAMINOS];

const char *g_old_locale = nullptr;

wchar_t screen[SCREENHEIGHT][SCREENWIDTH];

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
void fall();

/**
 * Stampa a schermo i tetramini alla posizione corretta
 */
void drawScreen();

/**
 * Svuota lo schermo dai caratteri precedenti
 */
void clearScreen();

/**
 * Stampa i tetramini rimanenti in righe da 5
 */
void drawRemainingTetraminos();

/**
 * Inserisce il tetramino dato alla posizione specificata nello schermo ed alla rotazione specificata
 * 
 * rotazione:
 * 1 -> su
 * 2 -> destra
 * 3 -> giu
 * 4 -> sinistra
 */
void insert(wchar_t *tetramino, IVec2 pos, int rot);

/**
 * Ritorna 1 se pos risiede nei limiti dello schermo 0 altrimenti
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