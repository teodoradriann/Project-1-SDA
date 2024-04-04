#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define NO_LIST_ERROR "You need to create a list first. Exiting..."
#define NODE_FAILED "Node allocation failed. Exiting..."

typedef struct Node {
    char info;
    struct Node *next;
    struct Node *prev;
} Node;
/*
    locomotiva (santinela) este head, ultimul vagon este tail 
    vagonul unde se afla mecanicul este mechanic
*/
typedef struct {
    Node* head;
    Node* tail;
    Node* mechanic;
    int size;
} LinkedList;

void checkIfListIsCreated(LinkedList *list){
    if (list == NULL) {
        printf(NO_LIST_ERROR);
        exit(0);
    }
}

void checkIfNodeIsCreated(Node *node){
    if (node == NULL){
        printf(NODE_FAILED);
        exit(0);
    }
}

void defaultLinks(LinkedList *list){
    list->head->next = list->tail;
    list->head->prev = list->tail;

    list->tail->next = list->head;
    list->tail->prev = list->head;

    list->mechanic = list->tail;

    list->head->info = '\0';
    list->tail->info = '#';

    list->size = 1;
}

LinkedList* createList() {

    LinkedList* list = malloc(sizeof(LinkedList));
    checkIfListIsCreated(list);
    
    list->head = malloc(sizeof(Node));
    checkIfNodeIsCreated(list->head);
    
    list->tail = malloc(sizeof(Node));
    checkIfNodeIsCreated(list->tail);

    defaultLinks(list);

    return list;
}

// UPDATE
void insertLeft(LinkedList *list, char c, FILE *file){
    checkIfListIsCreated(list);
    if (list->mechanic == list->head->next){
        fprintf(file, "ERROR\n");
    }
    else {
        Node *new = malloc(sizeof(Node));
        checkIfNodeIsCreated(new);
        Node *leftNode = list->mechanic->prev;

        new->info = c;

        leftNode->next = new;
        new->prev = leftNode;
        new->next = list->mechanic;
        list->mechanic->prev = new;

        list->mechanic = new;
        list->size++;
    }
}

void insertRight(LinkedList *list, char c){
    checkIfListIsCreated(list);

    Node *new = malloc(sizeof(Node));
    checkIfNodeIsCreated(new);

    new->info = c;

    if (list->mechanic == list->tail){
        new->prev = list->tail;
        new->next = list->head;

        list->tail->next = new;
        list->head->prev = new;

        list->tail = new;
        list->mechanic = new;
    } else {
        Node *rightNode = list->mechanic->next;

        rightNode->prev = new;
        new->next = rightNode;
        new->prev = list->mechanic;
        list->mechanic->next = new;
        list->mechanic = new;
    }

    
    list->size++;
}

void moveLeft(LinkedList *list){
    // daca mecanicul este in primul vagon il mut in ultimul
    // altfel il mut in stanga lui
    if (list->mechanic == list->head->next){
        list->mechanic = list->tail;
    } else {
        list->mechanic = list->mechanic->prev;
    }
}

void moveRight(LinkedList *list) {
    if (list->mechanic != list->tail) {
        list->mechanic = list->mechanic->next;
    } else {
        insertRight(list, '#');
    }
}

void insert(LinkedList *list, char *where, char c, FILE *file){
    checkIfListIsCreated(list);
    if (strcmp(where, "INSERT_LEFT") == 0){
        insertLeft(list, c, file);
    } else if (strcmp(where, "INSERT_RIGHT") == 0){
        insertRight(list, c);
    } else {
        fprintf(file, "Invalid direction.\n");
    }
}

void moveMechanic(LinkedList *list, char *where, FILE *file){
    checkIfListIsCreated(list);
    if (strcmp(where, "MOVE_LEFT") == 0){
        moveLeft(list);
    } else if (strcmp(where, "MOVE_RIGHT") == 0){
        moveRight(list);
    } else {
        fprintf(file, "\nInvalid direction.\n");
    }
}

void write(LinkedList *list, char c){
    checkIfListIsCreated(list);
    list->mechanic->info = c;
}

void clearAll(LinkedList *list) {
    checkIfListIsCreated(list);

    Node* current = list->head->next;
    Node* previous = current;
    while(current->next != list->head){
        current = current->next;
        free(previous);
        previous = current;
    }
    defaultLinks(list);
}

