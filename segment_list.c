#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"
#include "segment_list.h"

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
		printf("\nWarning: list is empty\n");
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
		printf("\nWarning: list is empty\n");
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
		printf("\nSegment is not in list\n");
		return false;
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