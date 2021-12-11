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



bool insertSeg(Treeseg **rootptr, Point* p, Segment* s, Treeseg *parent, bool b) { // insert the segment s in the tree; p is the node being analyzed on the sweep line (needed to know where the segments cross the horizontal sweep line)
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
		if (p->x < x_root || (p->x == x_root && (m_s != 0.0 && (m_root > 0.0 && (m_s <= 0 || m_s > m_root)) || (m_root < 0.0 && (m_s >= 0 || m_s < m_root))) || (m_root == 0.0 && (m_s < 0.0 || s->p0->y == s->p1->y)) || (m_root == m_s && s->p0->y != s->p1->y && s->p1->y < root->value->p1->y))) {
			return insertSeg(&(root->left), p, s, root, b);
		}// error ici 
		else {
			return insertSeg(&(root->right), p, s, root, b);
		}
	}
	else{ // the segment in root is horizontal 
		if ((p->x < root->value->p0->x) || (p->x == root->value->p0->x && s->p1->x < root->value->p1->x && s->p0->y == s->p1->y)){
			return insertSeg(&(root->left), p, s, root, b);
		}
		else{
			insertSeg(&(root->right), p, s, root, b);
		}
	}
}



bool delSeg(Treeseg** root, Segment* seg, Point *p){ // delete the segment seg from the tree where the point p gives information about the position of the sweep line
	if(*root != NULL){
		Treeseg* tree = malloc(sizeof(Treeseg));
		tree = findSeg(*root, seg, p); // find the segment in the tree
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
						printf("error: my parents doesn't have children...\n";
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



Treeseg* findSeg(Treeseg *root, Segment *s, Point *p) { // find and return the tree with s as upper node (if it is in the tree, NULL otherwise), p is again there to inform about the position of the sweep line
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
			
		
		if (x_s < x_root || (x_s == x_root && (m_s != 0.0 && (m_root > 0.0 && (m_s <= 0 || m_s > m_root)) || (m_root < 0.0 && (m_s >= 0 || m_s < m_root))) || (m_root == 0.0 && (m_s < 0.0 || s->p0->y == s->p1->y)) || (m_root == m_s && s->p0->y != s->p1->y && s->p1->y < root->value->p1->y))) {
			return findSeg((root->left), s, p);
		}
		else {
			return findSeg((root->right), s, p);
		}
	}
	else{ // root is horizontal 
		if ((x_s < root->value->p0->x) || (x_s == root->value->p0->x && s->p1->x < root->value->p1->x && s->p0->y == s->p1->y)){
			return findSeg((root->left), s, p);
		}
		else{
			return findSeg((root->right), s, p);
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



Segment* findLParent(Treeseg* root){ // return the segment contained in the node of the first parent node of root that has root on its right
	if (root != NULL){
		if (root->parent != NULL){
			if(root->parent->left != NULL){
				if(equalSegment(root->value, root->parent->left->value)){ // root is on the left of its parent node: continue to go up in the tree
					return findLParent(root->parent);
				}
				// the parent node has two children and root is on its right: bingo return the parent value
				return root->parent->value;
			}
			else{
				return root->parent->value; 
			}
		}
	}
	return NULL;
}



Segment* findRParent(Treeseg* root){ // return the segment contained in the node of the first parent node of root that has root on its left
	if (root != NULL){
		if (root->parent != NULL){
			if(root->parent->right != NULL){
				if(equalSegment(root->value, root->parent->right->value)){ // root is on the right of its parent node: continue to go up in the tree
					return findRParent(root->parent);
				}
				// the parent node has two children and root is on its left: bingo return the parent value
				return root->parent->value;
			}
			else{
				return root->parent->value; 
			}
		}
	}
	return NULL;
}



Segment* findLeftNb(Treeseg* root, Segment* s, Point* p){ // return the segment in the closest left neighbour of s in root
	if(root != NULL){
		Treeseg* tree = malloc(sizeof(Treeseg));
		tree = findSeg(root, s, p); // find s in root
		if(tree->left != NULL){ // if the node containing s has a left child then its left neigbour is on the most right point of its left child tree
			return findRSeg(tree->left)->value;
		}
		else{ // if he node containing s has no left child then its left neighbour is the first parent node of s node that has s node on its right tree
			return findLParent(tree);
		}
	}
	return NULL;
}



Segment* findRightNb(Treeseg* root, Segment* s, Point* p){ // return the segment in the closest right neighbour of s in root
	if(root != NULL){
		Treeseg* tree = malloc(sizeof(Treeseg));
		tree = findSeg(root, s, p); // find s in root
		if(tree->right != NULL){ // if the node containing s has a right child then its right neigbour is on the most left point of its right child tree
			return findLSeg(tree->right)->value;
		}
		else{// if he node containing s has no right child then its right neighbour is the first parent node of s node that has s node on its left tree
			return findRParent(tree);
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

