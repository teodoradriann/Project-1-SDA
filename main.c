/* Miron Teodor Adrian - 314CC */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "train.h"
#include "queue.h"
#define STANDARD_CMD_SIZE 101

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}



int main() {   
    FILE *inputFile;
    FILE *outputFile;
    
    LinkedList *train = createList();
    Queue *queue = createQueue();
    int n;

    char *executeCmd = NULL;
    char *cmd = malloc(STANDARD_CMD_SIZE);

    if (cmd == NULL) {
        printf("ERROR. COULD NOT ALLOCATE MEMORY FOR CMD\n");
        return 0;
    }
    
    inputFile = fopen("tema1.in", "r");
    outputFile = fopen("tema1.out", "w");

    if (inputFile == NULL){
        printf("ERROR. THE DATA FILE WAS NOT FOUND\n");
        free(cmd);
        return 0;
    }
    
    fscanf(inputFile, "%d", &n);
    fgetc(inputFile);
    
    while (n){
        if (fgets(cmd, STANDARD_CMD_SIZE, inputFile) != NULL){
            cmd[strcspn(cmd, "\n")] = '\0';
            
            if (strcmp(cmd, "SWITCH") == 0){
                switchQueueCmds(queue);
            }

            else if (strcmp(cmd, "SHOW") == 0){
                show(train, outputFile);
            } 
            
            else if (strcmp(cmd, "SHOW_CURRENT") == 0){
                showCurrent(train, outputFile);
            } 

            else if (strcmp(cmd, "EXECUTE") != 0){
                enqueue(queue, cmd);
            } else {
                if (!isEmpty(queue)){
                    executeCmd = dequeue(queue);
                    
                    if (strcmp(executeCmd, "MOVE_RIGHT") == 0 || 
                        strcmp(executeCmd, "MOVE_LEFT") == 0) {
                        moveMechanic(train, executeCmd, outputFile);
                    }

                    else if (strncmp(executeCmd, "WRITE", 5) == 0){
                        char *space = strchr(executeCmd, ' ');
                        char c = *(space + 1);
                        if (c) {
                            write(train, c);
                        }
                    }

                    else if (strcmp(executeCmd, "CLEAR_CELL") == 0){
                        clearCell(train);
                    }

                    else if (strcmp(executeCmd, "CLEAR_ALL") == 0){
                        clearAll(train);
                    }

                    else if (strncmp(executeCmd, "INSERT", 6) == 0){
                        char *space = strchr(executeCmd, ' ');
                        char c = *(space + 1);
                        
                        size_t length = space - executeCmd;
                        char *where = malloc(length + 1);
                        strncpy(where, executeCmd, length);
                        where[length] = '\0';
                        
                        insert(train, where, c, outputFile);
                        free(where);
                    }

                    else if (strncmp(executeCmd, "SEARCH_", 7) == 0){
                        char *space = strchr(executeCmd, ' ');
                        
                        size_t length = space - executeCmd;
                        char *where = malloc(length + 1);
                        strncpy(where, executeCmd, length);
                        where[length] = '\0';
                        searchDirection(train, where, space + 1, outputFile);
                        free(where);
                    }

                    else if (strncmp(executeCmd, "SEARCH", 6) == 0){
                        char *space = strchr(executeCmd, ' ');
                        search(train, space + 1, outputFile);
                    }
                    free(executeCmd);
                }

            }
            n--;
        }
    }
    
    destroyQueue(queue);
    destroyList(train);
    
    free(cmd);

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
