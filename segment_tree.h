#ifndef SEGMENT_TREE_H_
#define SEGMENT_TREE_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"


typedef struct Treeseg {
	Segment *value;
	struct Treeseg *parent;
	struct Treeseg *left;
	struct Treeseg *right;

}Treeseg;

Treeseg *createSeg(Segment*);
bool insertSeg(Treeseg**, Point*, Segment*, Treeseg*);
bool delSeg(Treeseg**, Segment*, Point*);

//Treeseg* findSeg(Treeseg*, Segment*, Point*);
Treeseg* findSegBEFOREUPDATE(Treeseg*, Segment*, Point*);

Treeseg* findRSeg(Treeseg*);
Treeseg* findLSeg(Treeseg*);
Treeseg* findRParent(Treeseg*);
Treeseg* findLParent(Treeseg*);
Treeseg* findRightNb(Treeseg*, Segment*, Point*, bool);
Treeseg* findLeftNb(Treeseg*, Segment*, Point*, bool);

bool findLandC(Treeseg*, Treeseg*, Point*, bool, List*, List*, List*);
Segment* findLeftMost(Treeseg*, Treeseg*, Point*, bool);
Segment* findRightMost(Treeseg*, Treeseg*, Point*, bool);

void printtabsseg(int);
void printTreesegRec(Treeseg*, int);
void printTreeseg(Treeseg*);
#endif
