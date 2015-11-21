//
//  main.c
//  DS_HW2_DFS
//
//  Created by GONG, YI-JHONG on 2015/11/21.
//  Copyright © 2015年 GONG, YI-JHONG. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 2048
#define TRUE 1
#define FALSE 0

/* CONSTRUCT THE SELF-REFERENCE LIST */

typedef struct list *listPtr;
typedef struct list{
    int nodeNum;
    listPtr nextPtr;
}list;

list adjList[MAX_VERTEX];
    // Construnt the adjacency list head

int strengthList[MAX_VERTEX] = {FALSE};
    // Build the strength list for each node

int visited[MAX_VERTEX] = {FALSE};
    // Make a list for record each node visiting

int currentStrength, neededStrenght, road, nodeCount;
int win = 0, lose = 0;


/* FUNCTION INIT. */

void addNode ();
void DFS();
void initialize();

int main(int argc, const char * argv[]) {
    
    int i, parent, child;
    
    initialize();
    
    scanf("%d%d%d%d", &nodeCount, &road, &currentStrength, &neededStrenght);
    
    for (i = 0; i < nodeCount; i++) {
        scanf("%d", &strengthList[i]);
    }
    
    for (i = 0; i < road; i++) {
        scanf("%d%d", &parent, &child);
        addNode(parent, child);
    }
    
    DFS(0);
    
    printf("\n%d %d %d\n", lose, win, currentStrength);
    
    return 0;
}

/* FUNCTION OF ADD ADJACENCY LIST */
/* DIFFERENT FROM NORMAL ADDING, THIS FUNCTION ADD EACH NODE TO ITS TAIL. */

void addNode (int adjListLoc, int nodeNum){
    
    listPtr tmp = malloc(sizeof(*tmp));
    tmp->nodeNum = nodeNum;
    // Mallocating and writing the data to listPtr tmp
    
    listPtr latestNode = &adjList[adjListLoc];
    // Get the head memory location
    
    while (latestNode->nextPtr) {
        latestNode = latestNode->nextPtr;
    }
    // Using iteration to find the latest node
    
    tmp->nextPtr = latestNode->nextPtr;
    latestNode->nextPtr = tmp;
    // Put the tmp to the latest node.
}

/* FUNCTION OF DISCOVERING THE GRAPH BY DFS RECURSIVE */

void DFS(int start){
    
    listPtr w;
    visited[start] = TRUE;
    // Initializing the pointer and setting current node is just visited
    
    if (currentStrength > strengthList[start]) {
        
        win++;
        
    }else{
        
        lose++;
        return;
        
    }
    // If current strength is larger than the strength of current node, win once.
    // O.W., lose times add and stop discovering.
    
    for (w = &adjList[start]; w; w = w->nextPtr) {
        
        if (!visited[w->nodeNum] && currentStrength < neededStrenght && currentStrength > strengthList[start]){
            
            currentStrength += strengthList[start];
            DFS(w->nodeNum);
            
        }
        
    }
    // Using loop to discovering the adjList; if any adjList is not visited and
    // current strength does not meet the assigned strength and
    // current strength is larger than the strength of current node
    // DFS the node, and add the currentStrength.
}

/* FUNCTION OF INITIALIZING THE ADJLIST */

void initialize(){
    int i;
    for (i = 0; i < MAX_VERTEX; i++) {
        adjList[i].nextPtr = NULL;
    }
}
