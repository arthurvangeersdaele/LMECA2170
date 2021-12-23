#ifndef POINT_TREE_H_
#define POINT_TREE_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "geometry.h"


typedef struct Treenode {
	Point *value;
	struct Treenode *parent;
	struct Treenode *left;
	struct Treenode *right;

}Treenode;

Treenode *createNode(Point*);
bool insertPoint(Treenode**, Point*, Treenode*, Segment*, bool);
bool findPoint(Treenode*, Point*);
Point* delPoint(Treenode**);

void freeTreenode(Treenode*);

void printtabs(int);
void printTreeRec(Treenode*, int);
void printTree(Treenode*);

#endif
