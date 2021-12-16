#include "BOV.h"
#include <math.h>
#include "geometry.h"
#include "point_tree.h"
#include "segment_tree.h"
#include "segment_list.h"
#include "point_list.h"

#ifndef SWEEPLINE_H_
#define SWEEPLINE_H_

//void delForC(Treeseg*, List*, Point*);
void insertForC(Treeseg*, List*, Point*);
void insertForU(Treeseg*, List*, Point*);

void findNewEvent(Segment*, Segment*, Point*, Treenode*);

void HandleEventPoint(Point*, Point*, Point*);

listP* FindIntersections(Segment*);

#endif
