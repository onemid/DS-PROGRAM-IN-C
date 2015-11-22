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

void DFS();
void traceRing();

int main(int argc, const char * argv[]) {
    
    int i, j;
    
    scanf("%d", &mapSize);
    
    int ringMap[mapSize][mapSize+1];
    int routeTrace[mapSize+1];
    int visited[MAX_MAP][3] = {FALSE};
    
    for (i = 1; i <= mapSize; i++) {
        for (j = 1; j <= mapSize; j++) {
            scanf("%d", &ringMap[i][j]);
        }
    }
    
    DFS(ringMap, visited, 1, 0, 0);
    
    printf("\n");
    
    return 0;
}

void DFS (int ringMap[][mapSize], int visited[][3], int start, int rank, int previousNode){
    
    int i, j;
    visited[start][0] = TRUE;
    visited[start][1] = rank;
    visited[start][2] = previousNode;
    
    printf("%3d", start);
    
    for (i = 1; i <= mapSize; i++) {
        for (j = 1; j <= mapSize; j++) {
            if (!visited[j][0] && ringMap[i][j]) {
                DFS(ringMap, visited, j, rank, start);
            }else if (visited[j][0] && ringMap[i][j] && visited[j][1] != rank){
                printf("Find Ring\n");
            }
        }
    }
    
}

void traceRing (int visited[][2]){
    
}

