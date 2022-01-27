/**
 * @file
 * Funzioni necessarie alla modalita' di gioco multi giocatore con e senza la AI
 */
#pragma once

#include <stdbool.h>

#include "constants.h"

/**
 * Gestisce il gioco tra due giocatori da tastiera o un giocatore e una AI o due AI
 * 
 * @param AI1 true se deve essere utilizzata la AI come giocatore 1
 * @param AI2 true se deve essere utilizzata la AI come giocatore 2
 */
void multiPlayerLoop(bool AI1, bool A12);

/**
 * La Cpu esplora ogni possibilita' per i tetramini \n 
 * Quindi N tetramini * 4 rotazioni * 10 colonne come caso peggiore \n
 * 
 * Per ogni combinazione trova:
 * * Il punto piu' alto risultante
 * * Il punto piu' basso risultante
 * * Quante righe vengono eliminate
 * * Quanti buchi vengono prodotti
 * 
 * @param screen matrice 15 * 10 rappresentante il campo di gioco
 * @param runtimeTetraminos tetramini ancora disponibili per essere usati
 */
void AITurn(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * Ottiene le statistiche del campo utili per decidere la mossa da fare per la AI
 * 
 * Le statistiche sono le seguenti: 
 * * results [0] -> il punto piu' alto e' il numero dalla prima riga che, partendo dall'alto, contiene un carattere non vuoto
 * * results [1] -> il punto piu' basso e' il numero della riga piu' bassa che presenta solo caratteri vuoti sopra
 * * results [2] -> le righe che vengono eliminate e' semplicimente il numero di righe senza caratteri vuoti
 * * results [3] -> il numero di buchi e' il numero di caratteri vuoti che presentano un carattere non vuoto sopra di esso
 * 
 * esempio di come potrebbe essere il campo di un giocatore
 * 
 * <pre>
 * x x         x x x x   
 * x x x   x x x x       
 * x x x   x x   x   x x 
 * 0 1 2 3 4 5 6 7 8 9 10
 * </pre>
 * 
 * alla colonna indice 3 e 10 non abbiamo buchi, i caratteri vuoti sono accessibili \n
 * alla colonna indice 6 e 9 abbiamo un singolo buco \n
 * alla colonna indice 8 abbiamo due buchi, non importa quanto in alto e' il carattere non vuoto \n
 * 
 * @param screen matrice 15 * 10 rappresentante il campo di gioco del quale calcolare le statistiche
 * @param result array dove mettere le diverse statistiche calcolate
 */
void multiCalcStats(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int result[4]);

/**
 * Combino le statische di una mossa insieme per ottenere quanto ottimale sia:
 * 1.  2 * results[0] \n
 *   visto che esprimo l'altezza come distanza dall'alto, un numero maggiore indica una posizione bassa, quindi migliore \n
 * 2. 10 * results[2] \n
 *   le righe eliminate sono le piu' importanti visto che migliorano tutti le altre statistiche \n
 * 3. -2 * results[3] \n
 *    piu' alto e' il numero di buchi piu' grande sara' il numero negativo, disincentivando le mosse che ne creano \n
 * 4. -1 * (results[1] - results[0]) \n
 *   la differenza tra il punto piu' alto ed il punto piu' basso mi da' una stima di quanto e' irregolare il campo \n
 * 
 * 
 * Lo score di una mossa e' quindi -> (1 + 2 + 3 + 4), piu' alto e' lo score, migliore e' la mossa
 * 
 * @param stats le statistiche dalle quali calcolare lo score
 * 
 * @return lo Score calcolato
 */
int calcScore(int stats[4]);

/**
 * Controlla se almeno un carattere sopra quello richiesto e' un tetramino, confermando che il carattere in questione sia un buco
 * 
 * @param screen matrice 15 * 10 rappresentante il campo di gioco nel quale controllare la presenza di un buco
 * @param row,column coordinate da controllare 
 * 
 * @return true se il carattere e' un buco, false altrimenti
 */
bool isAHole(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int row, int column);

/**
 * Decide se la partita e' ancora giocabile e ritorna un valora specifico per ogni scenario
 * Se uno dei due giocatori non ha piu' spazio nel campo vinco il giocatore opposto
 * Se i tetramino finiscono non posso sapere qui giocatore ha vinto, quindi ritorno un valore specifico per far fare la decisione al chiamante
 * 
 * @param screenG1 matrice 15 * 10 rappresentante il campo di gioco del giocatore 1 
 * @param screenG2 matrice 15 * 10 rappresentante il campo di gioco del giocatore 2
 * @param runtimeTetraminos tetramini ancora disponibili per essere usati
 * 
 * @return un intero rappresentate il vincitore:
 * * -1 se sono finiti i tetramini
 * * 0 se il gioco puo' continuare
 * * 1 se ha vinto il giocatore 1
 * * 2 se ha vinto il giocatore 2
 * 
 */
int multiGameShouldEnd(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * Inizializza il generatore di numeri casuali e sceglie i tetramini che saranno usati nella partita
 * 
 * @param runtimeTetraminos lista dei tratramini da inizializzare
 */
void multiSetup(unsigned char runtimeTetraminos[INITIAL_TETRAMINOS_2X]);

/**
 * Controlla se sono presenti linee piene in screenG1 e ne ritorna il numero
 * Se sono presenti 3 o piu' linee piene inverte le ultime n righe di screenG2
 * 
 * @param screenG1 matrice 15 * 10 rappresentante il campo di gioco del giocatore 1 nel quale cercare linee piene
 * @param screenG2 matrice 15 * 10 rappresentante il campo di gioco del giocatore 2 nel quale, in caso, invertire le ultime n righe
 * 
 * @return il numero di linee piene cancellate
 */
int multiClearLines(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Sposta in basso di una posizione tutte le linee da "line" in su
 * effettivamente cancellando la linea all'indice "line"
 * 
 * @param screen matrice 15 * 10 rappresentante il campo di gioco nel quale spostare le linee
 * @param line indice della linea dalla quale iniziare
 */
void multiFixLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int line);

/**
 * Inverte count linee nella parte piu' bassa del campo:
 * '_' -> '▩'
 * 'x' -> '_'
 * 
 * @param screen matrice 15 * 10 rappresentante il campo di gioco nel quale invertire le ultime "count" righe
 * @param count numero di linee da invertire
 */
void multiInvertLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int count);