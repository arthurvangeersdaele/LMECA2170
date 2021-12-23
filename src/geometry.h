#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#ifndef tol
//#define tol 0.00000001
#define tol 0.0000000001
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Segment Segment;
typedef struct Point Point;
typedef struct List List;
typedef struct Listseg Listseg;


bool feq(double, double);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Points
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
struct Point{
	double x;
	double y;
	struct List* U;
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

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% CREATE A LIST STRUCTURE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
List *createVoidList();

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% ADD A SEGMENT IN LIST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
bool insertListHead(List*, Segment*);
bool insertListQueue(List*, Segment*);
bool insertList(List*, Listseg*);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% LIST CONCATENATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
List* concatenate(List*, List*, List*);
List* concatenate2(List*, List*);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% FREE LIST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void freeList(List*);
void freeListSeg(Listseg*);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% PRINT LIST FUNCTIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void printList(List*);
void printListRec(Listseg*);
#endif


