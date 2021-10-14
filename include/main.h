#pragma once

#include "constants.h"

struct IVec2 {
	char x, y;
};

/* Indico con '#' il quadrato pieno e con '_' il quadrato vuoto
  ogni tetramino e' nel proprio array, ma per la larghezza di un tetramino uso '/' per indicare un "a capo"
  inoltre uso il carattere '*' per indicare la fine 
*/

/*
# # # # *
*/
char tetr_I[5] = {'#', '#', '#', '#', '*'};

/*
# _ /
# # /
# _ * 
*/ 
char tetr_T[9] = {'#', '_', '/',
				  '#', '#', '/',
				  '#', '_', '*'};

/*	
# # /
# # *
*/
char tetr_Q[6] = {'#', '#', '/',
				  '#', '#', '*'};

/*
# # # /
# _ _ *
*/
char tetr_L[8] = {'#', '#', '#', '/',
				  '#', '_', '_', '*'};

/* 
# # _ /
_ # # *
*/
char tetr_S[8] = {'#', '#', '_', '/',
				  '_', '#', '#', '*'};

char screen[screenWidth][screenHeight];

void setup();
void drawScreen();
void insert(char *tetramino, struct IVec2 pos);
/* Ritorna 1 se pos risiede nei limiti dello schermo*/
int checkBounds(struct IVec2 pos);