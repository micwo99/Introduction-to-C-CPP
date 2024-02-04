#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ex2.h"

#define DOUBLE_2_FORMAT "%.2lf"
#define ARGC_ERROR_MSG "ERROR: Wrong number of arguments.\nUsage: main <path to file>\n"
#define POINTER_ERROR_MSG "ERROR: Invalid pointer"
#define MAX_lINE_LENGTH 1024
#define FILE_NOT_FOUND_ERR "ERROR: File not found!\n"
#define DELIMITERS " ,"

Node *NewNode(int *data, int len){
    Node *node =malloc(sizeof(Node));
    if(!node){
        return NULL;
    }
    node -> data = data;
    node -> next = NULL;
    node -> prev = NULL;
    node ->len = len;
    return node;
}

LinkedList *NewLinkedList(){
    return calloc(1,sizeof(struct LinkedList));
}

void AddToStartLinkedList(LinkedList *const list, Node *const node){
    if (!list || !node) {
        fprintf(stderr, POINTER_ERROR_MSG);
        return;
    }
    if(list->head == NULL){
        list->head=node;
        node->prev= NULL;
        node->next = NULL;
        list->tail= node;
    }

    else{
        list->head->prev = node;
        node->next = list->head;
        node->prev = NULL;
        list->head =node;
    }


}

void AddToEndLinkedList(LinkedList *const list, Node *const node) {
    if (!list || !node) {
        fprintf(stderr, POINTER_ERROR_MSG);
        return;
    }
    if(list->head == NULL){
        list->head = node;
        list->tail = node;
        node->prev= NULL;
        node->next = NULL;
    }
    else{

        list->tail->next=node;
        node->prev = list->tail;
        node->next= NULL;
        list->tail = node;
    }


}

void RemoveNode(LinkedList *const list, Node *const node) {
    if (!list) {
        fprintf(stderr, POINTER_ERROR_MSG);
        return;
    }
    Node* curr_node = list->head;

    if (!curr_node){
        fprintf(stderr, POINTER_ERROR_MSG);
        return;
    }
    else if (list->head->next== NULL && list->head->prev== NULL){
        list->head= NULL;
        list->tail= NULL;
    }
    else if (curr_node == node) {
        Node* tmp =curr_node->next;
        tmp->prev = NULL;
        list->head = tmp;
        free(curr_node);
    }
    else if (list->tail == node){
        Node* tmp = list->tail->prev;
        tmp->next = NULL;
        list->tail = tmp;
        free(node);
    }
    else {
        while(curr_node){
            if(curr_node == node){
                Node* tmp1 = curr_node->next;
                Node* tmp2 = curr_node->prev;
                tmp2->next = tmp1;
                tmp1->prev = tmp2;
                free(node);
                break;
            }
            curr_node = curr_node->next;
        }
    }
}

void FreeLinkedList(LinkedList *const list){
    if (!list){
        fprintf(stderr, POINTER_ERROR_MSG);
        return;
    }
    Node* curNode = list->head;
    Node* tmp= NULL;
    while (curNode){
        tmp = curNode->next;
        free(curNode->data);
        free (curNode);
        curNode = tmp;
    }
    free(list);

}

int CalculateLenList(LinkedList *const list){
    Node* curr = list->head;
    int count = 0;
    while(curr){
        if(curr->data != NULL){
            count += 1;
        }
        curr = curr->next;
    }
    return count;
}

double NodeAverage(Node *node ){
    double sum=0;
    for( int i=0; i<node->len; i++){
        if (node->data !=NULL){
            sum += node->data[i];
        }
    }
    double average = sum/ node->len;
    return average;
}

double *GetAverages(LinkedList *const list, size_t *const num_elements_in_returned_array){
    if(!list){
        fprintf(stderr, POINTER_ERROR_MSG);
        return NULL;
    }
    if(!num_elements_in_returned_array){
        fprintf(stderr, POINTER_ERROR_MSG);
        return NULL;
    }

    *num_elements_in_returned_array=0;
    int  node_in_list = CalculateLenList(list);
    double* array= malloc(sizeof(double)*node_in_list);
    Node* curr = list->head;
    int i =0;
    while (curr){
        if(curr->data !=NULL){
            double node_average= NodeAverage(curr);
            array[i] = node_average;
            i+=1;
            *num_elements_in_returned_array +=1;
        }
        curr = curr->next;
   }
   return array;


}

LinkedList *ParseLinkedList(const char *const filename) {
    if (!filename) {
        fprintf(stderr, POINTER_ERROR_MSG);
        return NULL;
    }
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, FILE_NOT_FOUND_ERR);
        return NULL;
    }

    LinkedList *list = NewLinkedList();
    char buffer[MAX_lINE_LENGTH], *line = NULL;
    while (fgets(buffer, MAX_lINE_LENGTH, file)) {
        line = strtok(buffer, DELIMITERS);
        if (strcmp(line, "s") == 0) {

            int *array = malloc(sizeof(int));
            int i = 0;

            while ((line = strtok(NULL, DELIMITERS))) {
                int *tmp;
                tmp = realloc(array, sizeof(int) * (1 + i));
                if (!tmp) {
                    free(array);
                    array = NULL;
                }

                array = tmp;
                char *endPtr;
                int num = strtol(line, &endPtr, 10);
                array[i] = num;
                i += 1;
            }
            Node *node = NewNode(array, i);
            AddToStartLinkedList(list, node);
        } else if (strcmp(line, "e") == 0) {

            int *array = malloc(sizeof(int));
            int i = 0;

            while ((line = strtok(NULL, DELIMITERS))) {
                int *tmp;
                tmp = realloc(array, sizeof(int) * (1 + i));
                if (!tmp) {
                    free(array);
                    array = NULL;
                }

                array = tmp;
                char *endPtr;
                int num = strtol(line, &endPtr, 10);
                array[i] = num;
                i += 1;

            }

            Node *node = NewNode(array, i);
            AddToEndLinkedList(list, node);
        }
    }
    fclose(file);
    return list;
}


