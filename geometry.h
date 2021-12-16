#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "segment_list.h"


#ifndef GEOMETRY_H_
#define GEOMETRY_H_

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Points
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
typedef struct Point{S
	float x;
	float y;
	List* U;
	//Segment* segments;
} Point;

Point *createPoint(float, float);
bool equalPoint(Point*, Point*);
void printPoint(Point *p);


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
