#pragma once

#include <stdbool.h>

#include "constants.h"

/**
 * Gestisce il gioco tra due giocatori da tastiera o un giocatore e una AI
 */
void multiPlayerLoop(bool AI);

/**
 * La Cpu esplora ogni possibilita' per i tetramini, 
 * N tetramini * 4 rotazioni * 10 colonne come caso peggiore
 * Per ogni combinazione trova:
 * 	il punto piu' alto risultante
 * 	il punto piu' basso risultante
 * 	quante righe vengono eliminate
 * 	quanti buchi vengono prodotti
 */
void AITurn(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * Ottiene le statistiche del campo utili per decidere la mossa da fare per la AI
 * Tenendo conto che il carattere vuoto e' -> ' '
 * 
 *  results [0] -> il punto piu' alto e' il numero dalla prima riga che, partendo dall'alto, contiene un carattere non vuoto
 *  results [1] -> il punto piu' basso e' il numero della riga piu' bassa che presenta solo caratteri vuoti sopra
 *  results [2] -> le righe che vengono eliminate e' semplicimente il numero di righe senza caratteri vuoti
 *  results [3] -> il numero di buchi e' il numero di caratteri vuoti che presentano un carattere non vuoto sopra di esso
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
 * alla colonna indice 8 abbiamo due buchi, non importa quanto in alto e' il carattere non vuoto.
 * 
 */
void multiCalcStats(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int result[4]);

/**
 * Combino le statische di una mossa insieme per ottenere quanto ottimale sia
 * 
 * 1)  2 * results[0]					visto che esprimo l'altezza come distanza dall'alto, un numero maggiore indica una posizione bassa, quindi miglire 
 * 2)  2 * results[1]					piu' bassi posso tenere i tetramini meglio e'
 * 3) 10 * results[2]					le righe eliminate sono le piu' importanti visto che migliorano tutti le altre statistiche
 * 4) -1 * results[3]					piu' alto e' il numero di buchi piu' grande sara' il numero negativo, disincentivando le mosse che ne creano
 * 5) -1 * abs(results[1] - results[0]) la differenza tra il punto piu' alto ed il punto piu' basso mi da' una stima di quanto e' irregolare il campo
 * 
 * Lo score di una mossa e' quindi -> (1 + 2 + 3 + 4 + 5), piu' alto e' lo score, migliore e' la mossa
 *
 */
int calcScore(int stats[4]);

/**
 * Controlla se almeno un carattere sopra quello richiesto e' un tetramino, confermando che il carattere in questione sia un buco
 */
bool isAHole(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int row, int column);

/**
 * Decide se la partita e' ancora giocabile e ritorna un valora specifico per ogni scenario
 * 
 * -1 -> se sono finiti i tetramini
 *  0 -> se il gioco puo' continuare
 *  1 -> se ha vinto il giocatore 1
 *  2 -> se ha vinto il giocatore 2
 * 
 * Se uno dei due giocatori non ha piu' spazio nel campo vinco il giocatore opposto
 * Se i tetramino finiscono non posso sapere qui giocatore ha vinto, quindi ritorno un valore specifico per far fare la decisione al chiamante
 */
int multiGameShouldEnd(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * Inizializza il generatore di numeri casuali e sceglie i tetramini che saranno usati nella partita
 */
void multiSetup(unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * Controlla se sono presenti linee piene in screenG1 e ne ritorna il numero
 * Se sono presenti 3 o piu' linee piene inverte le ultime n righe di screenG2
 */
int multiClearLines(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Sposta in basso di una posizione tutte le linee da line in su
 * effettivamente cancellando la linea all'indice line
 */
void multiFixLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int line);

/**
 * Inverte count linee nella parte piu' bassa del campo:
 * ' ' -> '▩'
 * '#' -> ' '
 */
void multiInvertLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int count);