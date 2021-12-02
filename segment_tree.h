#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"

#ifndef SEGMENT_TREE_H_
#define SEGMENT_TREE_H_

typedef struct Treeseg {
	Segment *value;
	struct Treenode *parent;
	struct Treenode *left;
	struct Treenode *right;

}Treeseg;

Treeseg *createSeg(Segment*);
bool checkTree2(Treeseg*);
bool insertSeg(Treeseg**, Segment*, Treeseg*, bool, bool);
bool findSeg(Treeseg*, Segment*);
Treeseg* delSeg(Treeseg*, Treeseg*);


#endif