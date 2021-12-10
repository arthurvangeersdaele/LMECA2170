#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"
#include "point_tree.h"

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

bool insertPoint(Treenode **rootptr, Point* p, Treenode *parent, bool upper, bool b) {
	Treenode *root = *rootptr;
	if (root == NULL) {
		(*rootptr) = createNode(p);
		if(upper){
			(*rootptr)->value->value++;
		}
		if (parent != NULL){
			(*rootptr)->parent = parent;
		}
		else{
			(*rootptr)->parent = NULL;
		}
		return true;
	}
	if (p->x == root->value->x && p->y == root->value->y) {
		if(upper){
			(*rootptr)->value->value++;
		}
		if (b){
			(*rootptr) = createNode(p);
			(*rootptr)->parent = parent;
			return true;
		}
		else{
			return false;
		}
	}
	if (p->y < root->value->y || (p->y == root->value->y && p->x < root->value->x)) {
		return insertPoint(&(root->left), p, root, upper, b);
	}
	else {
		return insertPoint(&(root->right), p, root, upper, b);
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

/*Treenode* delPoint(Treenode *root, Treenode *head){
	if(root == NULL){return head;}
	if(root->left != NULL){
		head = delPoint(root->left, head);
	}
	else{
		if(root->parent != NULL){
			if(root->parent != NULL && root->right != NULL){
				root->parent->left = root->right;
				root->right->parent = root->parent;
				free(root);
				return head;
			}
			else if(root->parent== NULL && root->right != NULL){
				head = root->right;
				head->parent = NULL;
				return head;
			}
			else {
				free(head);
				free(root);
				return NULL;
			}
		}
	}
	return head;
}
*/
Point* delPoint(Treenode **root){
	if(*root == NULL){return (*root)->value;}
	if((*root)->left != NULL){
		delPoint(&((*root)->left));
	}
	else{
		//if(root->parent != NULL){
			if((*root)->parent != NULL && (*root)->right != NULL){
				Point *p = malloc(sizeof(Point));
				p = (*root)->value;
				(*root)->right->parent = (*root)->parent;
				(*root)->parent->left = (*root)->right;
				return p;
			}
			if((*root)->parent != NULL && (*root)->right == NULL){
				Point *p = malloc(sizeof(Point));
				p = (*root)->value;
				(*root)->parent->left = NULL;
				return p;
			}
			else if((*root)->parent== NULL && (*root)->right != NULL){
				Point *p = malloc(sizeof(Point));
				p = (*root)->value; 
				(*root) = (*root)->right;
				(*root)->parent = NULL;
				return p;
			}
			else {
				return (*root)->value;
			}
		
	}
	return (*root)->value;
}


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




