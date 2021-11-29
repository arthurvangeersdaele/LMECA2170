#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"
#include "tree.h"

// create a simple node
Treenode *createNode(Point *p) {
	Treenode* result = malloc(sizeof(Treenode));
	if (result != NULL) {
		result->parent = NULL;
		result->left = NULL;
		result->right = NULL;
		result->value = p;
	}
	return result;
}
/*Treenode *createNode(int p) {
	Treenode* result = malloc(sizeof(Treenode));
	if (result != NULL) {
		result->left = NULL;
		result->right = NULL;
		result->value = p;
	}
	return result;
}*/

//insert a point in the binary tree
/*bool insertPoint(Treenode **rootptr, Point *p) {
	Treenode *root = *rootptr;
	if (root == NULL) {
		(*rootptr) = createNode(p);
		return true;
	}
	if (p->x == root->value->x && p->y == root->value->y) {
		return false;
	}
	if (p->y < root->value->y || (p->y == root->value->y && p->x < root->value->x)) {
		return insertPoint(&(root->left), p);
	}
	else {
		return insertPoint(&(root->right), p);
	}
}*/

bool insertPoint(Treenode **rootptr, Point* p, Treenode *parent) {
	Treenode *root = *rootptr;
	if (root == NULL) {
		(*rootptr) = createNode(p);
		(*rootptr)->parent = parent;
		return true;
	}
	if (p->x == root->value->x && p->y == root->value->y) {
		return false;
	}
	if (p->y < root->value->y || (p->y == root->value->y && p->x < root->value->x)) {
		return insertPoint(&(root->left), p, root->left);
	}
	else {
		return insertPoint(&(root->right), p, root->right);
	}
}

// find a given value for the points in the tree
bool findPoint(Treenode *root, Point *p) {
	if (root == NULL) {
		return false;
	}
	if (p->x == root->value->x && p->y == root->value->y) {
		return true;
	}
	if (p->y < root->value->y || (p->y == root->value->y && p->x < root->value->x)) {
		return findPoint(root->left, p);
	}
	else {
		return findPoint(root->right, p);
	}
}

bool checkTree(Treenode* root){
	if(root != NULL){
		if(root-> left != NULL){
			insertPoint(&root->left, root->value, root);
			checkTree(root->left);
		}
		if(root->right->left != NULL || root->right->right != NULL){
			checkTree(root->right);
		}
		else{
			root->left = createNode(root->left->value);
			root->left->parent = root;
		}
	}
	return false; 
}
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
	printf("value = (%f, %f) : %d\n", root->value->x, root->value->y, root->value->value);
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

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%% OLD MAIN
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*int main()
{
	Treenode *root = NULL;
	insertPoint(&root, createPoint(1, 1, 1), root);
	insertPoint(&root, createPoint(1, 3, 2), root);
	insertPoint(&root, createPoint(4, 1, 3), root);
	insertPoint(&root, createPoint(4, 5, 4), root);
	insertPoint(&root, createPoint(1, 2, 5), root);
	insertPoint(&root, createPoint(9, 9, 6), root);
	insertPoint(&root, createPoint(3, 3, 7), root);
	insertPoint(&root, createPoint(5, 1, 8), root);

	printTree(root);
	printf("%d (%d)\n", 9, findPoint(root, createPoint(3, 3, NULL)));
	printf("%d (%d)\n", 7, findPoint(root, createPoint(2, 2, NULL)));
	free(root);
}*/

