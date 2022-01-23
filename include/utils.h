#pragma once

#include <stdbool.h>

#include "constants.h"

/**
 * Calcola il numero di punti dati dalle righe eliminate insieme
 */
int calcPoints(int num);

/**
 * Rimuove tutti i caratteri presenti nel buffer dell'stdin
 */
void clearStdin();

/**
 * Riceve un input da tastiera e controlla la sua validita' rispetto ai limiti dati per parametro
 * lowBound incluso, highBound escluso
 */
int getIntStdin(int lowBound, int highBound);

/**
 * Imposta il locale, il charset utilizzato, a UTF-8 per poter stampare i simboli speciali
 * Ritorna il vecchio locale per poterlo riutillzarlo
 */
char *setupLocale();

/**
 * rimuove il locale, il charset utilizzato, reimpostando quello presente precedentemente
 */
void cleanupLocale(char *locale);