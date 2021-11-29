#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
//#include "test.h"
#include "tree.h"
#include "geometry.h"

int main() {
	/*Point p;
	printf("Hello World\n");
	p = createPoint(1, 10, 1);
	Treenode* n1 = createNode(&p);
	Point p2 = createPoint(1, 1, 2);
	insertPoint(&n1, &p2, n1);
	printTree(n1);*/
	int* liste;
	liste = (int*)malloc(sizeof(int)*1);
	printf("ici 0");
	liste[0] = 1;//{5, 2, 7, 1, 3, 6, 9, 7, 8};
	printf("ici 1");
	Treenode *tree = createNode(NULL);
	printf("ici 2");
	for(int i = 0; i<sizeof(liste); i++){
		printf("ici 3");
		Point *p = malloc(sizeof(Point));
		printf("ici 4");
		*p = createPoint(liste[i], 0, liste[i]);
		printf("ici 5");
		Treenode* node = createNode(p);
		//insertPoint(&tree, p, node);
		free(p);
		free(node);
	}
	checkTree(tree);
	printTree(tree);
	free(tree);

}

