#ifndef POINT_H_
#define POINT_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "segment_list.h"



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Points
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
typedef struct Point{
	float x;
	float y;
	List* U;
	//Segment* segments;
} Point;

Point *createPoint(float, float);
bool equalPoint(Point*, Point*);
void printPoint(Point *p);

#endif
