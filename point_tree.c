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
        result->value = createPoint(p->x, p->y, p->U);
    }
    return result;
}

bool insertPoint(Treenode **rootptr, Point* p, Treenode *parent, Segment* s, bool upper) { // insert a point p in the tree; upper means that p is an upper point of some segment
    Treenode *root = *rootptr;
    if (root == NULL) { // if the tree is empty we just add the point
        (*rootptr) = createNode(p);
        if(upper){ // if p is some upper point we need to add the segment to its U list
            insertListHead((*rootptr)->value->U, s);
        }
        if (parent != NULL){ // initialize the parent node
            (*rootptr)->parent = parent;
        }
        else{ // first node to be created: this node has no parent
            (*rootptr)->parent = NULL;
        }
        return true;
    }
    if (equalPointTOL(root->value, p)) { // if the point is already in the tree we do not add it again
        if(upper){ // if p is some upper point we need to add the segment to its U list
            insertListHead((*rootptr)->value->U, s);
        }
        return false;
    }
    if (p->y < root->value->y || (p->y == root->value->y && p->x < root->value->x)) { // add p to the left if p is above the current root or on same height but to the left (ie sweep line will first visit p then root)
        return insertPoint(&(root->left), p, root, s, upper);
    }
    else { // go right
        return insertPoint(&(root->right), p, root, s, upper);
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
        return NULL;
    }
    if((*root)->left != NULL){// go on the left if possible
        return delPoint(&((*root)->left));
    }
    else{// we have reach the point
        if((*root)->parent != NULL && (*root)->right != NULL){ // link the parent of the node with its right child
            Point* p = createPoint((*root)->value->x, (*root)->value->y, (*root)->value->U);

            Treenode *par = (*root)->parent;
            Treenode *r = (*root)->right;

            freePoint((*root)->value);
            free(*root);
            *root = NULL;

            r->parent = par;
            par->left = r;
            return p;
        }
        if((*root)->parent != NULL && (*root)->right == NULL){ // the parent of the node is now a leaf
            Point* p = createPoint((*root)->value->x, (*root)->value->y, (*root)->value->U);
            (*root)->parent->left = NULL;
            freeTreenode(*root);
            return p;
        }
        else if((*root)->parent== NULL && (*root)->right != NULL){ // the right child becomes the upper parent of the tree
            Point *p = createPoint((*root)->value->x, (*root)->value->y, (*root)->value->U);

            Treenode *r = (*root)->right;

            freePoint((*root)->value);
            free(*root);
            *root = NULL;

            (*root) = r;
            (*root)->parent = NULL;
            return p;
        }
        else { // the point is the only node remaining in the tree
            Point *p = createPoint((*root)->value->x, (*root)->value->y, (*root)->value->U);
            freeTreenode(*root);
            (*root) = NULL;
            return p;
        }

    }
}


void freeTreenode(Treenode* root){
    if (root == NULL){
        return;
    }
    freeTreenode(root->left);
    freeTreenode(root->right);

    freePoint(root->value);
    free(root);
    root = NULL;
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




