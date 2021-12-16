#ifndef SEGMENT_LIST_H_
#define SEGMENT_LIST_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "segment.h"


typedef struct List{
	struct Listseg *head;
	struct Listseg *queue;
	int length;
}List;

typedef struct Listseg {
	Segment *value;
	struct Listseg *prev;
	struct Listseg *next;

}Listseg;

Listseg *createListseg(Segment*);


List *createVoidList();
List *createList(Segment*);

bool insertListHead(List*, Segment*);
bool insertListQueue(List*, Segment*);

bool delHead(List*);
bool delQueue(List*);
bool delList(List*, Segment*);
bool delListRec(List*, Listseg*, Segment*);

List* concatenate(List*, List*, List*);
List* concatenate2(List*, List*);

void printList(List*);
void printListRec(Listseg*);
void printListLight(List*);
void printListLightRec(Listseg*);

#endif
