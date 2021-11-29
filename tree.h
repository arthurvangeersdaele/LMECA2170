#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"

#ifndef TREE_H_
#define TREE_H_

typedef struct Treenode {
	Point *value;
	struct Treenode *parent;
	struct Treenode *left;
	struct Treenode *right;

}Treenode;

Treenode *createNode(Point*);
bool checkTree(Treenode*);
bool insertPoint(Treenode**, Point*, Treenode*, bool);
bool findPoint(Treenode*, Point*);
void printtabs(int);
void printTreeRec(Treenode*, int);
void printTree(Treenode*);

#endif
