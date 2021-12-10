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

bool equalPoint(Point *p1, Point *p2){
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
/*Segment createSegment(Point *p0, Point *p1, int value) {
	Segment *result = malloc(sizeof(Segment));
	if (result != NULL) {
		result->p0 = p0;
		result->p1 = p1;
		result->value = value;
	}
	return *result;
}*/

Segment *createSegment(Point *p0, Point *p1, int value) {
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
	return s;
}

bool equalSegment(Segment* s0, Segment* s1){
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


bool contains(Point* p, Segment* s){
	float m;
	float oao;
	if(s != NULL){
		if(s->p0->x != s->p1->x){ // pas vertical
			m = (s->p0->y - s->p1->y)/(s->p0->x - s->p1->x);
			oao = s->p0->y - m * s->p0->x;
			return p->y == m*p->x + oao && p->y > s->p0->y && p->y < s->p1->y;
		}
		else{
			return p->x == s->p0->x && p->y > s->p0->y && p->y < s->p1->y;
		}

	}
	return false;
}
