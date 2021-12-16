#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "inputs.h"
//include "translate.h"
#include "geometry.h"
//#include "point_tree.h"


List* fromTab2List(GLfloat coord[][2], GLsizei nPoints){
	List* segmentList = malloc(sizeof(List));
	segmentList = createVoidList();
	
	for (GLsizei i=0; i<(nPoints/2); i+=2) {
		insertListHead(segmentList, createSegment(createPoint(coord[i][0], coord[i][1]), createPoint(coord[i+1][0], coord[i+1][1]), i/2));
	}
		
	return segmentList;
}


int main() {
	const GLsizei nPoints = 500;
	GLfloat (*coord)[2] = malloc(sizeof(coord[0])*nPoints);

	random_points(coord, nPoints);
	List* segmentList = fromTab2List(coord, nPoints);
	//Point* p = createPoint(1.0, 1.0);
	//printPoint(p);
	//free(p);
	free(segmentList);
}

