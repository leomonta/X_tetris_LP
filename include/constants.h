#pragma once

#include <wchar.h>

#define SCREEN_WIDTH  10
#define SCREEN_HEIGHT 15
#define nullptr 0x0

#define NUM_TETRAMINOS     7
#define INITIAL_TETRAMINOS 20
#define INVALID_TETRAMINO  0xff

/**
 * 0x2550 -> 0x256C
 * 0x2550 ═ ║ ╒ ╓ ╔ ╕ ╖ ╗ ╘ ╙ ╚ ╛ ╜ ╝ ╞ ╟ 
 * 0x2560 ╠ ╡ ╢ ╣ ╤ ╥ ╦ ╧ ╨ ╩ ╪ ╫ ╬ 
 * 0x25a0 ■ □ ▢ ▣ ▤ ▥ ▦ ▧ ▨ ▩ 
 * ◰ ◱ ◲ ◳
 * 0x2b10 ⬐ ⬑ ⬒ ⬓ ⬔ ⬕ ⬖ ⬗ ⬘ ⬙ ⬚ ⬛ ⬜ ⬝ ⬞ ⬟
 */

/**
 * # # # # *
 * 
 * # /
 * # /
 * # /
 * # *
 */
const wchar_t tetr_I_0[5] = {L'▣', L'▣', L'▣', L'▣', L'*'};

const wchar_t tetr_I_1[8] = {L'▣', L'/',
							 L'▣', L'/',
							 L'▣', L'/',
							 L'▣', L'*'};

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
const wchar_t tetr_T_0[7] = {L'_', L'■', L'/',
							 L'■', L'■', L'■', L'*'};

const wchar_t tetr_T_1[7] = {L'■', L'/',
							 L'■', L'■', L'/',
							 L'■', L'*'};

const wchar_t tetr_T_2[7] = {L'■', L'■', L'■', L'/',
							 L'_', L'■', L'*'};

const wchar_t tetr_T_3[9] = {L'_', L'■', L'/',
							 L'■', L'■', L'/',
							 L'_', L'■', L'*'};

/**
 * # # /
 * # # *
 */
const wchar_t tetr_Q_0[6] = {L'◲', L'◱', L'/',
							 L'◳', L'◰', L'*'};

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
const wchar_t tetr_L_0[6] = {L'□', L'□', L'□', L'/',
							 L'□', L'*'};

const wchar_t tetr_L_1[9] = {L'□', L'□', L'/',
							 L'_', L'□', L'/',
							 L'_', L'□', L'*'};

const wchar_t tetr_L_2[8] = {L'_', L'_', L'□', L'/',
							 L'□', L'□', L'□', L'*'};

const wchar_t tetr_L_3[9] = {L'_', L'□', L'/',
							 L'_', L'□', L'/',
							 L'□', L'□', L'*'};

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
const wchar_t tetr_J_0[8] = {L'⬚', L'⬚', L'⬚', L'/',
							 L'_', L'_', L'⬚', L'*'};

const wchar_t tetr_J_1[9] = {L'_', L'⬚', L'/',
							 L'_', L'⬚', L'/',
							 L'⬚', L'⬚', L'*'};

const wchar_t tetr_J_2[6] = {L'⬚', L'/',
							 L'⬚', L'⬚', L'⬚', L'*'};

const wchar_t tetr_J_3[7] = {L'⬚', L'⬚', L'/',
							 L'⬚', L'/',
							 L'⬚', L'*'};

/**
 * # # /
 * _ # # *
 * 
 * _ # /
 * # # /
 * # *
 */
const wchar_t tetr_Z_0[7] = {L'▢', L'▢', L'/',
							 L'_', L'▢', L'▢', L'*'};

const wchar_t tetr_Z_1[8] = {L'_', L'▢', L'/',
							 L'▢', L'▢', L'/',
							 L'▢', L'*'};

/**
 * _ # # /
 * # # *
 * 
 * # /
 * # # /
 * _ # *
 */
const wchar_t tetr_S_0[7] = {L'_', L'▧', L'▧', L'/',
							 L'▧', L'▧', L'*'};

const wchar_t tetr_S_1[8] = {L'▧', L'/',
							 L'▧', L'▧', L'/',
							 L'_', L'▧', L'*'};

const wchar_t *const allTetraminos[NUM_TETRAMINOS] = {tetr_I_0, tetr_L_0, tetr_J_0, tetr_Q_0, tetr_Z_0, tetr_S_0, tetr_T_0};

const wchar_t *const tetraminosRotation[4][NUM_TETRAMINOS] = {{tetr_I_0, tetr_L_0, tetr_J_0, tetr_Q_0, tetr_Z_0, tetr_S_0, tetr_T_0},
															  {tetr_I_1, tetr_L_1, tetr_J_1, tetr_Q_0, tetr_Z_1, tetr_S_1, tetr_T_1},
															  {tetr_I_0, tetr_L_2, tetr_J_2, tetr_Q_0, tetr_Z_0, tetr_S_0, tetr_T_2},
															  {tetr_I_1, tetr_L_3, tetr_J_3, tetr_Q_0, tetr_Z_1, tetr_S_1, tetr_T_3}};