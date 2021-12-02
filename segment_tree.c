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

// Le point p est le point qui est en cours d'analysation sur la sweep line
bool insertSeg(Treeseg **rootptr, Point* p, Segment* s, Treeseg *parent, bool b) {
	Treeseg *root = *rootptr;
	if (root == NULL) {
		(*rootptr) = createSeg(s);
		if (parent != NULL){
			(*rootptr)->parent = parent;
		}
		else{
			(*rootptr)->parent = NULL;
		}
		return true;
	}
	if (equalPoint(p, root->value->p0) && (s->p1, root->value->p1) {
		// ATTENTION AU CAS D'UN SEGMENT INCLUS DANS UN AUTRE LEQUEL VA EN PREMS???
		
		/*if (b){
			(*rootptr) = createNode(p);
			(*rootptr)->parent = parent;
			return true;
		}
		else{
			return false;
		}*/
		return false;
	}
	if (p->x < root->value->p0->x || (p->x == root->value->p0->x && s->p1->x < root->value->p1->x)) {
		return insertSeg(&(root->left), p, s, root, b);
	}
	else {
		return insertPoint(&(root->right), p, s, root, b);
	}
}

/*
// find a given value for the points in the tree
bool findSeg(Treeseg *root, Segment *s) {
	if (root == NULL) {
		return false;
	}
	if (equalPoint(s->p0, root->value->p0) && equalPoint(s->p1, root->value->p1)) {
		return true;
	}
	if (COMPLIQUE AVEC LES INTERSECTIONS DE SEGMENTS) {
		return findPoint(root->left, p);
	}
	else {
		return findPoint(root->right, p);
	}
}*/

Treeseg* delSeg(Treeseg *root, Treeseg *head){
	if(root == NULL){return head;}
	if(root->left != NULL){
		head = delSeg(root->left, head);
	}
	else{
		if(root->parent != NULL){
			if(root->parent->parent != NULL && root->parent->right != NULL){
				root->parent->parent->left = root->parent->right;
				root->parent->right->parent = root->parent->parent;
				free(root->parent);
				free(root);
				return head;
			}
			else if(root->parent->parent == NULL && root->parent->right != NULL){
				head = root->parent->right;
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

/*
// PROBLEME ICI L'ARBRE EST PAS FIXE!!
bool checkTree2(Treeseg* root){
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


