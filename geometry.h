#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Points
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
typedef struct Point{
	float x;
	float y;
	int value;
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


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
bool contains(Point*, Segment*);
#endif
