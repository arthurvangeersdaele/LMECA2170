#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "point.h"
#include "segment.h"
#include "point_tree.h"
#include "segment_tree.h"
#include "segment_list.h"

int main() {
	/*Point p;
	printf("Hello World\n");
	p = createPoint(1, 10, 1);
	Treenode* n1 = createNode(&p);
	Point p2 = createPoint(1, 1, 2);
	insertPoint(&n1, &p2, n1);
	printTree(n1);*/
	
	/*
	Treenode *tree;
	Point* p = createPoint(5.0, 0.0, 5);
	Treenode* node = createNode(p);
	insertPoint(&tree, p, node);
	
	free(node);
	free(p);
	printTree(tree);
	free(tree);
	*/
	
	/*int length = 9;
	//liste = (int*)malloc(sizeof(int)*1);
	int liste[] = {5, 2, 8, 1, 3, 6, 10, 7, 9};
	Treenode *tree = NULL;
	Point* p;
	for(int i = 0; i<length; i++){
		p = createPoint(liste[i], 0);
		insertPoint(&tree, p, tree, false, false);
	}
	printTree(tree);

	for(int i = 1; i<=9; i++){
		p = delPoint(&tree);
	}

	printTree(tree);
	
	free(tree);
	free(p);*/
	

	/*Treeseg *tree = NULL;

	


	Segment* s;
	Point* p1;
	Point* p2; 
	int length = 4;
	float liste_x1[] = {1.0, 1.4, 2.0, 3.0};
	float liste_y1[] = {3.0, 2.0, 3.0, 1.0};
	float liste_x2[] = {4.5, 3.5, 2.5, 0.75};
	float liste_y2[] = {3.0, 5.5, 5.5, 5.5};

	for(int i = 0; i < length; i++){
		p1 = createPoint(liste_x1[i], liste_y1[i]);
		p2 = createPoint(liste_x2[i], liste_y2[i]);
		s = createSegment(p1, p2, i);
		insertSeg(&tree, createPoint(2.0, 3.0), s, tree, false);
		if(i == 0){
			insertSeg(&tree, createPoint(0.6, 2.8), createSegment(createPoint(1.0, 2.0), createPoint(0.0, 4.0), -1), tree, false);
		}
	}
	printTreeseg(tree);

	/*int i = 0;
	p1 = createPoint(liste_x1[i], liste_y1[i]);
	p2 = createPoint(liste_x2[i], liste_y2[i]);
	delSeg(&tree, createSegment(p1, p2, i), createPoint(2.0, 3.0));
	printTreeseg(tree);

	int i = 2;
	p1 = createPoint(liste_x1[i], liste_y1[i]);
	p2 = createPoint(liste_x2[i], liste_y2[i]);
	// printSeg(findLeftNb(tree, createSegment(p1, p2, i), createPoint(2.0, 3.0)));
	
	printSeg(findRightNb(tree, createSegment(createPoint(1.0, 2.0), createPoint(0.0, 4.0), -1), createPoint(0.6, 2.8)));
	
	free(tree);
	free(p1);
	free(p2); 
	free(s);*/


	List* list = createVoidList();
	Segment* s;
	Point* p1;
	Point* p2; 

	int length = 4;
	float liste_x1[] = {1.0, 1.4, 2.0, 3.0};
	float liste_y1[] = {3.0, 2.0, 3.0, 1.0};
	float liste_x2[] = {4.5, 3.5, 2.5, 0.75};
	float liste_y2[] = {3.0, 5.5, 5.5, 5.5};
	
	printListLight(NULL);

	for(int i = 0; i < length; i++){
		p1 = createPoint(liste_x1[i], liste_y1[i]);
		p2 = createPoint(liste_x2[i], liste_y2[i]);
		s = createSegment(p1, p2, i);
		insertListHead(list, s);
		printListLight(list);
	}

	for(int i = 0; i < length; i++){
		delQueue(list);
		printListLight(list);
	}
	

}

