#ifndef TRAIN_H
#define TRAIN_H

typedef struct Node {
    char info;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    Node* mechanic;
    int size;
} LinkedList;

LinkedList* createList();
void checkIfNodeIsCreated(Node *node);

// UPDATE METHODS
void clearAll(LinkedList *list);
void clearCell(LinkedList* list);

void moveMechanic(LinkedList *list, char *where, FILE *file);
void insert(LinkedList *list, char *where, char c, FILE *file);

// de sters
void insertRight(LinkedList *list, char c);

void write(LinkedList *list, char c);

// SEARCH METHODS
void search(LinkedList *list, char *word, FILE *file);
void searchLeft(LinkedList *list, char *word, FILE *file);
void searchRight(LinkedList *list, char *word, FILE *file);
void searchDirection(LinkedList *list, char *where, char *what, FILE *file);

// QUERY METHODS
void show(LinkedList *list, FILE *file);
void showCurrent(LinkedList *list, FILE *file);

void destroyList(LinkedList *list);

#endif