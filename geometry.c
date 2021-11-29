#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Points 2D
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Point *createPoint(float x, float y, int value) {
	Point *result = malloc(sizeof(Point));
	if (result != NULL) {
		result->x = x;
		result->y = y;
		result->value = value;
	}
	return result;
}

void printPoint(Point *p) {
	printf("Point = (%f, %f), value = %d\n", p->x, p->y, p->value);
}
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Segments
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*Segment createSegment(Point *p0, Point *p1, int value) {
	Segment *result = malloc(sizeof(Segment));
	if (result != NULL) {
		result->p0 = p0;
		result->p1 = p1;
		result->value = value;
	}
	return *result;
}*/

Segment createSegment(Point *p0, Point *p1, int value) {
	Segment *s = malloc(sizeof(Segment));
	if (s != NULL) {
		if (p0->y < p1->y) {
			s->p0 = p0;
			s->p1= p1;
		}
		else if (p0->y == p1->y && p0->x < p1->x) {
			s->p0 = p0;
			s->p1 = p1;
		}
		else if (p0->y > p1->y) {
			s->p0 = p1;
			s->p1 = p0;
		}
		s->value = value;
	}
	return *s;
}

/*Segment checkSegment(Segment *s, int value) {
	Segment* result = malloc(sizeof(Segment));
	if (result != NULL) {
		if (s->p0->y < s->p1->y) {
			result->p0 = s->p0;
			result->p1= s->p1;
		}
		else if (s->p0->y == s->p1->y && s->p0->x < s->p1->x) {
			result->p0 = s->p0;
			result->p1 = s->p1;
		}
		else if (s->p0->y > s->p1->y) {
			result->p0 = s->p1;
			result->p1 = s->p0;
		}
		result->value = value;
		*s = *result; 
		free(result);
	}
	return *s;
}*/
