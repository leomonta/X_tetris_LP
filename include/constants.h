#pragma once

#define SCREENWIDTH	 10
#define SCREENHEIGHT 15
#define nullptr 0x0

#define NUM_TETRAMINOS	   7
#define INITIAL_TETRAMINOS 20
#define INVALID_TETRAMINO 0xff

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
 */
const wchar_t tetr_I[5] = {L'▣', L'▣', L'▣', L'▣', L'*'};

/**
 * _ # _ /
 * # # # *
 */
const wchar_t tetr_T[8] = {L'_', L'■', L'_', L'/',
						   L'■', L'■', L'■', L'*'};

/**
 * # # /
 * # # *
 */
const wchar_t tetr_Q[6] = {L'◲', L'◱', L'/',
						   L'◳', L'◰', L'*'};

/**
 * # # # /
 * # _ _ *
 */
const wchar_t tetr_L[8] = {L'□', L'□', L'□', L'/',
						   L'□', L'_', L'_', L'*'};

/**
 * # # # /
 * _ _ # *
 */
const wchar_t tetr_J[8] = {L'⬚', L'⬚', L'⬚', L'/',
						   L'_', L'_', L'⬚', L'*'};

/**
 * # # _ /
 * _ # # *
 */
const wchar_t tetr_Z[8] = {L'▢', L'▢', L'_', L'/',
						   L'_', L'▢', L'▢', L'*'};

/**
 * _ # # /
 * # # _ *
 */
const wchar_t tetr_S[8] = {L'_', L'▧', L'▧', L'/',
						   L'▧', L'▧', L'_', L'*'};

const wchar_t *const allTetraminos[NUM_TETRAMINOS] = {tetr_I, tetr_L, tetr_J, tetr_Q, tetr_Z, tetr_S, tetr_T};
