//
//  main.c
//  DS_HW2_RING
//
//  Created by GONG, YI-JHONG on 2015/11/21.
//  Copyright © 2015年 GONG, YI-JHONG. All rights reserved.
//

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_MAP 1024

int top = -1;
int mapSize = 1;

int visited[MAX_MAP] = {FALSE};
int ringMap[MAX_MAP][MAX_MAP];
int routeTrack[MAX_MAP] = {0};

int DFS();
void traceRing();
void initialize();

void addStack(int data){
    routeTrack[++top] = data;
}

int popStack(){
    return routeTrack[top--];
}

int main(int argc, const char * argv[]) {
    
    int i, j, signal = FALSE;
    
    scanf("%d", &mapSize);
    
    
    
    for (i = 1; i <= mapSize; i++) {
        for (j = 1; j <= mapSize; j++) {
            scanf("%d", &ringMap[i][j]);
        }
    }
    
    for (i = 1; i <= mapSize; i++) {
        initialize();
        if(DFS(i, i)){
            printf("\nYes\n");
            while (top >= 0) {
                printf("%d ", popStack());
            }
            printf("\n");
            signal = TRUE;
            break;
        }else{
            signal = FALSE;
        }
    }
    
    if (!signal) {
        printf("\nNo\n");
    }
    
    
    return 0;
}

int DFS (int start, int originalPoint){
    
    int j;
    visited[start] ++;
    addStack(start);
    for (j = 1; j <= mapSize; j++) {
        if (!visited[j] && ringMap[start][j]) {
            if(DFS(j, originalPoint)) return TRUE;
            else popStack();
        }else if (visited[j] && ringMap[start][j] && originalPoint == j){
            addStack(originalPoint);
            return TRUE;
        }
    }

    return FALSE;
}

void initialize(){
    int i;
    for (i = 1; i <= MAX_MAP; i++) {
        visited[i] = FALSE;
    }
}

