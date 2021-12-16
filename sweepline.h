#ifndef SWEEPLINE_H_
#define SWEEPLINE_H_

//#include "BOV.h"
//#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "point.h"
#include "segment.h"
#include "point_tree.h"
#include "segment_tree.h"
#include "segment_list.h"
#include "point_list.h"


//void delForC(Treeseg*, List*, Point*);
void insertForC(Treeseg*, List*, Point*);
void insertForU(Treeseg*, List*, Point*);

void findNewEvent(Segment*, Segment*, Point*, Treenode*);

void HandleEventPoint(Point*, Point*, Point*);

listP* FindIntersections(Segment*);

#endif
