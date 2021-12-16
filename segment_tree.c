#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"
#include "segment_tree.h"

Treeseg *createSeg(Segment *s) {
	Treeseg* result = malloc(sizeof(Treeseg));
	if (result != NULL) {
		result->parent = NULL;
		result->left = NULL;
		result->right = NULL;
		result->value = s;
	}
	return result;
}



bool insertSeg(Treeseg **rootptr, Point* p, Segment* s, Treeseg *parent) { // insert the segment s in the tree; p is the node being analyzed on the sweep line (needed to know where the segments cross the horizontal sweep line)
	Treeseg *root = *rootptr;
	if (root == NULL) { // if the tree is empty we just add the segment
		(*rootptr) = createSeg(s);
		if (parent != NULL){ // if nodes are already in the tree we need to link the parent
			(*rootptr)->parent = parent;
		}
		else{ // the node is the first one to be inserted in the tree
			(*rootptr)->parent = NULL;
		}
		return true;
	}
	if (equalPoint(s->p0, root->value->p0) && equalPoint(s->p1, root->value->p1)) { // the segment is already in the tree so we do nothing
		return false;
	}

	if(root->value->p0->y != root->value->p1->y){ // the segment in root is not horizontal 
		float p_root, p_s = 0.0; // (imaginary) crossing of the segments of root and segm. s with the y axis
		float m_root, m_s = 0.0; // slopes of the segm. root and the segm. s
		float x_root = (p->y * (root->value->p0->x - root->value->p1->x) - root->value->p1->y * root->value->p0->x + root->value->p0->y * root->value->p1->x);
		x_root/=(root->value->p0->y - root->value->p1->y); // x_root is the intersection point of segm. root and the sweep line
		// Note that p is the intersection of s with the sweep line

		if(root->value->p0->x != root->value->p1->x){ // segm. of root is not vertical: compute the slope and oao of segm. of root 
			m_root = (root->value->p0->y - root->value->p1->y)/(root->value->p0->x - root->value->p1->x);
			p_root = root->value->p0->y - m_root*(root->value->p0->x);
		}
		if(s->p0->x != s->p1->x){ // s is not vertical: compute the slope and the oao of s
			m_s = (s->p0->y - s->p1->y)/(s->p0->x - s->p1->x);
			p_s = s->p0->y - m_s*(s->p0->x);
		}
		// if the segment of root is vertical we know that m_root=0
		
		// probleme ici !
		if (p->x < x_root || (p->x == x_root && (m_s != 0.0 && (m_root > 0.0 && (m_s <= 0.0 || m_s > m_root)) || (m_root <= 0.0 && (m_s < m_root || s->p0->y == s->p1->y))) || (m_root == m_s && s->p0->y != s->p1->y && s->p1->y < root->value->p1->y))) {
			return insertSeg(&(root->left), p, s, root);
		}// error ici 
		else {
			return insertSeg(&(root->right), p, s, root);
		}
	}
	else{ // the segment in root is horizontal 
		if ((p->x < root->value->p0->x) || (p->x == root->value->p0->x && s->p1->x < root->value->p1->x && s->p0->y == s->p1->y)){
			return insertSeg(&(root->left), p, s, root);
		}
		else{
			insertSeg(&(root->right), p, s, root);
		}
	}
}



