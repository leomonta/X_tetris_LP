#pragma once

#include <stdbool.h>

#include "constants.h"


/**
 * Calcola il numero di punti per riga eliminate insieme
 */
int calcPoints(int num);

/**
 * Rimuove tutti i caratteri presenti nel buffer dell'stdin
 */
void clearStdin();

/**
 * Riceve un input da tastiera e controlla la sua validità rispetto ai bound dati per parametro
 * lowBound incluso, highBound escluso
 */
int getIntStdin(int lowBound, int highBound);

/**
 *  imposta il locale, praticamente il charset utilizzato, a utf-8 per poter disegnare i simboli speciali
 */
char* setupLocale();

/**
 *  rimuove il locale, praticamente il charset utilizzato, reimpostando quello presente precedentemente
 */
void cleanupLocale(char* locale);