#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"
#include "point_tree.h"
#include "segment_tree.h"
#include "sweepline.h"

NULL findNewEvent(Segment *sL, Segment *sR, Point *p){
	// if sL and sR intersect below the sweep line, or on it and to the right of the current event point p, 
	// and the intersection is not yet present as an event in Q
	
	// then insert the intersection point as an event into Q
}

NULL HandleEventPoint(Point *p, Treeseg* Tau){
	Segment* LL = findLSeg(Tau)->value;
	if(contains(p, LL)){
		// ajouter segment LL dans C
	} 
	else if(equalPoint(p, LL->p1)){
		// ajouter LL dans L(OW)
	}
	
}

NULL FindIntersections(Segment s[]){ //<- list of segments 
	// 1- checkSegment to sort segemnts -- ease process for Upper/Lower points (v)
	// 2 - (p, list s) -> return s(starting = p)  <---- donner aux segment.value la valeur de Upper Point  <<< tous les points qui vont être dans l'arbre Q
	// 3 - creer l'arbre Q avec tous les points
	Treenode *Q = NULL;
	for(int i = 0; i < sizeof(s); i++){
		insertPoint(&Q, &(s[i].p0), &Q, true, false); // <- update si p0 already dans le tree
		insertPoint(&Q, &(s[i].p1), &Q, false, false);
	}

	// attribution des seg a leur upper ::: suspendu :::
	for(int i = 0; i <sizeof(s); i++){

	}

	Treeseg *Tau = NULL; // tous les points qui sont sur L (sweepline)
	Point *p;
	while(Q != NULL){
		p = delPoint(&Q);
		HandleEventPoint(p, Tau);
	}
	//check all point which y <line 
	// is their p1 lower ? 
	free(upper);
	free(lower);
	free(Q);
}
