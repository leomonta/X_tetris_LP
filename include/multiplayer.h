#pragma once

#include <stdbool.h>

#include "constants.h"

void multiPlayerLoop();

void multiPlayerLoopAI();

void multiPlayerTurn(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * La Cpu esplora ogni possibilità per i tetramini, 
 * N tetramini * 4 rotazioni * 10(o meno) posizioni.
 * Per ogni combinazione trova:
 * 	il punto più alto risultante
 * 	il punto più basso risultante
 * 	quante righe vengono eliminate
 * 	quanti buchi vengono prodotti, come buco si intende uno spazio con almeno uno spazio occupato sopra 
 */
void AITurn(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * Ottiene le statistiche del campo utili per decidere la mossa da fare per la CPU
 * Tenendo conto che il carattere vuoto è -> L' '
 * 
 *  results [0] -> il punto più alto è il numero dalla prima riga che, partendo dall'alto, contiene un carattere non vuoto
 *  results [1] -> il punto più basso è il numero della riga più bassa che presenta solo caratteri vuoti sopra
 *  results [2] -> le righe che vengono eliminate è semplicimente il numero di righe senza caratteri vuoti
 *  results [3] -> il numero di buchi è il numero di caratteri vuoti che presentano un carattere non vuoto sopra di esso
 * 
 * esempio di come potrebbe essere il campo di un giocatore
 * 
 * # #         # # # # 
 * # # #   # # # #    
 * # # #   # #   #   # # 
 * 0 1 2 3 4 5 6 7 8 9 10
 * 
 * alla colonna indice 3 e 10 non abbiamo buchi, i caratteri vuoto sono accessibili
 * alla colonna indice 6 e 9 abbiamo un singolo buco
 * alla colonna indice 8 abbiamo due buchi, non importa quanto in alto è il carattere non vuoto.
 * 
 */
void multiCalcStats(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int result[4]);

/**
 * combinando le statische insieme ottengo quanto buona una mossa è
 * 
 * 1)  2 * results[0]   visto che esprimo l'altezza come distanza dall'alto, un numero maggiore indica una posizione bassa 
 * 2)  2 * results[1]   più bassi posso tenere i tetramini meglio è
 * 3) 10 * results[2]   le righe eliminate sono le più importanti visto che mmigliorano tutti le altre statistiche
 * 4) -1 * results[3]   più buchi ci sono peggio è
 * 5) -1 * abs (results[1] - results[0]) la differenza tra il punto più alto ed il punto più basso mi dà una stima di quanto è irregolare il campo
 * 
 * lo score di una mossa è quindi -> (1 + 2 + 3 + 4 + 5)), più alto è lo score, migliore è la mossa
 *
 */
int calcScore(int stats[4]);

/**
 * Controlla se almeno un carattere sopra quello richiesto è un tetramino
 */
bool isAHole(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int row, int column);

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