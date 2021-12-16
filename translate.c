#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "geometry.h"
#include "translate.h"

List* fromTab2List(GLfloat coord[][2], GLsizei nPoints){
	List* segmentList = malloc(sizeof(List));
	segmentList = createvoidList();
	
	for (GLsizei i=0; i<(nPoints/2); i+=2) {
		insertListHead(segmentList, createSegment(createPoint(coord[i][0], coord[i][1]), createPoint(coord[i+1][0], coord[i+1][1]), i/2));
	}
		
	return segmentList;
}


