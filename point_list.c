#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "point.h"
#include "segment_list.h"
#include "point_list.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% CREATE A LIST NODE 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Listpoint *createListpoint(Point* p){
	Listpoint* result = malloc(sizeof(Listpoint));
	if (result != NULL) {
		result->prev = NULL;
		result->next = NULL;
		result->value = p;
		result->luc = NULL; 
	}
	return result;
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% CREATE A LIST STRUCTURE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

ListP *createListP(Point* p){
	ListP* result = malloc(sizeof(ListP));
	if (result != NULL) {
		result->head = createListpoint(p);
		result->queue = createListpoint(p);
		result->length = 0;
	}
	return result;
}
ListP *createVoidListP(){
	ListP* result = malloc(sizeof(ListP));
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

bool insertListHeadP(ListP* list, Point* p, List* luc){
	if(p == NULL){
		printf("\nWarning: point is NULL\n");
		return false;
	}
	if(list != NULL){
		if(list->head != NULL){
			if(list->length == 1){
				list->queue = createListpoint(list->queue->value);
				list->head = createListpoint(p);
				list->head->luc = luc;
				list->queue->next = list->head;
				list->head->prev = list->queue; 
				list->length += 1;
			}
			else{
				list->head->next = createListpoint(p);
				list->head->next->luc = luc;
				list->head->next->prev = list->head;
				list->head = list->head->next;
				list->length+=1;
			}
		}
		else{
			// printf("\nWarning: HEAD of List is NULL\n");
			list->head = createListpoint(p);
			list->head->luc = luc;
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

// pas de luc gestion !!!! 
bool insertListQueueP(ListP* list, Point* p){
	if(p == NULL){
		printf("\nWarning: point is NULL\n");
		return false;
	}
	if(list != NULL){
		if(list->queue != NULL){
			if(list->length == 1){
				list->queue = createListpoint(p);
				list->head = createListpoint(list->head->value);
				list->queue->next = list->head;
				list->head->prev = list->queue; 
				list->length += 1;
			}
			else{
				list->queue->prev = createListpoint(p);
				list->queue->prev->next = list->queue;
				list->queue = list->queue->prev;
				list->length+=1;
			}
		}
		else{
			// printf("\nWarning: QUEUE of List is NULL\n");
			list->queue = createListpoint(p);
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

bool delHeadP(ListP* list){
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

bool delQueueP(ListP* list){
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


bool delListP(ListP* list, Point* p){
	if(list->length == 1){
		list->head = NULL;
		list->queue = NULL;
		list->length = 0;
		return true; 
	}
	return delListRecP(list, list->queue, p);
}

bool delListRecP(ListP* list, Listpoint* node, Point* p){
	if(equalPoint(list->queue->value, p)){
		list->queue->next->prev = NULL;
		list->queue = list->queue->next;
		list->length-=1;
		return true;
	}
	else if(equalPoint(list->head->value, p)){
		list->head->prev->next= NULL;
		list->head = list->head->prev;
		list->length-=1;
		return true; 
	}
	else if(equalPoint(node->value, p)){
		node->prev->next = node->next; 
		node->next->prev = node->prev;
		list->length-=1;
		return true; 
	}
	else if(node->next != NULL){
		delListRecP(list, node->next, p);
	}
	else{
		// printf("\nSegment is not in list\n");
		return false;
	}
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% PRINT LIST FUNCTIONS 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void printListP(ListP* list){
	if(list == NULL){
		printf("\nList is NULL\n");
		return;
	}
	else if(list->length == 0){
		printf("\nList is empty\n");
	}
	else if(list->length == 1){
		printf("\n<QUEUE> :[]:[");
		printPoint(list->queue->value);
		printf("]:[]: <head>\n");
	}
	else {
		printf("\n<QUEUE> :[]:[");
		printListRecP(list->queue);
	}
}

void printListRecP(Listpoint* node){
	if(node != NULL){
		printPoint(node->value);
		printf("]:[");
		printListRecP(node->next);
	}
	else{
		printf("]: <HEAD>\n\n");
	}
}

