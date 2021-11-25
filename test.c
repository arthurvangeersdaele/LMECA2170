#include <tree.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main() {
	Point* p;

	int N = 100;
	srand((int)time(NULL));
	int MAX = 100000;
	int MIN = 0;
	for (int i = 0; i < N; i++) {
		*(p + 1) = createPoint((rand() % (MAX - MIN + 1) + MIN), (rand() % (MAX - MIN + 1) + MIN), i);
	}
}