bool delSeg(Treeseg** root, Segment* seg, Point *p){ // delete the segment seg from the tree where the point p gives information about the position of the sweep line
	if(*root != NULL){
		Treeseg* tree = malloc(sizeof(Treeseg));
		tree = findSegBEFOREUPDATE(*root, seg, p); // find the segment in the tree
		if(tree->left == NULL && tree->right == NULL){ // The seg node is a leaf: just remove the segment node from the tree
			if(tree->parent != NULL){ // there are other nodes in the tree
				// find if the segm is on the left or the right of the parent node
				if(tree->parent->left != NULL){
					if(equalSegment(tree->parent->left->value, tree->value)){
						tree->parent->left = NULL;
						return true; 
					}
				}
				else if(tree->parent->right != NULL){ // if right exists and the segm is not on the left of its parent then it is on the right
					tree->parent->right = NULL;
					return true; 
				}
				else{
					printf("error: my parents doesn't have children...\n");
					return false;
				}
			}
			else{ // The segment is the only node is the tree so deleting seg suppress the tree
				*root = NULL;
				free(*root);
				free(tree);
				return true;
			}
		}
		else if(tree->left != NULL && tree->right != NULL){ // the seg node has two children in the tree: we delete seg by replacing it by the leaf the most on the right of the left tree of the node of seg
			Treeseg* child = malloc(sizeof(Treeseg));
			child = findRSeg(tree->left); // find the replacement, delete that node in the tree and replace in the seg node the value by the replacement value
			delSeg(root, child->value, p);
			free(tree->value);
			tree->value = child->value;
			return true; 
		}
		else{ // the seg node has only one children
			if(tree->left == NULL){ // child on the right
				if(tree->parent != NULL){ // the segment is not in the top upper node: we need to rely the parent of the node of segm with the child tree of the node of segm
					if(tree->parent->left != NULL){
						if(equalSegment(tree->parent->left->value, tree->value)){ // the segm. node lies on the left of its parent
						tree->parent->left = tree->right;
						return true;
						}
					}
					else if(tree->parent->right != NULL){ // if right exists and the segm is not on the left of its parent then it is on the right
						tree->parent->right = tree->right;
						return true; 
					}
					else{
						printf("error: my parents doesn't have children...\n");
						return false;
					}
				}
				else{ // if the segm is in the top upper node then we just take its right tree as the tree with segm deleted
					(*root) = tree->right;
					return true;
				}
			}
			else if(tree->right == NULL){ // child on the left
				if(tree->parent != NULL){ // the segment is not in the top upper node: we need to rely the parent of the node of segm with the child tree of the node of segm
					if(tree->parent->left != NULL){
						if(equalSegment(tree->parent->left->value, tree->value)){ // the segm. node lies on the left of its parent
						tree->parent->left = tree->left;
						return true;
						}
					}
					else if(tree->parent->right != NULL){ // if right exists and the segm is not on the left of its parent then it is on the right
						tree->parent->right = tree->left;
						return true; 
					}
					else{
						printf("error: my parents doesn't have children...\n");
						return false;
					}
				}
				else{ // if the segm is in the top upper node then we just take its left tree as the tree with segm deleted
					(*root) = tree->left;
					printTreeseg(*root);
					return true;
				}
			}
		}
	}
	return false;
}



Treeseg* findSegAFTERUPDATE(Treeseg *root, Segment *s, Point *p) { // find and return the tree with s as upper node (if it is in the tree, NULL otherwise), p is again there to inform about the position of the sweep line; Careful root is update with the point p!
	if (root == NULL) { // s in not in the tree root
		return NULL;
	}
	if (equalPoint(s->p0, root->value->p0) && equalPoint(s->p1, root->value->p1)) { // bingo we found the node containing s
		return root;
	}
	
	float x_s; // intersection of s with the sweep line
	if (s->p0->y != s->p1->y){ // s is not horizontal 
		x_s = (p->y * (s->p0->x - s->p1->x) - s->p1->y * s->p0->x + s->p0->y * s->p1->x);
		x_s /= (s->p0->y - s->p1->y);
	}else{ // s is horizontal: we know that all segments in the tree cross the sweep line, if horizontal segm, infinite number of crossing but the first one is on P0 (upper point of s)
		x_s = s->p0->x;
	}
	
	if(root->value->p0->y != root->value->p1->y){ // root n'est pas horizontal 
		float p_root, p_s = 0.0; // (imaginary) crossing of the segments of root and segm. s with the y axis
		float m_root, m_s = 0.0; // slopes of the segm. root and the segm. s
		float x_root = (p->y * (root->value->p0->x - root->value->p1->x) - root->value->p1->y * root->value->p0->x + root->value->p0->y * root->value->p1->x);
		x_root /= (root->value->p0->y - root->value->p1->y); // x_root is the intersection point of segm. root and the sweep line
		
		
		if(root->value->p0->x != root->value->p1->x){ // segm. of root is not vertical: compute the slope and oao of segm. of root 
			m_root = (root->value->p0->y - root->value->p1->y)/(root->value->p0->x - root->value->p1->x);
			p_root = root->value->p0->y - m_root*(root->value->p0->x);
		}
		if(s->p0->x != s->p1->x){ // s is not vertical: compute the slope and the oao of s
			m_s = (s->p0->y - s->p1->y)/(s->p0->x - s->p1->x);
			p_s = s->p0->y - m_s*(s->p0->x);
		}
		// if the segment of root is vertical we know that m_root=0
			
		
		if (p->x < x_root || (p->x == x_root && (m_s != 0.0 && (m_root > 0.0 && (m_s <= 0.0 || m_s > m_root)) || (m_root <= 0.0 && (m_s < m_root || s->p0->y == s->p1->y))) || (m_root == m_s && s->p0->y != s->p1->y && s->p1->y < root->value->p1->y))) {
			return findSegAFTERUPDATE((root->left), s, p);
		}
		else {
			return findSegAFTERUPDATE((root->right), s, p);
		}
	}
	else{ // root is horizontal 
		if ((p->x < root->value->p0->x) || (p->x == root->value->p0->x && s->p1->x < root->value->p1->x && s->p0->y == s->p1->y)){
			return findSegAFTERUPDATE((root->left), s, p);
		}
		else{
			return findSegAFTERUPDATE((root->right), s, p);
		}
	}
}




