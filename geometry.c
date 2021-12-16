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
		result->value = s;
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
		result->queue = createListseg(s);
		result->length = 0;
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
		printf("\nWarning: segment is NULL\n");
		return false;
	}
	if(list != NULL){
		if(list->head != NULL){
			if(list->length == 1){
				list->queue = createListseg(list->queue->value);
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
		}
		else{
			// printf("\nWarning: HEAD of List is NULL\n");
			list->head = createListseg(s);
			list->queue = list->head;
			list->head->prev = list->queue;
			list->queue->next = list->head;
			list->length = 1;
			return true;
		}
	}
	else{
		return false;
	}
}

bool insertListQueue(List* list, Segment* s){
	if(s == NULL){
		printf("\nWarning: segment is NULL\n");
		return false;
	}
	if(list != NULL){
		if(list->queue != NULL){
			if(list->length == 1){
				list->queue = createListseg(s);
				list->head = createListseg(list->head->value);
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
		}
		else{
			// printf("\nWarning: QUEUE of List is NULL\n");
			list->queue = createListseg(s);
			list->head = list->queue;
			list->head->prev = list->queue;
			list->queue->next = list->head;
			list->length = 1;
			return false;
		}
	}
	else{
		return false;
	}
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DELETE A SEGMENT IN LIST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

bool delHead(List* list){
	if(list->length == 0){
		// printf("\nWarning: list is empty\n");
		return false;
	}
	if(list->length == 1){
		list->head = NULL;
		list->queue = NULL;
		list->length = 0;
		return true; 
	}
	else{
		list->head = list->head->prev;
		list->head->next = NULL;
		list->length -=1;
		return true;
	}
}

bool delQueue(List* list){
	if(list->length == 0){
		// printf("\nWarning: list is empty\n");
		return false;
	}
	if(list->length == 1){
		list->head = NULL;
		list->queue = NULL;
		list->length = 0;
		return true; 
	}
	else{
		list->queue = list->queue->next;
		list->queue->prev = NULL;
		list->length -=1;
		return true;
	}
}


bool delList(List* list, Segment* s){
	if(list->length == 1){
		list->head = NULL;
		list->queue = NULL;
		list->length = 0;
		return true; 
	}
	return delListRec(list, list->queue, s);
}

bool delListRec(List* list, Listseg* node, Segment* s){
	if(equalSegment(list->queue->value, s)){
		list->queue->next->prev = NULL;
		list->queue = list->queue->next;
		list->length-=1;
		return true;
	}
	else if(equalSegment(list->head->value, s)){
		list->head->prev->next= NULL;
		list->head = list->head->prev;
		list->length-=1;
		return true; 
	}
	else if(equalSegment(node->value, s)){
		node->prev->next = node->next; 
		node->next->prev = node->prev;
		list->length-=1;
		return true; 
	}
	else if(node->next != NULL){
		delListRec(list, node->next, s);
	}
	else{
		// printf("\nSegment is not in list\n");
		return false;
	}
}


List* concatenate(List* l1, List* l2, List* l3){
	return concatenate2(concatenate2(l1, l2), l3);
}

List* concatenate2(List* l1, List* l2){
	if(l1 != NULL && l1->head != NULL && l1->queue != NULL){
		if(l2 != NULL && l2->head != NULL && l2->queue != NULL){
			List* tmp = createVoidList();
			tmp->head = l1->head; 
			tmp->queue = l2->queue; 
			l1->queue->next = l2->head;
			l2->head->prev = l1->queue;
			free(l1); 
			free(l2); 
			return tmp;
		}
		else{ // l2 == NULL
			free(l2); 
			return l1;
		}
	}
	else{ // l1 == NULL
		free(l1);
		return l2;
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
		printf("\nList is empty\n");
	}
	else if(list->length == 1){
		printf("\n<QUEUE> :[]:[");
		printSeg2(list->queue->value);
		printf("]:[]: <head>\n");
	}
	else {
		printf("\n<QUEUE> :[]:[");
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
}



