#ifndef POINT_LIST_H_
#define POINT_LIST_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"


typedef struct ListP{
	struct Listpoint *head;
	struct Listpoint *queue;
	int length;
}ListP;

typedef struct Listpoint {
	Point *value;
	struct Listpoint *prev;
	struct Listpoint *next;
	struct List *luc;
}Listpoint;

Listpoint* createListpoint(Point*);


ListP* createVoidListP();
ListP* createListP(Point*);

bool insertListHeadP(ListP*, Point*, List*);
bool insertListQueueP(ListP*, Point*);

bool delHeadP(ListP*);
bool delQueueP(ListP*);
bool delListP(ListP*, Point*);
bool delListRecP(ListP*, Listpoint*, Point*);

void freeListP(ListP*);
void freeListpoint(Listpoint*);

void printListP(ListP*);
void printListRecP(Listpoint*);

#endif
