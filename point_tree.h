#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"

#ifndef POINT_TREE_H_
#define POINT_TREE_H_

typedef struct Treenode {
	Point *value;
	struct Treenode *parent;
	struct Treenode *left;
	struct Treenode *right;

}Treenode;

Treenode *createNode(Point*);
// bool checkTree(Treenode*);
bool insertPoint(Treenode**, Point*, Treenode*, bool, bool);
bool findPoint(Treenode*, Point*);
Point* delPoint(Treenode**);


void printtabs(int);
void printTreeRec(Treenode*, int);
void printTree(Treenode*);

#endif