Treeseg* findSegBEFOREUPDATE(Treeseg* root, Segment* s, Point* p) { // find and return the tree with s as upper node (if it is in the tree, NULL otherwise), p is again there to inform about the position of the sweep line; Careful root is not yet update with the point p!
	if (root == NULL) { // s in not in the tree root
		return NULL;
	}
	if (equalPoint(s->p0, root->value->p0) && equalPoint(s->p1, root->value->p1)) { // bingo we found the node containing s
		return root;
	}
	
	float x_s; // intersection of s with the sweep line
	if (s->p0->y != s->p1->y){ // s is not horizontal 
		x_s = (p->y * (s->p0->x - s->p1->x) - s->p1->y * s->p0->x + s->p0->y * s->p1->x);
		x_s /= (s->p0->y - s->p1->y);
	}else{ // s is horizontal: we know that all segments in the tree cross the sweep line, if horizontal segm, infinite number of crossing but the first one is on P0 (upper point of s)
		x_s = s->p0->x;
	}
	if(root->value->p0->y != root->value->p1->y){ // root n'est pas horizontal 
		float p_root, p_s = 0.0; // (imaginary) crossing of the segments of root and segm. s with the y axis
		float m_root, m_s = 0.0; // slopes of the segm. root and the segm. s
		float x_root = (p->y * (root->value->p0->x - root->value->p1->x) - root->value->p1->y * root->value->p0->x + root->value->p0->y * root->value->p1->x);
		x_root /= (root->value->p0->y - root->value->p1->y); // x_root is the intersection point of segm. root and the sweep line
		
		
		if(root->value->p0->x != root->value->p1->x){ // segm. of root is not vertical: compute the slope and oao of segm. of root 
			m_root = (root->value->p0->y - root->value->p1->y)/(root->value->p0->x - root->value->p1->x);
			p_root = root->value->p0->y - m_root*(root->value->p0->x);
		}
		if(s->p0->x != s->p1->x){ // s is not vertical: compute the slope and the oao of s
			m_s = (s->p0->y - s->p1->y)/(s->p0->x - s->p1->x);
			p_s = s->p0->y - m_s*(s->p0->x);
		}
		// if the segment of root is vertical we know that m_root=0
			
		
		if (x_s < x_root || (x_s == x_root && (m_s != 0.0 && (m_root < 0.0 && (m_s > 0.0 || m_s < m_root)) || (m_root >= 0.0 && ((m_s > 0.0 && m_s < m_root) || s->p0->y == s->p1->y))) || (m_root == m_s && s->p0->y != s->p1->y && s->p0->y < root->value->p0->y))) {
			return findSegBEFOREUPDATE((root->left), s, p);
		}
		else {
			return findSegBEFOREUPDATE((root->right), s, p);
		}
	}
	else{ // root is horizontal 
		if (x_s < root->value->p0->x){
			return findSegBEFOREUPDATE((root->left), s, p);
		}
		else{
			return findSegBEFOREUPDATE((root->right), s, p);
		}
	}
}



Treeseg* findRSeg(Treeseg* root){ // return the right most node of root
	if(root == NULL){
		return NULL;
	}
	if(root->right != NULL){
		return findRSeg(root->right);
	}
	return root;
}



Treeseg* findLSeg(Treeseg* root){ // return the left most node of root
	if(root == NULL){
		return NULL;
	}
	if(root->left != NULL){
		return findLSeg(root->left);
	}
	return root;
}



Treeseg* findLParent(Treeseg* root){ // return the first parent node of root that has root on its right
	if (root != NULL){
		if (root->parent != NULL){
			if(root->parent->left != NULL){
				if(equalSegment(root->value, root->parent->left->value)){ // root is on the left of its parent node: continue to go up in the tree
					return findLParent(root->parent);
				}
				// the parent node has two children and root is on its right: bingo
				return root->parent;
			}
			else{
				return root->parent; 
			}
		}
	}
	return NULL;
}



