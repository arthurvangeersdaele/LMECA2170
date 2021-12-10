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

		if(root->value->p0->x != root->value->p1->x){ // root n'est pas vertical 
			m_root = (root->value->p0->y - root->value->p1->y)/(root->value->p0->x - root->value->p1->x);
			p_root = root->value->p0->y - m_root*(root->value->p0->x);
		}
		if(s->p0->x != s->p1->x){ // segment n'est pas vertical 
			m_s = (s->p0->y - s->p1->y)/(s->p0->x - s->p1->x);
			p_s = s->p0->y - m_s*(s->p0->x);
		} 
		// probleme ici ! 
		//if (p->x < x_root || (p->x == x_root && m_s != 0.0 && m_root != 0.0 && m_s < m_root) || (p->x == x_root && m_s == 0.0 && m_root > 0.0) || (p->x == x_root && m_root == 0.0 && m_s < 0.0)) {
		if (p->x < x_root || (p->x == x_root && m_s != 0.0 && m_root > 0.0 && (m_s <= 0 || m_s > m_root)) || (p->x == x_root && m_s != 0.0 && m_root < 0.0 && (m_s >= 0 || m_s < m_root)) || (p->x == x_root && m_s == 0.0 && m_root > 0.0) || (p->x == x_root && m_root == 0.0 && m_s < 0.0)) {
			return insertSeg(&(root->left), p, s, root, b);
		}// error ici 
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
		printf("j'entre la fonction\n");
		tree = findSeg(*root, seg, p);
		printf("j'ai trouvé le segment\n");
		printTreeseg(tree);
		printf("\n");
		if(tree->left == NULL && tree->right == NULL){
			printf("je suis un leaf\n");
			if(tree->parent != NULL){
				if(tree->parent->left != NULL){
					if(equalSegment(tree->parent->left->value, tree->value)){
						tree->parent->left = NULL;
						return true; 
					}
				}
				else if(tree->parent->right != NULL){
					tree->parent->right = NULL;
					return true; 
				}
				else{
					printf("error, enfant is not reconnu par les darons");
					return false;
				}
			}
			else{
				*root = NULL;
				return true;
			}
		}
		else if(tree->left != NULL && tree->right != NULL){
			printf("j'ai des enfants à gauche et à droite\n");
			Treeseg* child = malloc(sizeof(Treeseg));
			child = findRSeg(tree->left);
			delSeg(root, child->value, p);
			printTreeseg(*root);
			printf("\n\n\n");
			free(tree->value);
			tree->value = child->value;
			return true; 
		}

		else{
			if(tree->left == NULL){
				printf("je n'ai que un enfant à droite\n");
				if(tree->parent != NULL){
					if(tree->parent->left != NULL){
						if(equalSegment(tree->parent->left->value, tree->value)){
						printf("je suis l'enfant de gauche\n");
						tree->parent->left = tree->right;
						return true;
						}
					}
					else if(tree->parent->right != NULL){
						printf("je suis l'enfant de droite\n");
						tree->parent->right = tree->right;
						return true; 
					}
					else{
						printf("error, enfant is not reconnu par les darons");
						return false;
					}
				}
				else{
					(*root) = tree->right;
					return true;
				}
			}
			else if(tree->right == NULL){
				printf("je n'ai que un enfant à gauche \n");
				if(tree->parent != NULL){
					if(tree->parent->left != NULL){
						if(equalSegment(tree->parent->left->value, tree->value)){
						printf("je suis l'enfant de gauche\n");
						tree->parent->left = tree->left;
						return true;
						}
					}
					else if(tree->parent->right != NULL){
						printf("je suis l'enfant de droite\n");
						tree->parent->right = tree->left;
						return true; 
					}
					else{
						printf("error, enfant is not reconnu par les darons");
						return false;
					}
				}
				else{
					printf("je suis le mega giga daron\n");
					(*root) = tree->left;
					printTreeseg(*root);
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
	//Calcul du croisement de s avec la sweep line
	float x_s;
	if (s->p0->y != s->p1->y){ // s n'est pas horizontal 
		x_s = (p->y * (s->p0->x - s->p1->x) - s->p1->y * s->p0->x + s->p0->y * s->p1->x);
		x_s /= (s->p0->y - s->p1->y);
	}else{
		x_s = s->p0->x;
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
		}
		if (x_s < x_root || (x_s == x_root && m_s != 0.0 && m_root > 0.0 && (m_s <= 0 || m_s > m_root)) || (x_s == x_root && m_s != 0.0 && m_root < 0.0 && (m_s >= 0 || m_s < m_root)) || (x_s == x_root && m_s == 0.0 && m_root > 0.0) || (x_s == x_root && m_root == 0.0 && m_s < 0.0)) {
			return findSeg((root->left), s, p);
		}
		else {
			return findSeg((root->right), s, p);
		}
	}
	else{ // root est horizontal 
		if((x_s < root->value->p0->x) || (s->p0->y != s->p1->y && x_s == root->value->p0->x)){
			return findSeg((root->left), s, p);
		}
		else{
			return findSeg((root->right), s, p);
		}
	}
}

Treeseg* findRSeg(Treeseg* root){
	if(root == NULL){
		return NULL;
	}
	if(root->right != NULL){
		return findRSeg(root->right);
	}
	return root;
}

Treeseg* findLSeg(Treeseg* root){
	if(root == NULL){
		return NULL;
	}
	if(root->left != NULL){
		return findLSeg(root->left);
	}
	return root;
}

Segment* findLParent(Treeseg* root){
	if(root->parent != NULL){
		if(root->parent->left != NULL){
			if(equalSegment(root->value, root->parent->left->value)){
				findLParent(root->parent);
			}
			else if(root != NULL){
				return root->value;
			}
			else{
				return NULL; 
			}
		}
		else{
			return root->parent->value; 
		}
	}
	else{
		return NULL;
	}
}

Segment* findRParent(Treeseg* root){
	if(root->parent != NULL){
		if(root->parent->right != NULL){
			if(equalSegment(root->value, root->parent->right->value)){
				findRParent(root->parent);
			}
			else if(root != NULL){
				return root->parent->value;
			}
			else{
				return NULL; 
			}
		}
		else{
			return root->parent->value; 
		}
	}
	else{
		return NULL;
	}
}

Segment* findLeftNb(Treeseg* root, Segment* s, Point* p){
	if(root != NULL){
		Treeseg* tree = malloc(sizeof(Treeseg));
		tree = findSeg(root, s, p);
		if(tree->left != NULL){
			return findRSeg(tree->left)->value;
		}
		else{
			// chzrcher le premier parent qui a s dans son right
			return findLParent(tree);
		}
	}
	return NULL;
}


Segment* findRightNb(Treeseg* root, Segment* s, Point* p){
	if(root != NULL){
		Treeseg* tree = malloc(sizeof(Treeseg));
		tree = findSeg(root, s, p);
		if(tree->right != NULL){
			return findLSeg(tree->right)->value;
		}
		else{
			// chzrcher le premier parent qui a s dans son right
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

