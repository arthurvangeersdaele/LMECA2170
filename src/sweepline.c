#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "geometry.h"
#include "point_tree.h"
#include "segment_tree.h"
#include "point_list.h"
#include "sweepline.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Create Data Structure
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
dataStruct* initDataStruct(){
    dataStruct *result = malloc(sizeof(dataStruct));
    if (result != NULL) {
        result->Intersections = NULL;
        result->Q = NULL;
        result->Tau = NULL;
        result->p = NULL;
        result->LM = NULL;
        result->RM = NULL;
        result->LN = NULL;
        result->RN = NULL;
        result->RLN = NULL;
    }
    return result;
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Deletion / Insertion in the different elements
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void delForL(Treeseg** Tau, Listseg* Li, Point* p){
    if (Li != NULL){
        delSeg(Tau, Li->value, p);
        delForC(Tau, Li->prev, p);
    }
}

void delForC(Treeseg** Tau, Listseg* Ci, Point* p){
    if (Ci != NULL){
        delSeg(Tau, Ci->value, p);
        delForC(Tau, Ci->prev, p);
    }
}

void insertForC(Treeseg** Tau, Listseg* Ci, Point* p){
    if (Ci !=  NULL){
        insertSeg(Tau, p, Ci->value, *Tau);
        insertForC(Tau, Ci->prev, p);
    }
}

void insertForU(Treeseg** Tau, Listseg* Ui, Point* p){
    if (Ui != NULL){
        insertSeg(Tau, p, Ui->value, *Tau);
        insertForU(Tau, Ui->prev, p);
    }
}

void createQ(Listseg* s, Treenode** Q){
    if (s != NULL){
        insertPoint(Q, s->value->p0, *Q, s->value, true);
        insertPoint(Q, s->value->p1, *Q, s->value, false);
        createQ(s->prev, Q);
    }
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Algorithm Main Fonctions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void findNewEvent(Segment *sL, Segment *sR, Point *p, Treenode **Q, dataStruct *data){

    double mL, mR;
    double pL, pR;

    double x_inter, y_inter;

    if (sL->p0->x != sL->p1->x){//sL not vertical
        mL = (sL->p0->y - sL->p1->y) / (sL->p0->x - sL->p1->x);
        pL = sL->p0->y - mL * sL->p0->x;
    }
    if (sR->p0->x != sR->p1->x){//sR not vertical
        mR = (sR->p0->y - sR->p1->y) / (sR->p0->x - sR->p1->x);
        pR = sR->p0->y - mR * sR->p0->x;
    }

    if ((sL->p0->x != sL->p1->x) && (sR->p0->x != sR->p1->x)){ // two non-vertical segments
        if (mL != mR){// doesn't report intersection when overlapping segments
            x_inter = (pL - pR) / (mR - mL);
            y_inter = pL + mL * x_inter;
            if (y_inter > p->y || (y_inter == p->y && x_inter > p->x)){ // intersection happens bellow the sweep line
                Point *inter = createPoint(x_inter, y_inter, NULL);
                if ((contains(inter,sL) || equalPoint(inter, sL->p0) || equalPoint(inter, sL->p1)) && (contains(inter,sR) || equalPoint(inter, sR->p0) || equalPoint(inter, sR->p1))){
                    insertPoint(Q, inter, *Q, NULL, false);
                }
                freePoint(inter);
            }
        }
    }else if (sL->p0->x != sL->p1->x){// right is vertical
        x_inter = sR->p0->x;
        y_inter = pL + mL * x_inter;
        if (y_inter > p->y || (y_inter == p->y && x_inter > p->x)){ // intersection happens bellow the sweep line
            Point *inter = createPoint(x_inter, y_inter, NULL);
            if ((contains(inter,sL) || equalPoint(inter, sL->p0) || equalPoint(inter, sL->p1)) && (contains(inter,sR) || equalPoint(inter, sR->p0) || equalPoint(inter, sR->p1))){
                insertPoint(Q, inter, *Q, NULL, false);

            }
            freePoint(inter);
        }
    }else if (sR->p0->x != sR->p1->x){// left is vertical
        x_inter = sL->p0->x;
        y_inter = pR + mR * x_inter;
        if (y_inter > p->y || (y_inter == p->y && x_inter > p->x)){ // intersection happens bellow the sweep line
            Point *inter = createPoint(x_inter, y_inter, NULL);
            if ((contains(inter,sL) || equalPoint(inter, sL->p0) || equalPoint(inter, sL->p1)) && (contains(inter,sR) || equalPoint(inter, sR->p0) || equalPoint(inter, sR->p1))){
                insertPoint(Q, inter, *Q, NULL, false);
            }
            freePoint(inter);
        }
    }
}


void HandleEventPoint(dataStruct *data){
    List* L = createVoidList();
    List* C = createVoidList();
    data->RLN = createVoidList();

    findLandC(data->Tau, NULL, data->p, false, L, C, data->RLN);

    int lengthT = data->p->U->length + L->length + C->length;
    if (lengthT >= 2){// p is an intersection point
        List* concat = concatenate(data->p->U, L, C);
        insertListHeadP(data->Intersections, data->p, concat);
        freeList(concat);
    }

    //Delete segment with p as lower point from the tree
    delForL(&(data->Tau), L->head, data->p);
    freeList(L);

    //Delete and reinsert segment containing p from the tree (so they switch positions)
    delForC(&(data->Tau), C->head, data->p);
    insertForC(&(data->Tau), C->head, data->p);

    //Insert segment with p as upper point
    if (data->p->U != NULL) {
        insertForU(&(data->Tau), data->p->U->head, data->p);
    }

    // Check for new intersections
    if (data->p->U->length + C->length == 0){// p is only a lower point
        data->LM = NULL;
        data->RM = NULL;
        data->LN = NULL;
        data->RN = NULL;
        if (data->RLN->length == 2){// sl and sr exists
            findNewEvent(data->RLN->head->value, data->RLN->queue->value, data->p, &(data->Q), data);
        }
    }else{
        freeList(data->RLN);
        data->RLN = NULL;
        data->LM = NULL;
        data->RM = NULL;
        data->LN = NULL;
        data->RN = NULL;

        Segment *LM = findLeftMost(data->Tau, NULL, data->p, false);
        Segment *RM = findRightMost(data->Tau, NULL, data->p, false);
        Treeseg *LN = NULL;
        Treeseg *RN = NULL;

        if (LM != NULL) {
            data->LM  = createSegment(LM->p0, LM->p1, LM->value);
            LN = findLeftNb(data->Tau, LM, data->p, false);
        }
        if (RM != NULL){
            data->RM  = createSegment(RM->p0, RM->p1, RM->value);
            RN = findRightNb(data->Tau, RM, data->p, false);
        }

        if (LN != NULL){
            data->LN = createSegment(LN->value->p0, LN->value->p1, LN->value->value);
            findNewEvent(data->LN, data->LM, data->p, &(data->Q), data);
        }
        if (RN != NULL){
            data->RN = createSegment(RN->value->p0, RN->value->p1, RN->value->value);
            findNewEvent(data->RN, data->RM, data->p, &(data->Q), data);
        }
    }
    freeList(C);
}


bool FindIntersections(List* s, dataStruct *data){
    data->Q = NULL;
    createQ(s->head, &(data->Q));
    data->Tau = NULL;
    data->Intersections = createVoidListP();

    while((data->Q) != NULL){
        data->p = delPoint(&(data->Q));
        HandleEventPoint(data);
        if (data->Q != NULL){
            freePoint(data->p);
            freeList(data->RLN);
            freeSeg(data->LM);
            freeSeg(data->LN);
            freeSeg(data->RM);
            freeSeg(data->RN);
        }
    }
    return true;
}

bool FindIntersections2(List* s, dataStruct *data, Point* red_point){
    data->Q = NULL;
    createQ(s->head, &(data->Q));
    data->Tau = NULL;
    data->Intersections = createVoidListP();

    bool avant_dernier = false;
    while((data->Q) != NULL){
        data->p = delPoint(&(data->Q));
        HandleEventPoint(data);
        if(avant_dernier){
            return true;
        }
        if((red_point->y < data->p->y || (red_point->y == data->p->y && red_point-> x <= data->p->x))){
            avant_dernier = true;
        }
        if (data->Q != NULL){
            freePoint(data->p);
            freeList(data->RLN);
            freeSeg(data->LM);
            freeSeg(data->LN);
            freeSeg(data->RM);
            freeSeg(data->RN);
        }
    }
    return true;
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%% CONVERTERS Tab - Tree - List
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
List* fromTab2List(GLfloat coord[][2], GLsizei nPoints){
    List* segmentList = createVoidList();
    for (GLsizei i=0; i<nPoints; i+=2) {
        Point* p0 = createPoint(coord[i][0], -coord[i][1], NULL);
        Point* p1 = createPoint(coord[i+1][0], -coord[i+1][1], NULL);
        Segment *s = createSegment(p0, p1, i/2);

        insertListHead(segmentList, s);
        freePoint(p0);
        freePoint(p1);
        freeSeg(s);
    }
    return segmentList;
}

bool fromListP2Tab(ListP* list, GLfloat coord[][2]){
    if (list->head == NULL) {return false; }
    int i = 0;
    for (Listpoint* curr = list->head; curr != NULL; curr = curr->prev) {
        coord[i][0] = (GLfloat)curr->value->x;
        coord[i][1] = -(GLfloat)curr->value->y;
        i += 1;
    }
    return true;
}


bool fromTreenode2ListP(ListP* list, Treenode* tree){
    if(tree == NULL){
        return false;
    }
    if(tree->value != NULL){
        insertListHeadP(list, tree->value, NULL);
        if(tree->right != NULL){
            fromTreenode2ListP(list, tree->right);
        }
        if(tree->left != NULL){
            fromTreenode2ListP(list, tree->left);
        }
        return true;
    }else{
        return true;
    }
}

bool fromTreeseg2ListP(ListP* list, Treeseg* tree){
    if(tree == NULL){
        return false;
    }
    if(tree->value != NULL){
        insertListHeadP(list, tree->value->p0, NULL);
        insertListHeadP(list, tree->value->p1, NULL);
        if(tree->right != NULL){
            fromTreeseg2ListP(list, tree->right);
        }
        if(tree->left != NULL){
            fromTreeseg2ListP(list, tree->left);
        }
        return true;
    }else{
        return true;
    }
}

bool fromTreenode2Tab(Treenode* tree, GLfloat tab[][2]){
    ListP* list = createVoidListP();
    fromTreenode2ListP(list, tree);
    fromListP2Tab(list, tab);
    freeListP(list);
    return true;
}

bool fromTreeseg2Tab(Treeseg* tree, GLfloat tab[][2]){
    ListP* list = createVoidListP();
    fromTreeseg2ListP(list, tree);
    fromListP2Tab(list, tab);
    freeListP(list);
    return true;
}

int TreesegSize(Treeseg* tree) {
    ListP* list = createVoidListP();
    fromTreeseg2ListP(list, tree);
    int ans = list->length;
    freeListP(list);
    return ans;
}


int TreenodeSize(Treenode* tree) {
    ListP* list = createVoidListP();
    fromTreenode2ListP(list, tree);
    int ans = list->length;
    freeListP(list);
    return ans;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%  Free Data Structure
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void freeDatastruct(dataStruct *data){
    if (data != NULL){
        freeListP(data->Intersections);
        freeTreenode(data->Q);
        freeTreeseg(data->Tau);
        freePoint(data->p);
        freeSeg(data->LM);
        freeSeg(data->RM);
        freeSeg(data->RN);
        freeSeg(data->LN);
        freeList(data->RLN);
        free(data);
        data = NULL;
    }
}