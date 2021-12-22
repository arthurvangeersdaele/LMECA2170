#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "geometry.h"
#include "point_list.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% CREATE A LIST NODE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Listpoint* createListpoint(Point* p){
    Listpoint* result = malloc(sizeof(Listpoint));
    if (result != NULL) {
        result->prev = NULL;
        result->next = NULL;
        result->value = createPoint(p->x, p->y, p->U);
        result->luc = NULL;
    }
    return result;
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% CREATE A LIST STRUCTURE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

ListP* createListP(Point* p){
    ListP* result = malloc(sizeof(ListP));
    if (result != NULL) {
        result->head = createListpoint(p);
        result->queue = createListpoint(p);
        result->length = 0;
    }
    return result;
}


ListP* createVoidListP(){
    ListP* result = malloc(sizeof(ListP));
    if (result != NULL) {
        result->head = NULL;
        result->queue = NULL;
        result->length = 0;
    }
    return result;
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% ADD A SEGMENT IN LIST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

bool insertListHeadP(ListP* list, Point* p, List* luc){
    if(p == NULL){
        return false;
    }
    if(list != NULL){
        if(list->head != NULL){
            if(list->length == 1){
                list->queue = list->head;
                list->head = createListpoint(p);
                list->head->luc = createVoidList();
                if (luc != NULL){
                    insertList(list->head->luc, luc->head);
                }
                list->queue->next = list->head;
                list->head->prev = list->queue;
                list->length += 1;
            }
            else{
                list->head->next = createListpoint(p);
                list->head->next->luc = createVoidList();
                if (luc != NULL){
                    insertList(list->head->next->luc, luc->head);
                }
                list->head->next->prev = list->head;
                list->head = list->head->next;
                list->length+=1;
            }
            return true;
        }
        else{
            list->head = createListpoint(p);
            list->head->luc = createVoidList();
            if (luc != NULL){
                insertList(list->head->luc, luc->head);
            }
            list->length = 1;
            return true;
        }
    }
    return false;
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% FREE LIST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

void freeListpoint(Listpoint* LS){
    if (LS == NULL){
        return;
    }
    Listpoint *tmp = LS->prev;
    freePoint(LS->value);
    freeList(LS->luc);
    free(LS);
    LS = NULL;
    while (tmp != NULL){
        Listpoint *tmp2 = tmp->prev;
        freePoint(tmp->value);
        freeList(tmp->luc);
        free(tmp);
        tmp = tmp2;
    }
}


void freeListP(ListP* L){
    if (L != NULL) {
        freeListpoint(L->head);
        //freeListpoint(L->queue);
        free(L);
        L = NULL;
    }
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% PRINT LIST FUNCTIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void printListP(ListP* list){
    if(list == NULL){
        printf("\nList is NULL\n");
        return;
    }
    else if(list->length == 0){
        printf("\nList is empty\n");
    }
    else if(list->length == 1){
        printf("\nlength = %d, <QUEUE> :[]:[", list->length);
        printPoint(list->head->value);
        printf("]:[]: <head>\n");
    }
    else {
        printf("\nlength = %d, <QUEUE> :[]:[", list->length);
        printListRecP(list->queue);
    }
}

void printListRecP(Listpoint* node){
    if(node != NULL){
        printPoint(node->value);
        printf("]:[");
        printListRecP(node->next);
    }
    else{
        printf("]: <HEAD>\n\n");
    }
}