Treeseg* findRParent(Treeseg* root){ // return the first parent node of root that has root on its left
	if (root != NULL){
		if (root->parent != NULL){
			if(root->parent->right != NULL){
				if(equalSegment(root->value, root->parent->right->value)){ // root is on the right of its parent node: continue to go up in the tree
					return findRParent(root->parent);
				}
				// the parent node has two children and root is on its left: bingo
				return root->parent;
			}
			else{
				return root->parent; 
			}
		}
	}
	return NULL;
}



Treeseg* findLeftNb(Treeseg* root, Segment* s, Point* p, bool BEFORE){ // return the closest left neighbour of root
	if(root != NULL){
		Treeseg* tree = malloc(sizeof(Treeseg));
		// find s in root
		if (BEFORE){
			tree = findSegBEFOREUPDATE(root, s, p);
		}else{
			tree = findSegAFTERUPDATE(root, s, p);
		}
		
		if(tree->left != NULL){ // if the node containing s has a left child then its left neigbour is on the most right point of its left child tree
			return findRSeg(tree->left);
		}
		else{ // if he node containing s has no left child then its left neighbour is the first parent node of s node that has s node on its right tree
			return findLParent(tree);
		}
	}
	return NULL;
}



Treeseg* findRightNb(Treeseg* root, Segment* s, Point* p, bool BEFORE){ // return the closest right neighbour of root
	if(root != NULL){
		Treeseg* tree = malloc(sizeof(Treeseg));
		// find s in root
		if (BEFORE){
			tree = findSegBEFOREUPDATE(root, s, p);
		}else{
			tree = findSegAFTERUPDATE(root, s, p);
		}
		
		if(tree->right != NULL){ // if the node containing s has a right child then its right neigbour is on the most left point of its right child tree
			return findLSeg(tree->right);
		}
		else{// if he node containing s has no right child then its right neighbour is the first parent node of s node that has s node on its left tree
			return findRParent(tree);
		}
	}
	return NULL;
}



bool findLandC(Treeseg* root, Treeseg* prev, Point* p, bool foundp, List* L, List* C, List* LR){
	if (root != NULL){
		bool isLower = equalPoint(root->value->p1, p);
		bool Contain = contains(p, root->value);
		float x_root;// x_root is the intersection point of segm. root and the sweep line
		if (root->value->p0->y != root->value->p1->y){
			x_root = (p->y * (root->value->p0->x - root->value->p1->x) - root->value->p1->y * root->value->p0->x + root->value->p0->y * root->value->p1->x);
			x_root /= (root->value->p0->y - root->value->p1->y); 
		}else{
			x_root = root->value->p0->x;
		}
		if (!(isLower||Contain)){//the point is not in the segment of the root node
			if (foundp){// we found the last right or left segment that contains p in root
				if (equalSegment(prev->value, findRightNb(root, root->value, p, true)->value)){
					insertListHead(LR, root->value);
				}else{
					insertListQueue(LR, root->value);
				}
				return foundp;
			}else{
				if (p->x < x_root){//p is on the left of segment in root
					return findLandC(root->left, root, p, false, L, C, LR);
				}else{
					return findLandC(root->right, root, p, false, L, C, LR);
				}
			}
		}else{//p is on segment in root
			//Find left and right neighbours of root
			Treeseg* rightNeigh = malloc(sizeof(Treeseg));
			rightNeigh = findRightNb(root, root->value, p, true);
			Treeseg* leftNeigh = malloc(sizeof(Treeseg));
			leftNeigh = findLeftNb(root, root->value, p, true);
			
			// update L and C
			if (isLower){//p is lower point of segment in root
				insertListHead(L, root->value);
			}else{//p is strictly contained in segment in root
				insertListHead(C, root->value);
			}
			
			if (!foundp){// root contains the first segm that contains p so look for its right and left neigh
				findLandC(leftNeigh, root, p, true, L, C, LR);
				findLandC(rightNeigh, root, p, true, L, C, LR);
			}else if(equalSegment(prev->value, rightNeigh->value)){// we already looked up on the right: look only for the left neigh
				findLandC(leftNeigh, root, p, true, L, C, LR);
			}else{// we already looked up on the left: look only for the right neigh
				findLandC(rightNeigh, root, p, true, L, C, LR);
			}
			free(leftNeigh);
			free(rightNeigh);
			return foundp;
		}
	}
	return foundp;
}



