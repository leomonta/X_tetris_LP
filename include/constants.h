/**
 * @file
 * Dichiaro tutte le costanti necessarie nel programma come misure varie e tetramini
 * 
 * Rappresentazione dei tetramini come array
 * * ' _ ' indica uno spazio vuoto
 * * ' / ' indica a capo
 * * ' * ' indica fine del tetramino
 * 
 * Rappresento gia' i tetramini ruotati, cosi' non devo calcolarli al volo
 *
 * Vari simboli UTF-8 usati \n
 * 0x2550 ═ ║ ╒ ╓ ╔ ╕ ╖ ╗ ╘ ╙ ╚ ╛ ╜ ╝ ╞ ╟ \n
 * 0x2560 ╠ ╡ ╢ ╣ ╤ ╥ ╦ ╧ ╨ ╩ ╪ ╫ ╬ \n
 * 0x25a0 ■ □ ▢ ▣ ▤ ▥ ▦ ▧ ▨ ▩ ◰ ◱ ◲ ◳ \n
 * 0x2b10 ⬐ ⬑ ⬒ ⬓ ⬔ ⬕ ⬖ ⬗ ⬘ ⬙ ⬚   ⬝ ⬞ ⬟ \n
 */

#pragma once

#include <wchar.h>

#define SCREEN_WIDTH  10
#define SCREEN_HEIGHT 15
#define nullptr 0x0

/* Costanti per i tetramini */

/**
 * Tipi diversi di tetramini esistenti 
 */
#define NUM_TETRAMINOS 7

/**
 * Numero di tetramini disponibili nelle partite a giocatore singolo 
 */
#define INITIAL_TETRAMINOS 20

/**
 * Numero di tetramini disponibili nella partite multigiocatore 
 */
#define INITIAL_TETRAMINOS_2X INITIAL_TETRAMINOS * 2

/**
 * Indice a tetramino invalido 
 */
#define INVALID_TETRAMINO 0xff

/**
 * Quanta importanza ha l'altezza massima risultate da una mossa
 */
#define HIGH_WEIGHT 2

/**
 * Quanta importanza ha l'altezza minima risultate da una mossa
 */
#define LOW_WEIGHT 2

/**
 * Quanta importanza ha la quantita' di linee cancellate risultante da una mossa
 */
#define LINES_WEIGHT 10

/**
 * Quanta importanza ha la quantita' di buchi risultati da una mossa
 */
#define HOLES_WEIGHT -2

/**
 * Quanta importanza ha la differenza tra punto piu' e quello piu' basso risultate da una mossa
 */
#define DIFF_WEIGHT -1

/**
 * # # # # *
 * 
 * # /
 * # /
 * # /
 * # *
 */
const wchar_t tetr_I_0[5];

const wchar_t tetr_I_1[8];

/**
 * _ # /
 * # # # *
 * 
 * # /
 * # # / 
 * # *
 * 
 * # # # /
 * _ # *
 * 
 * _ # /
 * # # /
 * _ # *
 */
const wchar_t tetr_T_0[7];

const wchar_t tetr_T_1[7];

const wchar_t tetr_T_2[7];

const wchar_t tetr_T_3[9];

/**
 * # # /
 * # # *
 */
const wchar_t tetr_Q_0[6];

/**
 * # # # /
 * # *
 * 
 * # # /
 * _ # /
 * _ # *
 * 
 * _ _ # /
 * # # # *
 * 
 * # /
 * # /
 * # # *
 */
const wchar_t tetr_L_0[6];

const wchar_t tetr_L_1[9];

const wchar_t tetr_L_2[8];

const wchar_t tetr_L_3[9];

/**
 * # # # /
 * _ _ # *
 * 
 * _ # /
 * _ # /
 * # # *
 * 
 * # /
 * # # # *
 * 
 * # # /
 * # /
 * # *
 */
const wchar_t tetr_J_0[8];

const wchar_t tetr_J_1[9];

const wchar_t tetr_J_2[6];

const wchar_t tetr_J_3[7];

/**
 * # # /
 * _ # # *
 * 
 * _ # /
 * # # /
 * # *
 */
const wchar_t tetr_Z_0[7];

const wchar_t tetr_Z_1[8];

/**
 * _ # # /
 * # # *
 * 
 * # /
 * # # /
 * _ # *
 */
const wchar_t tetr_S_0[7];

const wchar_t tetr_S_1[8];

/**
 * "Raccolte" dei tetramini per accesso diretto
 * all Tetramino contiene tutti i tipi di tetramino in una songola rotazione
 * 
 * tetramino Rotations serve per ottenere la rotazione di un tetramino in modo diretto 
 */

const wchar_t *const allTetraminos[NUM_TETRAMINOS];

const wchar_t *const tetraminosRotation[4][NUM_TETRAMINOS];