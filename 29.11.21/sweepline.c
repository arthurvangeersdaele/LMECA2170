#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"
#include "tree.h"
#include "sweepline.h"


NULL findNewEvent(Segment *sL, Segment *sR, Point *p){
	if()
}

NULL HandleEventPoint(Point *p1, Point *p2, Point *p3){

}

NULL FindIntersections(Segment s[]){ //<- list of segments 
	// 1- checkSegment to sort segemnts -- ease process for Upper/Lower points (v)
	// 2 - (p, list s) -> return s(starting = p)  <---- donner aux segment.value la valeur de Upper Point  <<< tous les points qui vont être dans l'arbre Q
	// 3 - creer l'arbre Q avec tous les points
	Treenode *Q = createNode(NULL);
	for(int i = 0; i < sizeof(s); i++){
		Point upper = s[i].p0;
		Point lower = s[i].p1;
		insertPoint(&Q, &upper); // <- update si p0 already dans le tree
		insertPoint(&Q, &lower);
	}

	Treenode *Tau = createNode(NULL); // tous les points qui sont sur L (sweepline)
	//check all point which y <line 
	// is their p1 lower ? 
}