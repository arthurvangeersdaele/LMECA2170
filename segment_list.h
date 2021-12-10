#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"

#ifndef SEGMENT_LIST_H_
#define SEGMENT_LIST_H_

typedef struct List{
	struct Listseg *head;
	struct Listseg *queue;
}List;

typedef struct Listseg {
	Segment *value;
	struct Listseg *prev;
	struct Listseg *next;

}Listseg;

Listseg *createListseg(Segment*);
List *createList(Segment*);
bool insertListHead(List*, Segment*);
bool insertListQueue(List*, Segment*);
bool delList(List*, Segment*);
bool delListRec(List*, Listseg*, Segment*);
void printList(List*);
void printListRec(Listseg*);
#endif