void clearCell(LinkedList* list){
    checkIfListIsCreated(list);

    if (list->size == 1){
        defaultLinks(list);
    }
    else if (list->mechanic != list->head->next) {
        Node *leftNode = list->mechanic->prev;
        Node *rightNode = list->mechanic->next;
        free(list->mechanic);
        list->mechanic = leftNode;
        leftNode->next = rightNode;
        rightNode->prev = leftNode;
    } else {
        Node *rightNode = list->mechanic->next;
        free(list->mechanic);
        list->head->next = rightNode;
        rightNode->prev = list->head;
        list->mechanic = list->tail;
    }
}

void show(LinkedList *list, FILE *file){
    checkIfListIsCreated(list);
    Node *current = list->head->next;
    do {
        if (current == list->mechanic) {
            fprintf(file, "|");
            fprintf(file, "%c", current->info);
            fprintf(file, "|");
        } else {
            fprintf(file, "%c", current->info);
        }
        current = current->next;
    } while (current != list->head);
    fprintf(file, "\n");
}

void showCurrent(LinkedList *list, FILE *file){
    fprintf(file, "%c\n", list->mechanic->info);
}

// SEARCH
void search(LinkedList *list, char *word, FILE *file) {
    int i = 0;
    Node *start = list->mechanic;
    bool notFound = false;
retry:
    while (start->info != word[i]){
        
        if (start->next == list->head){
            start = start->next->next;
        } else {
            start = start->next;
        }

        if (start == list->mechanic){
            notFound = true;
            break;
        }
    }
    
    if (notFound){
        fprintf(file, "ERROR\n");
    } else {
        i++;
        int remainingLenght = strlen(word) - 1;
        Node *firstLetter = start;

        if (start->next == list->head){
            start = start->next->next;
        } else {
            start = start->next;
        }

        while (remainingLenght != 0){
            if (start->info != word[i]){
                break;
            }
            else {
                if (start != list->mechanic){
                    remainingLenght--;
                    start = start->next;
                    i++;
                } else {
                    break;
                }
            }
        }
        if (remainingLenght == 0){
            list->mechanic = firstLetter;
        } else {
            if (remainingLenght != 0 && start != list->mechanic){
                i = 0;
                goto retry;
            }
            else {
                fprintf(file, "ERROR\n");
            }
        }
    }
}

void searchDir(LinkedList *list, char *word, FILE *file, char* where){
    int i = 0;
    Node *start = list->mechanic;
    Node *lastCharNode = NULL;
    bool notFound = false;
    bool left = false;
    int lenght = strlen(word);
    if (strcmp(where, "SEARCH_LEFT") == 0){
        left = true;
    } else {
        left = false;
    }
retry:
    while (start->info != word[i]){
        if (left){
            start = start->prev;
        } else {
            start = start->next;
        }
        if (start == list->head){
            notFound = true;
            break;
        }
    }
    if (notFound) {
        fprintf(file, "ERROR\n");
    } else {
        i++;
        int remainingLenght = lenght - 1;
        lastCharNode = start;
        if (left){
            start = start->prev;
        } else {
            start = start->next;
        }
        while (remainingLenght != 0){
            if (start->info != word[i]){
                break;
            }
            else {
                if (start != list->head){
                    remainingLenght--;
                    if (remainingLenght == 0){
                        lastCharNode = start;
                        break;
                    }
                    if (left){
                        start = start->prev;
                    } else {
                        start = start->next;
                    }
                    i++;
                } else {
                    break;
                }
            }
        }
        if (remainingLenght == 0){
            list->mechanic = lastCharNode;
        } else {
            if (remainingLenght != 0 && start != list->head){
                i = 0;
                goto retry;
            } else {
                fprintf(file, "ERROR\n");
            }
        }
    }
}

void searchDirection(LinkedList *list, char *where, char *what, FILE *file){
    checkIfListIsCreated(list);
    if (strcmp(where, "SEARCH_LEFT") == 0){
        searchDir(list, what, file, where);
    } else if (strcmp(where, "SEARCH_RIGHT") == 0){
        searchDir(list, what, file, where);
    } else {
        fprintf(file, "Invalid direction.\n");
    }
}

void destroyList(LinkedList *list){
    checkIfListIsCreated(list);

    Node* current = list->head->next;
    while (current != list->head) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    
    free(list);
}