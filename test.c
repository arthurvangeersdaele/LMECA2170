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
	
	/*
	Treenode *tree;
	Point* p = createPoint(5.0, 0.0, 5);
	Treenode* node = createNode(p);
	insertPoint(&tree, p, node);
	
	free(node);
	free(p);
	printTree(tree);
	free(tree);
	*/
	
	
	int length = 9;
	//liste = (int*)malloc(sizeof(int)*1);
	int liste[] = {5, 2, 8, 1, 3, 6, 10, 7, 9};
	Treenode *tree = NULL;
	Point* p;
	for(int i = 0; i<length; i++){
		p = createPoint(liste[i], 0, liste[i]);
		insertPoint(&tree, p, tree, false);
	}
	checkTree(tree);
	printTree(tree);
	free(tree);
	free(p);
	
	
}

