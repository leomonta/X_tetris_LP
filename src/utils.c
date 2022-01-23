#include <locale.h>
#include <math.h>
#include <stdio.h>

#include "utils.h"

int calcPoints(int num) {
	/* 2^(righe eliminate - 1) * 1.5f arrotondato per difetto */
	return (int)(pow(2, num - 1) * 1.5);
}

void clearStdin() {
	int c;
	/* leggo caratteri fino a che non trovo un \n o un fine File EOF */
	while ((c = getchar()) != '\n' && c != EOF) {
	}
}

int getIntStdin(int lowBound, int highBound) {
	int retVal;
	int inputTetr;

	while (1) {

		printf("numero -> ");
		/**
		 * scanf ritorna il numero di parametri correttamente assegnati alle variabili date
		 * uso questo numero per controllare che l'operazione di input sia stata effettuata correttamente
		 */
		retVal = scanf("%d", &inputTetr);

		/* Rimuovo eventuali caratteri rimasti */
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