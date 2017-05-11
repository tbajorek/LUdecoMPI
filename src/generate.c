#include <stdio.h>
#include <time.h>
#include "matrix.h"

int main() {
	int rows = 400;
	int cols = 1;
	int r, c;
	int value;
	matrix* m = createMatrix(rows, cols);
	srand(time(NULL));
	for(r =  1; r <= rows; ++r) {
		for(c = 1; c <= cols; ++c) {
			value = rand() % 100;
			setMatValue(m, r, c, value);
		}
	}
	writeToFile("input.txt", m);
	freeMatrix(m);
	return 0;
}
