#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"
#include "segment_list.h"

Listseg *createListseg(Segment* s){
	Listseg* result = malloc(sizeof(Listseg));
	if (result != NULL) {
		result->prev = NULL;
		result->next = NULL;
		result->value = s;
	}
	return result;
}

List *createList(Segment* s){
	List* result = malloc(sizeof(List));
	if (result != NULL) {
		result->head = createListseg(s);
		result->queue = createListseg(s);
	}
	return result;
}

bool insertListHead(List* list, Segment* s){
	if(s == NULL){
		printf("Warning: segment is NULL");
		return false;
	}
	if(list != NULL){
		if(list->head != NULL){
			list->head->next = createListseg(s);
			list->head->next->prev = list->head;
			list->head = list->head->next;
		}
		else{
			printf("Warning: HEAD of List is NULL");
			return false;
		}
	}
	else{
		return false;
	}
}

bool insertListQueue(List* list, Segment* s){
	if(s == NULL){
		printf("Warning: segment is NULL");
		return false;
	}
	if(list != NULL){
		if(list->queue != NULL){
			list->queue->prev = createListseg(s);
			list->queue->prev->next = list->queue;
			list->queue = list->queue->prev;
		}
		else{
			printf("Warning: QUEUE of List is NULL");
			return false;
		}
	}
	else{
		return false;
	}
}

bool delList(List* list, Segment* s){
	return delListRec(list, list->queue, s);
}

bool delListRec(List* list, Listseg* node, Segment* s){
	if(equalSegment(list->queue->value, s)){
		list->queue->next->prev = NULL;
		list->queue = list->queue->next;
		return true;
	}
	else if(equalSegment(list->head->value, s)){
		list->head->prev->next= NULL;
		list->head = list->head->prev;
		return true; 
	}
	else if(equalSegment(node->value, s)){
		node->prev->next = node->next; 
		node->next->prev = node->prev;
		return true; 
	}
	else if(node->next != NULL){
		delListRec(list, node->next, s);
	}
	else{
		printf("Segment is not in list");
		return false;
	}
}

void printList(List* list){
	if(list != NULL){
		printf("<QUEUE> [");
		printListRec(list->queue);
	}
	else{
		printf("List is NULL");
	}
}

void printListRec(Listseg* node){
	if(node != NULL){
		printSeg(node->value);
		printf("]:[");
		printListRec(node->next);
	}
	else{
		printf("]: <HEAD>");
	}
}