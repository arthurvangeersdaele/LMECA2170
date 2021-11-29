#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"

#ifndef TREE_H_
#define TREE_H_

typedef struct Treenode {
	struct Point *value;
	struct Treenode *left;
	struct Treenode *right;

}Treenode;

Treenode *createNode(Point*);
bool insertPoint(Treenode**, Point*);
bool findPoint(Treenode*, Point*);
void printtabs(int);
void printTreeRec(Treenode*, int);
void printTree(Treenode*);

#endif