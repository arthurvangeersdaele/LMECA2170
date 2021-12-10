#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"

#ifndef SEGMENT_TREE_H_
#define SEGMENT_TREE_H_

typedef struct Treeseg {
	Segment *value;
	struct Treeseg *parent;
	struct Treeseg *left;
	struct Treeseg *right;

}Treeseg;

Treeseg *createSeg(Segment*);
bool insertSeg(Treeseg**, Point*, Segment*, Treeseg*, bool);
bool delSeg(Treeseg**, Segment*, Point*);

Treeseg* findSeg(Treeseg*, Segment*, Point*);

Treeseg* findRSeg(Treeseg*);
Treeseg* findLSeg(Treeseg*);
Segment* findRParent(Treeseg*);
Segment* findLParent(Treeseg*);
Segment* findRightNb(Treeseg*, Segment*, Point*);
Segment* findLeftNb(Treeseg*, Segment*, Point*);


void printtabsseg(int);
void printTreesegRec(Treeseg*, int);
void printTreeseg(Treeseg*);
#endif
