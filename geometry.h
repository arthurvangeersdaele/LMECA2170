#ifndef GEOMETRY_H_
#define GEOMETRY_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Segment Segment;
typedef struct Point Point;
typedef struct List List;
typedef struct Listseg Listseg;
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Points
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
struct Point{
	float x;
	float y;
	struct List* U;
	//Segment* segments;
};

Point *createPoint(float, float);
bool equalPoint(Point*, Point*);
void printPoint(Point *p);


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Segments
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

struct Segment{
	struct Point* p0;
	struct Point* p1;
	int value;
};

Segment *createSegment(Point*, Point*, int);
Segment checkSegment(Segment*, int);
bool equalSegment(Segment*, Segment*);
void printSeg(Segment *s);
void printSeg2(Segment *s);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% POINTS & SEGMENTS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
bool contains(Point*, Segment*);


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% SEGMENTS LIST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

struct List{
	struct Listseg *head;
	struct Listseg *queue;
	int length;
};

struct Listseg {
	Segment *value;
	struct Listseg *prev;
	struct Listseg *next;

};

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


