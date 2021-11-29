#include "BOV.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Point{
	float x = 0.0;
	float y = 0.0;
} Point;

typedef struct Segment {
	struct Point p0;
	struct Point p1;
} Segment;


typedef struct Treenode {
	int value; 
	struct Treenode *left;
	struct Treenode *right;

}Treenode;

Treenode createNode(Point p) {
	Treenode* result = malloc(sizeof(Treenode));
	if (result != NULL) {
		result->left = NULL;
		result->right = NULL;
		result->value = p;
	}
	return result;
}



