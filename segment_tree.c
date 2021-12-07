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
	if (equalPoint(s->p0, root->value->p0) && equalPoint(s->p1, root->value->p1)) {
		// ATTENTION AU CAS D'UN SEGMENT INCLUS DANS UN AUTRE LEQUEL VA EN PREMS???
		return false;
	}

	if(root->value->p0->y != root->value->p1->y){ // root n'est pas horizontal 
		float p_root, p_s = 0.0; 
		float m_root, m_s = 0.0;
		float x_root = (p->y * (root->value->p0->x - root->value->p1->x) - root->value->p1->y * root->value->p0->x + root->value->p0->y * root->value->p1->x);
		x_root/=(root->value->p0->y - root->value->p1->y);

		if(root->value->p0->x != root->value->p1->x){
			m_root = (root->value->p0->y - root->value->p1->y)/(root->value->p0->x - root->value->p1->x);
			p_root = root->value->p0->y - m_root*(root->value->p0->x);
		}
		if(s->p0->x != s->p1->x){
			m_s = (s->p0->y - s->p1->y)/(s->p0->x - s->p1->x);
			p_s = s->p0->y - m_s*(s->p0->x);
		} // ATTENTION AUX SIGNES DES PENTES A CAUSE DE LA CONVENTION Y \> 
		if (p->x < x_root || (p->x == x_root && m_s != 0.0 && m_root != 0.0 && m_s > m_root) || (p->x == x_root && m_s == 0.0 && m_root > 0.0) || (p->x == x_root && m_root == 0.0 && m_s < 0.0)) {
			return insertSeg(&(root->left), p, s, root, b);
		}
		else {
			return insertSeg(&(root->right), p, s, root, b);
		}
	}
	else{ // root est horizontal 
		if((p->x < root->value->p0->x) || (s->p0->y != s->p1->y && p->x == root->value->p0->x)){
			return insertSeg(&(root->left), p, s, root, b);
		}
		else{
			insertSeg(&(root->right), p, s, root, b);
		}
	}
}


bool delSeg(Treeseg** root, Segment* seg, Point *p){
	if(*root != NULL){
		Treeseg* tree = malloc(sizeof(Treeseg));
		tree = findSeg(*root, seg, p);
		if(tree->left == NULL && tree->right == NULL){
			if(tree->parent != NULL){
				if(equalSegment(tree->parent->left->value, tree->value)){
					tree->parent->left = NULL;
					return true; 
				}
				else{
					tree->parent->right = NULL;
					return true; 
				}
			}
			else{
				*root = NULL;
				return true;
			}
		}
		else if(tree->left != NULL && tree->right != NULL){
			Treeseg* child = malloc(sizeof(Treeseg));
			child = findRSeg(tree->left);
			delSeg(root, child->value, p);
			free(tree->value);
			tree->value = child->value;
			return true; 
		}

		else{
			if(tree->left == NULL){
				if(equalSegment(tree->parent->left->value, tree->value)){
					tree->parent->left = tree->right;
					return true;
				}
				else{
					tree->parent->right = tree->right;
					return true; 
				}
			}
			else if(tree->right == NULL){
				if(equalSegment(tree->parent->left->value, tree->value)){
					tree->parent->left = tree->left;
					return true;
				}
				else{
					tree->parent->right = tree->left;
					return true; 
				}
			}
		}
	}
	else{
		return false; 
	}
}



// find a given value for the points in the tree
Treeseg* findSeg(Treeseg *root, Segment *s, Point *p) {
	if (root == NULL) {
		return NULL;
	}
	if (equalPoint(s->p0, root->value->p0) && equalPoint(s->p1, root->value->p1)) {
		return root;
	}
	if(root->value->p0->y != root->value->p1->y){ // root n'est pas horizontal 
		float p_root, p_s = 0.0; 
		float m_root, m_s = 0.0;
		float x_root = (p->y * (root->value->p0->x - root->value->p1->x) - root->value->p1->y * root->value->p0->x + root->value->p0->y * root->value->p1->x);
		x_root/=(root->value->p0->y - root->value->p1->y);

		if(root->value->p0->x != root->value->p1->x){
			m_root = (root->value->p0->y - root->value->p1->y)/(root->value->p0->x - root->value->p1->x);
			p_root = root->value->p0->y - m_root*(root->value->p0->x);
		}
		if(s->p0->x != s->p1->x){
			m_s = (s->p0->y - s->p1->y)/(s->p0->x - s->p1->x);
			p_s = s->p0->y - m_s*(s->p0->x);
		} // ATTENTION AUX SIGNES DES PENTES A CAUSE DE LA CONVENTION Y \> 
		if (p->x < x_root || (p->x == x_root && m_s != 0.0 && m_root != 0.0 && m_s > m_root) || (p->x == x_root && m_s == 0.0 && m_root > 0.0) || (p->x == x_root && m_root == 0.0 && m_s < 0.0)) {
			return findSeg((root->left), s, p);
		}
		else {
			return findSeg((root->right), s, p);
		}
	}
	else{ // root est horizontal 
		if((p->x < root->value->p0->x) || (s->p0->y != s->p1->y && p->x == root->value->p0->x)){
			return findSeg((root->left), s, p);
		}
		else{
			findSeg((root->right), s, p);
		}
	}
}

Treeseg* findRSeg(Treeseg* root){
	if(root == NULL){
		return NULL;
	}
	while(root->right != NULL){
		findRSeg(root->right);
	}
	return root;
}

/*Treeseg* delSeg(Treeseg *root, Treeseg *head){
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
}*/

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


