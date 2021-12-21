#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#ifndef tol
//#define tol 0.00000001
#define tol 0.0000000001
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Segment Segment;
typedef struct Point Point;
typedef struct List List;
typedef struct Listseg Listseg;


bool feq(double, double);
bool fgreater(double, double);
bool flower(double, double);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Points
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
struct Point{
	double x;
	double y;
	struct List* U;
	//Segment* segments;
};

Point *createPoint(double, double, List*);
bool equalPoint(Point*, Point*);
bool equalPointTOL(Point*, Point*);
void freePoint(Point*);
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
void freeSeg(Segment*);
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
bool insertList(List*, Listseg*);

bool delHead(List*);
//bool delQueue(List*);
//bool delList(List*, Segment*);
//bool delListRec(List*, Listseg*, Segment*);

List* concatenate(List*, List*, List*);
List* concatenate2(List*, List*);

void freeList(List*);
void freeListSeg(Listseg*);

void printList(List*);
void printListRec(Listseg*);
void printListLight(List*);
void printListLightRec(Listseg*);

#endif


