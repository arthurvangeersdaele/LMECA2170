#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Points 2D
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Point *createPoint(float x, float y) {
	Point *result = malloc(sizeof(Point));
	if (result != NULL) {
		result->x = x;
		result->y = y;
		result->value = 0;
		//result->segment= NULL;
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

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Segments
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Segment *createSegment(Point *p0, Point *p1, int value) { // Segments are such that P0 is the upper point of the segment and P1 is the lower point
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
		else{
			s->p0 = p1;
			s->p1 = p0;
		}
		s->value = value;
	}
	return s;
}

bool equalSegment(Segment* s0, Segment* s1){ // return true if the two segments are equal (do not look at the value, only the coordinates of the two points of the segments)
	return(equalPoint(s0->p1, s1->p1) && equalPoint(s0->p0, s1->p0));
}

void printSeg(Segment *s) {
	if (s!=NULL){
		printf("Seg = (%.2f,%.2f)->(%.2f,%.2f), v:%d\n", s->p0->x, s->p0->y, s->p1->x, s->p1->y, s->value);
	}
	else{
		printf("Seg = NULL\n");
	}
}

void printSeg2(Segment *s) {
	if (s!=NULL){
		printf("Seg = (%.2f,%.2f)->(%.2f,%.2f), v:%d", s->p0->x, s->p0->y, s->p1->x, s->p1->y, s->value);
	}
	else{
		printf("Seg = NULL");
	}
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
bool contains(Point* p, Segment* s){ // return true if the segment s contains the point p ON ITS INTERIOR
	float m; // slope of the segment
	float oao; // (imaginary) crossing of the segment with the y-axis
	if(s != NULL){
		if(s->p0->x != s->p1->x){ // s not vertical
			m = (s->p0->y - s->p1->y)/(s->p0->x - s->p1->x);
			oao = s->p0->y - m * s->p0->x;
			// check if p is on the line y=mx+p and if it is between the two extremities of the segment
			return p->y == m*p->x + oao && p->y > s->p0->y && p->y < s->p1->y;
		}
		else{ // s is vertical: check if p is on the line with x-coordinates and between the segment extremities with y coordinates
			return p->x == s->p0->x && p->y > s->p0->y && p->y < s->p1->y;
		}

	}
	return false;
}
