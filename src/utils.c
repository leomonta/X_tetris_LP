#include <locale.h>
#include <math.h>
#include <stdio.h>

#include "utils.h"

int calcPoints(int num) {
	/*2^(righe eliminate - 1) * 1.5f arrotondato per difetto*/
	return (int)(pow(2, num - 1) * 1.5);
}

void clearStdin() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {
	}
}

int getIntStdin(int lowBound, int highBound) {
	int retVal;
	int inputTetr;

	while (1) {

		printf("numero -> ");
		retVal = scanf("%d", &inputTetr);

		clearStdin();

		if (retVal == 1 && inputTetr >= lowBound && inputTetr < highBound) {
			break;
		}

		printf("Devi inserire un valore tra 0 e %d\n", highBound - 1);
	}

	return inputTetr;
}

char* setupLocale() {

	char* old_locale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "C.UTF-8");

	return old_locale;
}

void cleanupLocale(char* locale) {

	setlocale(LC_ALL, locale);
}