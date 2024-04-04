#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode {
    char *info;
    struct QueueNode *next;
    struct QueueNode *prev;
} QueueNode;

typedef struct {
    int size;
    QueueNode *head;
    QueueNode *tail;
}Queue;

Queue* createQueue();
int isEmpty(Queue *queue);
void enqueue(Queue *queue, char *command);
char *dequeue(Queue *queue);
void switchQueueCmds(Queue *queue);
void printQueue(Queue *queue);
void destroyQueue(Queue *queue);

#endif