Segment* findLeftMost(Treeseg* root, Treeseg* prev, Point* p, bool foundp){
	if (root != NULL){
		bool isUpper = equalPoint(root->value->p0, p);
		bool Contain = contains(p, root->value);
		float x_root;// x_root is the intersection point of segm. root and the sweep line
		if (root->value->p0->y != root->value->p1->y){
			x_root = (p->y * (root->value->p0->x - root->value->p1->x) - root->value->p1->y * root->value->p0->x + root->value->p0->y * root->value->p1->x);
			x_root /= (root->value->p0->y - root->value->p1->y); 
		}else{
			x_root = root->value->p0->x;
		}
		if (!(isUpper||Contain)){//the point is not in the segment of the root node
			if (foundp){// we found the last right or left segment that contains p in root
				return prev->value;
			}else{
				if (p->x < x_root){//p is on the left of segment in root
					return findLeftMost(root->left, root, p, false);
				}else{
					return findLeftMost(root->right, root, p, false);
				}
			}
		}else{//p is on segment in root
			//Find left and right neighbours of root
			Treeseg* rightNeigh = malloc(sizeof(Treeseg));
			rightNeigh = findRightNb(root, root->value, p, false);
			Treeseg* leftNeigh = malloc(sizeof(Treeseg));
			leftNeigh = findLeftNb(root, root->value, p, false);
			
			if (!foundp){// root contains the first segm that contains p so look for its right and left neigh
				free(rightNeigh);
				return findLeftMost(leftNeigh, root, p, true);
			}else if(equalSegment(prev->value, rightNeigh->value)){// we already looked up on the right: look only for the left neigh
				free(rightNeigh);
				return findLeftMost(leftNeigh, root, p, true);
			}
		}
	}
	return NULL;
}


Segment* findRightMost(Treeseg* root, Treeseg* prev, Point* p, bool foundp){
	if (root != NULL){
		bool isUpper = equalPoint(root->value->p0, p);
		bool Contain = contains(p, root->value);
		float x_root;// x_root is the intersection point of segm. root and the sweep line
		if (root->value->p0->y != root->value->p1->y){
			x_root = (p->y * (root->value->p0->x - root->value->p1->x) - root->value->p1->y * root->value->p0->x + root->value->p0->y * root->value->p1->x);
			x_root /= (root->value->p0->y - root->value->p1->y); 
		}else{
			x_root = root->value->p0->x;
		}
		if (!(isUpper||Contain)){//the point is not in the segment of the root node
			if (foundp){// we found the last right or left segment that contains p in root
				return prev->value;
			}else{
				if (p->x < x_root){//p is on the left of segment in root
					return findRightMost(root->left, root, p, false);
				}else{
					return findRightMost(root->right, root, p, false);
				}
			}
		}else{//p is on segment in root
			//Find left and right neighbours of root
			Treeseg* rightNeigh = malloc(sizeof(Treeseg));
			rightNeigh = findRightNb(root, root->value, p, false);
			Treeseg* leftNeigh = malloc(sizeof(Treeseg));
			leftNeigh = findLeftNb(root, root->value, p, false);
			
			if (!foundp){// root contains the first segm that contains p so look for its right and left neigh
				free(leftNeigh);
				return findRightMost(rightNeigh, root, p, true);
			}else if(equalSegment(prev->value, leftNeigh->value)){// we already looked up on the right: look only for the left neigh
				free(leftNeigh);
				return findRightMost(rightNeigh, root, p, true);
			}
		}
	}
	return NULL;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Tree Print functions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void printtabsseg(int numtabs) {
	for (int i = 0; i < numtabs; i++) {
		printf("\t");
	}
}

void printTreesegRec(Treeseg* root, int level) {
	if (root == NULL) {
		printtabsseg(level);
		printf("---<empty>---\n");
		return;
	}
	printtabsseg(level);
	printSeg(root->value);
	//printf("value = (%f, %f) : %d\n", root->value->x, root->value->y, root->value->value);
	printtabsseg(level);
	printf("left\n");

	printTreesegRec(root->left, level + 1);
	printtabsseg(level);
	printf("right\n");
	printTreesegRec(root->right, level + 1);
	printtabsseg(level);

	printf("done\n");
}

void printTreeseg(Treeseg *root) {
	printTreesegRec(root, 0);
}

