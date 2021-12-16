#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "point.h"
#include "segment_list.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Points 2D
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Point *createPoint(float x, float y) {
	Point *result = malloc(sizeof(Point));
	if (result != NULL) {
		result->x = x;
		result->y = y;
		result->U = createVoidList();
	}
	return result;
}

bool equalPoint(Point *p1, Point *p2){ // return true if the two points are equal (do not look at the value, only the coordinates)
	if(p1 != NULL && p2 != NULL){
		return (p1->x == p2->x && p1->y == p2->y);
	}
	return false;
}

void printPoint(Point *p) {
	if (p != NULL){
		printf("Point = (%.2f, %.2f), v:%d\n", p->x, p->y, p->value);
	}else{
		printf("Point = NULL\n");
	}
}


