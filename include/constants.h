#pragma once

#include <wchar.h>

#define SCREEN_WIDTH  10
#define SCREEN_HEIGHT 15
#define nullptr 0x0

#define NUM_TETRAMINOS     7
#define INITIAL_TETRAMINOS 20
#define INITIAL_TETRAMINOS_2X INITIAL_TETRAMINOS * 2
#define INVALID_TETRAMINO  0xff

/**
 * 0x2550 -> 0x256C
 * 0x2550 ═ ║ ╒ ╓ ╔ ╕ ╖ ╗ ╘ ╙ ╚ ╛ ╜ ╝ ╞ ╟ 
 * 0x2560 ╠ ╡ ╢ ╣ ╤ ╥ ╦ ╧ ╨ ╩ ╪ ╫ ╬ 
 * 0x25a0 ■ □ ▢ ▣ ▤ ▥ ▦ ▧ ▨ ▩ 
 * ◰ ◱ ◲ ◳
 * 0x2b10 ⬐ ⬑ ⬒ ⬓ ⬔ ⬕ ⬖ ⬗ ⬘ ⬙ ⬚   ⬝ ⬞ ⬟
 */

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

const wchar_t *const allTetraminos[NUM_TETRAMINOS];

const wchar_t *const tetraminosRotation[4][NUM_TETRAMINOS];