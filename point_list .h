#ifndef POINT_LIST_H_
#define POINT_LIST_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "point.h"
#include "segment_list.h"


typedef struct ListP{
	struct Listpoint *head;
	struct Listpoint *queue;
	int length;
}ListP;

typedef struct Listpoint {
	Point *value;
	struct Listpoint *prev;
	struct Listpoint *next;
	struct Listseg *luc;

}Listpoint;

Listseg *createListpoint(Point*);


List *createVoidListP();
List *createListP(Point*);

bool insertListHeadP(ListP*, Point*);
bool insertListQueueP(ListP*, Point*);

bool delHeadP(ListP*);
bool delQueueP(ListP*);
bool delListP(ListP*, Point*);
bool delListRecP(ListP*, Listpoint*, Point*);

void printListP(ListP*);
void printListRecP(Listpoint*);

#endif
