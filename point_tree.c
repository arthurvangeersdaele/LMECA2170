#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"
#include "point_tree.h"


Treenode *createNode(Point *p) { // create a simple node
	Treenode* result = malloc(sizeof(Treenode));
	if (result != NULL) {
		result->parent = NULL;
		result->left = NULL;
		result->right = NULL;
		result->value = p;
	}
	return result;
}

bool insertPoint(Treenode **rootptr, Point* p, Treenode *parent, bool upper, bool b) { // insert a point p in the tree; upper means that p is an upper point of some segment
	Treenode *root = *rootptr;
	if (root == NULL) { // if the tree is empty we just add the point
		(*rootptr) = createNode(p);
		if(upper){ // if p is some upper point we need to add the segment to its U list
			(*rootptr)->value->value++;
		}
		if (parent != NULL){ // initialize the parent node
			(*rootptr)->parent = parent;
		}
		else{ // first node to be created: this node has no parent
			(*rootptr)->parent = NULL;
		}
		return true;
	}
	if (p->x == root->value->x && p->y == root->value->y) { // if the point is already in the tree we do not add it again
		if(upper){ // if p is some upper point we need to add the segment to its U list
			(*rootptr)->value->value++;
		}
		else{
			return false;
		}
	}
	if (p->y < root->value->y || (p->y == root->value->y && p->x < root->value->x)) { // add p to the left if p is above the current root or on same height but to the left (ie sweep line will first visit p then root)
		return insertPoint(&(root->left), p, root, upper, b);
	}
	else { // go right
		return insertPoint(&(root->right), p, root, upper, b);
	}
}


bool findPoint(Treenode *root, Point *p) { // return true if p is in the tree (root)
	if (root == NULL) {
		return false;
	}
	if (equalPoint(p, root->value)) {
		return true;
	}
	if (p->y < root->value->y || (p->y == root->value->y && p->x < root->value->x)) {
		return findPoint(root->left, p);
	}
	else {
		return findPoint(root->right, p);
	}
}


Point* delPoint(Treenode **root){ // Delete the point the most on the left of the tree root and return that point
	if(*root == NULL){// the tree is empty
		return (*root)->value;
	}
	if((*root)->left != NULL){// go on the left if possible
		delPoint(&((*root)->left));
	}
	else{// we have reach the point
		if((*root)->parent != NULL && (*root)->right != NULL){ // link the parent of the node with its right child
			Point *p = malloc(sizeof(Point));
			p = (*root)->value;
			(*root)->right->parent = (*root)->parent;
			(*root)->parent->left = (*root)->right;
			return p;
		}
		if((*root)->parent != NULL && (*root)->right == NULL){ // the parent of the node is now a leaf
			Point *p = malloc(sizeof(Point));
			p = (*root)->value;
			(*root)->parent->left = NULL;
			return p;
		}
		else if((*root)->parent== NULL && (*root)->right != NULL){ // the right child becomes the upper parent of the tree
			Point *p = malloc(sizeof(Point));
			p = (*root)->value; 
			(*root) = (*root)->right;
			(*root)->parent = NULL;
			return p;
		}
		else { // the point is the only node remaining in the tree
			return (*root)->value;
		}
		
	}
	return (*root)->value;
}


/*
bool checkTree(Treenode* root){
	if(root != NULL){
		if(root-> left != NULL){
			insertPoint(&root->left, root->value, root, false, true);
			checkTree(root->left);
			if (root->right != NULL){
				if(root->right->left != NULL || root->right->right != NULL){
					checkTree(root->right);
				}
			}
			return true;
		}
		else{
			root->left = createNode(root->value);
			root->left->parent = root;
			if (root->right != NULL){
				if(root->right->left != NULL || root->right->right != NULL){
					checkTree(root->right);
				}
			}
			return true;
		}
	}
	return false; 
}*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Tree Print functions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void printtabs(int numtabs) {
	for (int i = 0; i < numtabs; i++) {
		printf("\t");
	}
}

void printTreeRec(Treenode* root, int level) {
	if (root == NULL) {
		printtabs(level);
		printf("---<empty>---\n");
		return;
	}
	printtabs(level);
	printPoint(root->value);
	//printf("value = (%f, %f) : %d\n", root->value->x, root->value->y, root->value->value);
	printtabs(level);
	printf("left\n");

	printTreeRec(root->left, level + 1);
	printtabs(level);
	printf("right\n");
	printTreeRec(root->right, level + 1);
	printtabs(level);

	printf("done\n");
}

void printTree(Treenode *root) {
	printTreeRec(root, 0);
}




