#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define NODE_FAILED "Node allocation failed. Exiting..."

typedef struct QueueNode {
    char *info;
    struct QueueNode *next;
    struct QueueNode *prev;
}QueueNode;

typedef struct {
    int size;
    QueueNode *head;
    QueueNode *tail;
}Queue;

void checkIfQueueNodeIsCreated(QueueNode *node){
    if (node == NULL){
        printf(NODE_FAILED);
        exit(0);
    }
}

void checkIfQueueExists(Queue *queue){
    if (queue == NULL){
        return;
    }
}

Queue* createQueue(){
    Queue* queue = malloc(sizeof(Queue));
    checkIfQueueExists(queue);
    
    queue->head = NULL;
    queue->tail = NULL;

    queue->size = 0;
    return queue;
}

int isEmpty(Queue *queue){
    checkIfQueueExists(queue);
    if (queue->size == 0){
        return 1;
    } else return 0;
}

void enqueue(Queue *queue, char *command){
    checkIfQueueExists(queue);
    
    QueueNode *new = malloc(sizeof(QueueNode));
    checkIfQueueNodeIsCreated(new);
    
    new->info = malloc(strlen(command) + 1);
    strcpy(new->info, command);
    new->next = NULL;
    
    if (isEmpty(queue)){
        new->prev = NULL;
        queue->head = new;
        queue->tail = new;
    } else {
        new->prev = queue->tail;
        queue->tail->next = new;
        queue->tail = new;
    }
    queue->size++;
}

char *dequeue(Queue *queue){
    checkIfQueueExists(queue);

    if (isEmpty(queue)){
        return NULL;
    }
    else {
        QueueNode *returnNode = queue->head;
        // copiez informatia din nod intr-o alta zona de memorie pentru
        // a putea elibera coada 
        
        char *info = malloc(strlen(returnNode->info) + 1);
        if (info == NULL){
            return NULL;
        }
        strcpy(info, returnNode->info);
        
        // actualizez noul prim element al cozii
        queue->head = returnNode->next;
        queue->size--;
        
        //eliberez vechiul element
        free(returnNode->info);
        free(returnNode);
        
        return info;
    }
}

void swapInfo(char **firstInfo, char **secondInfo){
    char *aux = *firstInfo;
    *firstInfo = *secondInfo;
    *secondInfo = aux;
}

void switchQueueCmds(Queue *queue){
    checkIfQueueExists(queue);
    if (isEmpty(queue)){
        return;
    } else {
        int nrInterschimbari = 0;
        QueueNode *first = queue->head;
        QueueNode *last = queue->tail;
        while (nrInterschimbari != queue->size / 2){
            swapInfo(&(first->info), &(last->info));
            nrInterschimbari++;
            first = first->next;
            last = last->prev;
        }
    }
}

void destroyQueue(Queue *queue) {
    checkIfQueueExists(queue);

    while (queue->head != NULL) {
        QueueNode *current = queue->head;
        queue->head = queue->head->next;
        free(current->info);
        free(current); 
    }
    free(queue);
}

void printQueue(Queue *queue){
    checkIfQueueExists(queue);
    QueueNode *current = queue->head;
    while (current != NULL){
        printf("%s", current->info);
        current = current->next;
    }
    printf("\n");
}