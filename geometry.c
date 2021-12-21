#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"


bool feq(double x, double y){
    return (y<x+tol && y>x-tol);
}

bool fgreater(double x, double y){
    return (x > y-tol);
}
bool flower(double x, double y){
    return (x < y-tol);
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Points 2D
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Point *createPoint(double x, double y, List *U) {
	Point *result = malloc(sizeof(Point));
	if (result != NULL) {
		result->x = x;
		result->y = y;
        result->U = createVoidList();
        if (U != NULL){
            insertList(result->U, U->head);
        }
	}
	return result;
}

bool equalPoint(Point *p1, Point *p2){ // return true if the two points are equal (do not look at the value, only the coordinates)
	if(p1 != NULL && p2 != NULL){
		return (p1->x == p2->x && p1->y == p2->y);
	}
	return false;
}

bool equalPointTOL(Point *p1, Point *p2){ // return true if the two points are equal (do not look at the value, only the coordinates)
    if(p1 != NULL && p2 != NULL){
        return (feq(p1->x, p2->x) && feq(p1->y, p2->y));
    }
    return false;
}

void freePoint(Point* p){
    if(p != NULL){
        freeList(p->U);
        free(p);
    }
}

void printPoint(Point *p) {
	if (p != NULL){
		printf("Point = (%.2f, %.2f)  ", p->x, p->y);
        printList(p->U);
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
		if (p0->y < p1->y || (p0->y == p1->y && p0->x < p1->x)) {
			s->p0 = createPoint(p0->x, p0->y, p0->U);
			s->p1 = createPoint(p1->x, p1->y, p1->U);
		}
		else{
			s->p0 = createPoint(p1->x, p1->y, p1->U);
			s->p1 = createPoint(p0->x, p0->y, p0->U);
		}
		s->value = value;
	}
	return s;
}

bool equalSegment(Segment* s0, Segment* s1){ // return true if the two segments are equal (do not look at the value, only the coordinates of the two points of the segments)
	if (s0 != NULL && s1 != NULL){
        return (s0->value == s1->value || (equalPoint(s0->p0, s1->p0) && equalPoint(s0->p1, s1->p1)));
    }
    return false;
}


void freeSeg(Segment* s){
    if (s != NULL) {
        freePoint(s->p0);
        freePoint(s->p1);
        free(s);
    }
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
	double m; // slope of the segment
	double oao; // (imaginary) crossing of the segment with the y-axis
	if(s != NULL){
		if(s->p0->x != s->p1->x){ // s not vertical
			m = (s->p0->y - s->p1->y)/(s->p0->x - s->p1->x);
			oao = s->p0->y - m * s->p0->x;
			// check if p is on the line y=mx+p and if it is between the two extremities of the segment
			return feq(p->y, m*p->x + oao) && p->y > s->p0->y && p->y < s->p1->y;
		}
		else{ // s is vertical: check if p is on the line with x-coordinates and between the segment extremities with y coordinates
			return feq(p->x, s->p0->x) && p->y > s->p0->y && p->y < s->p1->y;
		}

	}
	return false;
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Segments LIST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% CREATE A LIST NODE 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Listseg *createListseg(Segment* s){
	Listseg* result = malloc(sizeof(Listseg));
	if (result != NULL) {
		result->prev = NULL;
		result->next = NULL;
		result->value = createSegment(s->p0, s->p1, s->value);
	}
	return result;
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% CREATE A LIST STRUCTURE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

List *createList(Segment* s){
	List* result = malloc(sizeof(List));
	if (result != NULL) {
		result->head = createListseg(s);
		//result->queue = createListseg(s);
		result->length = 1;
	}
	return result;
}
List *createVoidList(){
	List* result = malloc(sizeof(List));
	if (result != NULL) {
		result->head = NULL;
		result->queue = NULL;
		result->length = 0;
	}
	return result;
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% ADD A SEGMENT IN LIST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

bool insertListHead(List* list, Segment* s){
	if(s == NULL){
		//printf("\nWarning: segment is NULL\n");
		return false;
	}
	if(list != NULL){
		if(list->head != NULL){
			if(list->length == 1){
                list->queue = list->head;
				list->head = createListseg(s);
				list->queue->next = list->head;
				list->head->prev = list->queue; 
				list->length += 1;
			}
			else{
				list->head->next = createListseg(s);
				list->head->next->prev = list->head;
				list->head = list->head->next;
				list->length+=1;
			}
            return true;
		}
		else{
            list->head = createListseg(s);
			list->length = 1;
			return true;
		}
	}
    return false;
}

bool insertListQueue(List* list, Segment* s){
	if(s == NULL){
		printf("\nWarning: segment is NULL\n");
		return false;
	}
	if(list != NULL){
		if(list->queue != NULL){
			if(list->length == 1){
                list->head = list->queue;
				list->queue = createListseg(s);
				list->queue->next = list->head;
				list->head->prev = list->queue; 
				list->length += 1;
			}
			else{
				list->queue->prev = createListseg(s);
				list->queue->prev->next = list->queue;
				list->queue = list->queue->prev;
				list->length+=1;
			}
            return true;
		}
		else{
			list->queue = createListseg(s);
			list->length = 1;
			return true;
		}
	}
	return false;
}


bool insertList(List* l1, Listseg* l2){//length l2 must be >1
    if (l2 != NULL){
        insertListHead(l1, l2->value);
        return insertList(l1, l2->prev);
    }
    return false;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DELETE A SEGMENT IN LIST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

bool delHead(List* list){
	if(list->length == 0){
		return false;
	}
	if(list->length == 1){
        //list->head = NULL;
        //list->queue = NULL;
        //list->length = 0;
        freeList(list);
		return true; 
	}
	else{
        freeSeg(list->head->value);
        free(list->head);
		list->head = list->head->prev;
		list->head->next = NULL;
		list->length -=1;
		return true;
	}
}

List* concatenate(List* l1, List* l2, List* l3){
    List* tmp = concatenate2(l1, l2);
    List* final = concatenate2(tmp, l3);
    freeList(tmp);
	return final;
}

List* concatenate2(List* l1, List* l2){
    List* tmp = createVoidList();
	if(l1 != NULL){
        *tmp = *l1;
		if(l2 != NULL){

            if (l2->length == 1 && l2->queue != NULL){
                insertListQueue(tmp, l2->queue->value);
            }else if(l2->length==1 && l2->head != NULL){
                insertListQueue(tmp, l2->head->value);
            }else{
                insertList(tmp, l2->head);
            }
		}
	}
	else{ // l1 == NULL
        *tmp = *l2;
	}
    return tmp;
}


void freeListSeg(Listseg* LS){
    if (LS == NULL){
        return;
    }
    Listseg *tmp = LS->prev;
    freeSeg(LS->value);
    free(LS);
    while (tmp != NULL){
        Listseg *tmp2 = tmp->prev;
        freeSeg(tmp->value);
        free(tmp);
        tmp = tmp2;
    }
}

void freeList(List* L){
    if (L != NULL) {
        freeListSeg(L->head);
        //freeListSeg(L->queue);
        free(L);
    }
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% PRINT LIST FUNCTIONS 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void printList(List* list){
	if(list == NULL){
		printf("\nList is NULL\n");
		return;
	}
	else if(list->length == 0){
		printf("List is empty: length=%d\n", list->length);
	}
	else if(list->length == 1){
		printf("length=%d, <QUEUE> :[]:[", list->length);
        if (list->queue!=NULL){
            printSeg2(list->queue->value);
        }else{
            printSeg2(list->head->value);
        }
		printf("]:[]: <head>\n");
	}
	else {
		printf("length=%d, <QUEUE> :[]:[", list->length);
		printListRec(list->queue);
	}
}

void printListRec(Listseg* node){
	if(node != NULL){
		printSeg2(node->value);
		printf("]:[");
		printListRec(node->next);
	}
	else{
		printf("]: <HEAD>\n\n");
	}
}
/*
void printListLight(List* list){
	if(list == NULL){
		printf("\nObject List is NULL\n");
		return;
	}
	else if(list->length == 0){
		printf("\n[0] <Q><H> (empty)\n");
	}
	else if(list->length == 1){
		printf("\n[1] <Q> ");
		printf("%d", list->queue->value->value);
		printf(" <H>\n");
	}
	else {
		printf("\n[%d] <Q> ", list->length);
		printListLightRec(list->queue);
	}
}

void printListLightRec(Listseg* node){
	if(node != NULL){
		printf("%d", node->value->value);
		printf(" - ");
		printListLightRec(node->next);
	}
	else{
		printf("<H>\n");
	}
}*/



