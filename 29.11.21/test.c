#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
//#include "test.h"
#include "tree.h"
#include "geometry.h"

int main() {
	Point p;
	printf("Hello World\n");
	p = createPoint(10, 10, 1);
	Treenode* n1 = createNode(&p);
	Point p2 = createPoint(1, 1, 2);
	insertPoint(&n1, &p2, n1);
	printTree(n1);

}

