#ifndef POINT_LIST_H_
#define POINT_LIST_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% CREATE A LIST NODE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Listpoint* createListpoint(Point*);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% CREATE A LIST STRUCTURE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
ListP* createVoidListP();

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% ADD A SEGMENT IN LIST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
bool insertListHeadP(ListP*, Point*, List*);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% FREE LIST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void freeListP(ListP*);
void freeListpoint(Listpoint*);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% PRINT LIST FUNCTIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void printListP(ListP*);
void printListRecP(Listpoint*);

#endif
