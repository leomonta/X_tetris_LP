/**
 * @file
 * Funzioni di utilita' varia: \n
 * I\O \n
 * setup \n
 */
#pragma once

#include <stdbool.h>

#include "constants.h"

/**
 * Calcola il numero di punti dati dalle righe eliminate insieme
 * 
 * @param num numero di righe eliminate con un solo tetramino
 * 
 * @return punteggio risultante
 */
int calcPoints(int num);

/**
 * Rimuove tutti i caratteri presenti nel buffer dell'stdin
 */
void clearStdin();

/**
 * Riceve un input da tastiera e controlla la sua validita' rispetto ai limiti dati per parametro
 * lowBound incluso, highBound escluso
 * 
 * @param lowBound limite inferiore incluso
 * @param highBound limite superiore escluso
 * 
 * @return il valore ottenuto in input rispettando il limiti
 */
int getIntStdin(int lowBound, int highBound);

/**
 * Imposta il locale, il charset utilizzato, a UTF-8 per poter stampare i simboli speciali
 * Ritorna il vecchio locale per poterlo riutillzarlo
 * 
 * @return il locale precendente
 */
char *setupLocale();

/**
 * rimuove il locale, il charset utilizzato, reimpostando quello presente precedentemente
 * 
 * @param locale il locale precedentemente ottenuto da ristabilire
 */
void cleanupLocale(char *locale);