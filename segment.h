#ifndef SEGMENT_H_
#define SEGMENT_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "point.h"


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Segments
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

typedef struct Segment{
	struct Point* p0;
	struct Point* p1;
	int value;
} Segment;

Segment *createSegment(Point*, Point*, int);
Segment checkSegment(Segment*, int);
bool equalSegment(Segment*, Segment*);
void printSeg(Segment *s);
void printSeg2(Segment *s);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% POINTS & SEGMENTS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
bool contains(Point*, Segment*);

#endif
