/**
 * @file
 * Funzioni di manipolazione di tetramini nello campo di gioco
 */
#pragma once

#include <stdbool.h>

#include "constants.h"

/**
 * Fa cadere i teramini fluttuanti, segnati da '@', fino al punto piu' basso che possono
 * 
 * @param screen matrice 15 * 10 rappresentante il campo di gioco del giocatore nel quale far cadere il tetramino temporaneo
 */
void fall(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Rimpiazza i tetramini temporanei segnati da '@' con il wchar_t dato come parametro
 * 
 * @param replaceWith carattere con cui rimpiazzre i tetramini temporanei
 * @param screen matrice 15 * 10 rappresentante il campo di gioco del giocatore nel quale rimpiazzare il tetramino temporaneo
 */
void replaceTempTetr(wchar_t replaceWith, wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Inserisce il tetramino dato alla posizione specificata nello schermo ed alla rotazione specificata
 * 
 * rotazione:
 * * 0 -> 0°   in senso orario
 * * 1 -> 90°  in senso orario
 * * 2 -> 180° in senso orario
 * * 3 -> 270° in senso orario
 * 
 * @param numTetramino indice del tetramino rispetto a allTetraminos che deve essere inserito
 * @param screen matrice 15 * 10 rappresentante il campo di gioco del giocatore nel quale inserire il tetramino
 * @param column,row coordinate dalle quali iniziare a inserire il tetramino
 * 
 * @return true se l'operazione ha avuto successo, false altrimenti
 */
bool insert(int numTetramino, wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], int column, int rot);

/**
 * Date delle coordinate ritorna de rientrano tra i limit del campo 10 * 15
 * 
 * @param column,row coordinate da controllare
 */
bool checkBounds(int column, int row);

/**
 * Gestisce il turno di un giocatore controllando gli input da tastiera e raccogliendo i dati per svolgere la mossa selezionata 
 * 
 * @param screen matrice 15 * 10 rappresentante il campo di gioco del giocatore nel quale operare
 * @param runtimeTetraminos lista di tetramini disponibili per essere usati
 * @param size lunghezza della lista di tetramini
 */
void playerTurn(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH], unsigned char *runtimeTetraminos, int size);