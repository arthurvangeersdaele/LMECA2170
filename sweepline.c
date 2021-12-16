#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"
#include "point_tree.h"
#include "segment_tree.h"
#include "point_list.h"
#include "sweepline.h"

/*
void delForC(Treeseg* Tau, List* Ci, Point* p){
	if (Ci->head != NULL){
		delSeg(&Tau, Ci->head->value, p);
		return delForC(Tau, Ci->prev, p);
	}
	return;
}*/

void insertForC(Treeseg* Tau, Listseg* Ci, Point* p){
	if (Ci!= NULL){
		delSeg(&Tau, Ci->value, p);
		insertSeg(&Tau, p, Ci->value, Tau);
		return insertForC(Tau, Ci->prev, p);
	}
	return;
}

void insertForU(Treeseg* Tau, Listseg* Ui, Point* p){
	if (Ui != NULL){
		insertSeg(&Tau, p, Ui->value, Tau);
		return insertForU(Tau, Ui->prev, p);
	}
	return;
}

void createQ(Listseg* s, Treenode* Q){
	if (s != NULL){
		insertPoint(&Q, s->value->p0, Q, s->value, true); // <- update si p0 already dans le tree
		insertPoint(&Q, s->value->p1, Q, s->value, false);
		return createQ(s->prev, Q);
	}
	return;
}


void findNewEvent(Segment *sL, Segment *sR, Point *p, Treenode *Q){
	// if sL and sR intersect below the sweep line, or on it and to the right of the current event point p, 
	// and the intersection is not yet present as an event in Q
	float mL, mR;
	float pL, pR;
	
	float x_inter, y_inter;
	if (sL->p0->x != sL->p1->x){//sL not vertical
		mL = (sL->p0->y - sL->p1->y) / (sL->p0->x - sL->p1->x);
		pL = sL->p0->y - mL * sL->p0->x;
	}
	if (sR->p0->x != sR->p1->x){//sR not vertical
		mR = (sL->p0->y - sL->p1->y) / (sL->p0->x - sL->p1->x);
		pR = sL->p0->y - mL * sL->p0->x;
	}
	if ((sL->p0->x != sL->p1->x) && (sR->p0->x != sR->p1->x)){ // deux segment non verticaux
		if (mL != mR){// si deux segments sont l'un sur l'autre on ne reporte pas d'intersections!
			x_inter = (pL - pR) / (mR - mL);
			y_inter = pL + mL * x_inter;
			if (y_inter > p->y || (y_inter == p->y && x_inter > p->x)){ // check si l'intersection arrive apres p dans la sweep line
				insertPoint(&Q, createPoint(x_inter, y_inter), Q, NULL, false);
			}
		}
	}else if (sL->p0->x != sL->p1->x){// right is vertical
		x_inter = sR->p0->x;
		y_inter = pL + mL * x_inter;
		if (y_inter > p->y || (y_inter == p->y && x_inter > p->x)){ // check si l'intersection arrive apres p dans la sweep line
			insertPoint(&Q, createPoint(x_inter, y_inter), Q, NULL, false);
		}
	}else if (sR->p0->x != sR->p1->x){// left is vertical
		x_inter = sL->p0->x;
		y_inter = pR + mR * x_inter;
		if (y_inter > p->y || (y_inter == p->y && x_inter > p->x)){ // check si l'intersection arrive apres p dans la sweep line
			insertPoint(&Q, createPoint(x_inter, y_inter), Q, NULL, false);
		}
	}
}


void HandleEventPoint(Point *p, Treeseg* Tau, ListP* Inter, Treenode *Q){
	List* L = malloc(sizeof(List));
	L = createVoidList();
	
	List* C = malloc(sizeof(List));
	C = createVoidList();
	
	List* RLNeigh = malloc(sizeof(List));
	RLNeigh = createVoidList();
	
	
	findLandC(Tau, NULL, p, false, L, C, RLNeigh);
		
	if (p->U->length + L->length + C->length > 1){// p is an intersection point
		insertListHeadP(Inter, p, concatenate(p->U, L, C));
	}
	
	//Delete segment with p as lower point from the tree
	for(int i=0; i<(L->length); i++){
		delSeg(&Tau, L->head->value, p);
		delHead(L);
	}
	//Delete and reinsert segment containing p from the tree (so they switch positions)
	insertForC(Tau, C->head, p);
	//Insert segment with p as upper point
	insertForU(Tau, p->U->head, p);
	
	
	// Check for new intersections
	if (p->U->length + C->length == 0){// p is only a lower point
		if (RLNeigh->length == 2){// sl and sr exists
			findNewEvent(RLNeigh->head->value, RLNeigh->queue->value, p, Q);
		}
	}else{
		Segment* LeftMost = malloc(sizeof(Segment));
		Segment* RightMost = malloc(sizeof(Segment));
		Segment* LeftNeigh = malloc(sizeof(Segment));
		Segment* RightNeigh = malloc(sizeof(Segment));
		
		if (LeftMost != NULL){
			LeftMost = findLeftMost(Tau, NULL, p, false);
		}
		if (RightMost != NULL){
			RightMost = findRightMost(Tau, NULL, p, false);
		}
		
		if (LeftNeigh != NULL && LeftMost != NULL){
			LeftNeigh = findLeftNb(Tau, LeftMost, p, true)->value;
		}
		if (RightNeigh != NULL && RightMost != NULL){
			RightNeigh = findRightNb(Tau, RightMost, p, true)->value;
		}
		
		if (LeftNeigh != NULL && LeftMost != NULL){
			findNewEvent(LeftNeigh, LeftMost, p, Q);
		}
		if (RightNeigh != NULL && RightMost != NULL){
			findNewEvent(RightNeigh, RightMost, p, Q);
		}
		
	}
	
	
}


ListP* FindIntersections(List* s){ //<- list of segments 
	// 1- checkSegment to sort segemnts -- ease process for Upper/Lower points (v)
	// 2 - (p, list s) -> return s(starting = p)  <---- donner aux segment.value la valeur de Upper Point  <<< tous les points qui vont être dans l'arbre Q
	// 3 - creer l'arbre Q avec tous les points
	Treenode *Q = malloc(sizeof(Treenode));
	Q = NULL;
	createQ(s->head, Q);


	Treeseg *Tau = malloc(sizeof(Treeseg));
	Tau = NULL; // tous les points qui sont sur L (sweepline)
	
	ListP* Intersections = malloc(sizeof(ListP));
	Intersections = createVoidListP();
	
	Point *p = malloc(sizeof(Point));
	p = NULL;
	
	while(Q != NULL){
		p = delPoint(&Q);
		HandleEventPoint(p, Tau, Intersections, Q);
	}
	//check all point which y <line 
	// is their p1 lower ?
	free(Tau);
	free(Q);
	free(p);
	return Intersections;
}


