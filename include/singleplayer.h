/**
 * @file
 * Funzioni necessarie alla modalita' di gioco singolo giocatore
 */
#pragma once

#include <stdbool.h>

#include "constants.h"

/**
 * Gestisce il gioco a giocatore singolo
 */
void singlePlayerLoop();

/**
 * Decide se la partita e' ancora giocabile e ritorna un vaore booleano appropriato
 * 
 * @param screen matrice 15 * 10 rappresentante il campo di gioco del giocatore
 * @param runtimeTetraminos tetramini ancora disponibili per essere usati
 * 
 * @return true non ci sono piu' tetramini utilizzabili o se non c'e' piu' spazio per inserirli nel campo, false altrimenti
 */
bool gameShouldEnd(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]);

/**
 * Inizializza il generatore di numeri casuali e sceglie i tetramini che saranno usati nella partita
 * 
 * @param runtimeTetraminos lista di tetramini da inizializzare
 */
void setup(unsigned char runtimeTetraminos[INITIAL_TETRAMINOS]);

/**
 * Cancella le righe piene e ritorna il numero di righe cancellate
 * 
 * @param screen matrice 15 * 10 rappresentante il campo di gioco del giocatore dove controllare la presenza di linee piene
 * 
 * @return il numero di linee piene cancellate
 */
int clearLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Sposta in basso di una posizione tutte le linee da line in su
 * effettivamente cancellando la linea all'indice line
 * 
 * @param screen matrice 15 * 10 rappresentante il campo di gioco del giocatore nel quale spostare le linee
 * @param row linea dalla quale iniziare a spostare i tetramini in basso
 */
void fixLines(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int row);
