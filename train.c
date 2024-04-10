/* Miron Teodor Adrian - 314CC */

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
    dummy node is head, tail is the last node and mechanic is the node
    where the mechanic stays obviously
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

void nextNode(LinkedList *list, Node **node){
    if ((*node)->next == list->head){
        (*node) = (*node)->next->next;
    } else {
        (*node) = (*node)->next;
    }
}
/*
    basic links for a double linked list
*/
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
        // links
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

    /*
        if the mechanic is in the last node then i'll simply append the 
        node to the train, otherwise i gotta make it fit in there by 
        recreating the links
    */ 
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
    /*
        if the mechanic is in the first wagon then i'll move him 
        to the last (tail) otherwise i'm just moving lil bro to his new place
    */
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
    /*
        checking where to search
    */
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
    /*
        checking where to move
    */
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
    /*
        iterating through the list and removing every node and after that
        recreating the default links
    */
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
    /*
        if the mechanic is not in the first node then i'll redo the links
        with the neighbours, otherwise only with the next node and the dummy
        node
    */
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
    /*
        searching for the first appeareance of the first word letter
        and marking the whole search with a retry in case we find a first
        matching character but the rest of them are different,
        and we didn't search the mechanic again yet we can go back
        and start fresh with another search
    */
retry:
    while (start->info != word[i]){
        /*
            if we reached the dummy node we skip it with next next
        */
        nextNode(list, &start);
        /*
            if we reached the mechanic without finding the first letter
            then the word is not found
        */
        if (start == list->mechanic){
            notFound = true;
            break;
        }
    }
    
    if (notFound){
        fprintf(file, "ERROR\n");
    } else {
        i++;
        int remainingLength = strlen(word) - 1;
        Node *firstLetter = start;

        nextNode(list, &start);
        /*
            as long as we have remaning characters we keep comparing
            them with the nodes info, if one doesnt match then we clearly
            didn't find the word so we break and try a new search if possible
        */
        while (remainingLength != 0){
            if (start->info != word[i]){
                break;
            }
            else {
                if (start != list->mechanic){
                    remainingLength--;
                    nextNode(list, &start);
                    i++;
                } else {
                    break;
                }
            }
        }
        /*
            moving the mechanic to the firstLetter of the word
        */
        if (remainingLength == 0){
            list->mechanic = firstLetter;
        } else {
            /*
                if the node we're currently at has not reached mechanic yet
                then we can try a new search and jump to the beggining
                of the search 
            */
            if (remainingLength != 0 && start != list->mechanic){
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
    /*
        pretty much the same search algorithm, i'm just seraching in a
        direction until i hit the dummy node
    */
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
        int remainingLength = lenght - 1;
        lastCharNode = start;
        if (left){
            start = start->prev;
        } else {
            start = start->next;
        }
        while (remainingLength != 0){
            if (start->info != word[i]){
                break;
            }
            else {
                if (start != list->head){
                    remainingLength--;
                    if (remainingLength == 0){
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
        if (remainingLength == 0){
            list->mechanic = lastCharNode;
        } else {
            if (remainingLength != 0 && start != list->head){
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
    /*
        checking the directions
    */
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
    
    free(list->head);
    free(list);
}