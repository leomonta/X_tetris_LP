/**
 * @file
 * Raccolte di funzioni specializzate a disegnare tetramini ed a gestire lo schermo
 */
#pragma once

#include "constants.h"

/**
 * Stampa i tetramini disponibili rimanenti in righe da 10
 * 
 * @param runtimeTetraminos lista dei tetraini da stampare
 * @param size lunghezza della lista dei tetramini
 */
void drawRemainingTetraminos(unsigned char *runtimeTetraminos, unsigned int size);

/**
 * Stampa a schermo i tetramini alla posizione corretta con una cornice
 * 
 * @param screen matrice 15 * 10 che rappresenta il campo di gioco da stampare
 */
void drawScreen(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Stampo lo schermo di entrambi i giocatori uno di fianco all'altro
 * 
 * @param screenG1 matrice 15 * 10 del giocatore 1 da disegnare a sinistra
 * @param screenG2 matrice 15 * 10 del giocatore 2 da disegnare a desta
 */
void multiDrawScreen(wchar_t screenG1[SCREEN_HEIGHT][SCREEN_WIDTH], wchar_t screenG2[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Pulisce la matrice dello schermo mettendo tutti caratteri vuoti 
 * 
 * @param screen matrice 15 * 10 da riempire con caratteri vuoti
 */
void clearScreen(wchar_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

/**
 * Stampa un singolo tetramino da mostrare all'utente per conferma
 * 
 * @param numTetramino indice rispetto ad allTetraminos che indica il tetramino da disegnare
 * @param rotation numero di rotazioni di 90° in senso orario da effetture
 */
void drawSingleTetramino(int numTetramino, int rotation);