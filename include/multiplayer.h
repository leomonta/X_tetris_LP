#pragma once

#include <stdbool.h>

#include "constants.h"

/**
 * Gestisce il gioco tra due giocatori da tastiera o un giocatore e una AI
 */
void multiPlayerLoop(bool AI);

/**
 * La Cpu esplora ogni possibilità per i tetramini, 
 * N tetramini * 4 rotazioni * 10 colonne come caso peggiore
 * Per ogni combinazione trova:
 * 	il punto più alto risultante
 * 	il punto più basso risultante
 * 	quante righe vengono eliminate
 * 	quanti buchi vengono prodotti
 */
void AITurn(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * Ottiene le statistiche del campo utili per decidere la mossa da fare per la AI
 * Tenendo conto che il carattere vuoto è -> ' '
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
 * alla colonna indice 3 e 10 non abbiamo buchi, i caratteri vuoti sono accessibili
 * alla colonna indice 6 e 9 abbiamo un singolo buco
 * alla colonna indice 8 abbiamo due buchi, non importa quanto in alto è il carattere non vuoto.
 * 
 */
void multiCalcStats(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int result[4]);

/**
 * Combino le statische di una mossa insieme per ottenere quanto ottimale sia
 * 
 * 1)  2 * results[0]					visto che esprimo l'altezza come distanza dall'alto, un numero maggiore indica una posizione bassa, quindi miglire 
 * 2)  2 * results[1]					più bassi posso tenere i tetramini meglio è
 * 3) 10 * results[2]					le righe eliminate sono le più importanti visto che migliorano tutti le altre statistiche
 * 4) -1 * results[3]					più alto è il numero di buchi più grande sarà il numero negativo, disincentivando le mosse che ne creano
 * 5) -1 * abs(results[1] - results[0]) la differenza tra il punto più alto ed il punto più basso mi dà una stima di quanto è irregolare il campo
 * 
 * Lo score di una mossa è quindi -> (1 + 2 + 3 + 4 + 5), più alto è lo score, migliore è la mossa
 *
 */
int calcScore(int stats[4]);

/**
 * Controlla se almeno un carattere sopra quello richiesto è un tetramino, confermando che il carattere in questione sia un buco
 */
bool isAHole(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int row, int column);

/**
 * Decide se la partita è ancora giocabile e ritorna un valora specifico per ogni scenario
 * 
 * -1 -> se sono finiti i tetramini
 *  0 -> se il gioco può continuare
 *  1 -> se ha vinto il giocatore 1
 *  2 -> se ha vinto il giocatore 2
 * 
 * Se uno dei due giocatori non ha più spazio nel campo vinco il giocatore opposto
 * Se i tetramino finiscono non posso sapere qui giocatore ha vinto, quindi ritorno un valore specifico per far fare la decisione al chiamante
 */
int multiGameShouldEnd(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * Inizializza il generatore di numeri casuali e sceglie i tetramini che saranno usati nella partita
 */
void multiSetup(unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * Controlla se sono presenti linee piene in screenG1 e ne ritorna il numero
 * Se sono presenti 3 o più linee piene inverte le ultime n righe di screenG2
 */
int multiClearLines(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Sposta in basso di una posizione tutte le linee da line in su
 * effettivamente cancellando la linea all'indice line
 */
void multiFixLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int line);

/**
 * Inverte count linee nella parte più bassa del campo:
 * ' ' -> '▩'
 * '#' -> ' '
 */
void multiInvertLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int count);