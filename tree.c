#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <tree.h>

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%% POINTS
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Point* createPoint(float x, float y, int value) {
	Point* result = malloc(sizeof(Point));
	if (result != NULL) {
		result->x = x;
		result->y = y;
		result->value = value;
	}
	return result;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%% SEGMENTS
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Segment* checkSegment(Segment *s, int value) {
	Segment* result = malloc(sizeof(Segment));
	if (result != NULL) {
		if (s->p0->y < s->p1->y) {
			result->p0 = s->p0;
			result->p1= s->p1;
		}
		else if (s->p0->y == s->p1->y && s->p0->x < s->p1->x) {
			result->p0 = s->p0;
			result->p1 = s->p1;
		}
		else if (s->p0->y > s->p1->y) {
			result->p0 = s->p1;
			result->p1 = s->p0;
		}
		result->value = value;
		*s = *result; 
		free(result);
	}
	return s;
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%% TREE
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
typedef struct Treenode {
	int value;
	struct Treenode *left;
	struct Treenode *right;

}Treenode;

Treenode *createNode(int p) {
	Treenode* result = malloc(sizeof(Treenode));
	if (result != NULL) {
		result->left = NULL;
		result->right = NULL;
		result->value = p;
	}
	return result;
}

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
	printf("value = %d\n", root->value);
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

bool insertPoint(Treenode **rootptr, int value, Treenode *parent) {
	Treenode *root = *rootptr;
	if (root == NULL) {
		(*rootptr) = createNode(value);
		/*(*rootptr)->left = createNode(value);
		printTree(parent);
		if (parent != NULL) {
			if (value < parent->value) {
				(*rootptr)->right = createNode(parent->value);
			}
	}*/
		return true;
	}
	if (value == root->value) {
		return false;
	}
	if (value < root->value) {
		return insertPoint(&(root->left), value, root->left);
	}
	else {
		return insertPoint(&(root->right), value, root->right);
	}
}

bool findPoint(Treenode *root, int value) {
	if (root == NULL) {
		return false;
	}
	if (value == root->value) {
		return true;
	}
	if (value < root->value) {
		return findPoint(root->left, value);
	}
	else {
		return findPoint(root->right, value);
	}
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%% MAIN
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//int main()
//{
//	Treenode *root = NULL;
//	insertPoint(&root, 1, root);
//	insertPoint(&root, 5, root);
//	insertPoint(&root, 6, root);
//	insertPoint(&root, 1, root);
//	insertPoint(&root, 3, root);
//	insertPoint(&root, 0, root);
//	insertPoint(&root, 9, root);
//
//	printTree(root);
//	printf("%d (%d)\n", 9, findPoint(root, 9));
//	printf("%d (%d)\n", 7, findPoint(root, 7));
//	free(root);
//}

