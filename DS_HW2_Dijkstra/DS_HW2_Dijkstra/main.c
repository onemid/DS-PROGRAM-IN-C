//
//  main.c
//  DS_HW2_Dijkstra
//
//  Created by GONG, YI-JHONG on 2015/11/20.
//  Copyright © 2015年 GONG, YI-JHONG. All rights reserved.
//  NOTE: There is a known issue for reading large input.

#include <stdio.h>

#define MAX_GRAPH 2048
#define INF MAX_GRAPH * MAX_GRAPH
#define TRUE 1
#define FALSE 0

int cost[MAX_GRAPH][MAX_GRAPH];
//this table is recorded for node-to-node cost.
int distance[MAX_GRAPH][2] = {0};
//the first row records the accumulate distance; the second row records the next node
short int found[MAX_GRAPH] = {0};
//table for marking which point is visited before.
int route[MAX_GRAPH];
int top = MAX_GRAPH;

void dijkstra(int start, int end, int maxVertex){
    
    int nextNode = start, tmpNextNode = start, i;
    int minCost;
    int allVisited = FALSE;
    
    distance[start][0] = 0;
    found[start] = TRUE;
    
    while (!allVisited) {
        
        minCost = INF;
        allVisited = TRUE;
        
        for (i = 0; i <= maxVertex; i++) {
            
            if (cost[nextNode][i] != INF && !found[i] && distance[i][0] > distance[nextNode][0] + cost[nextNode][i]) {
                distance[i][0] = distance[nextNode][0] + cost[nextNode][i];
                distance[i][1] = nextNode;
            }
            
            if (cost[nextNode][i] != INF && !found[i]) {
                if (minCost > distance[i][0]) {
                    minCost = distance[i][0];
                    tmpNextNode = i;
                }
                allVisited = FALSE;
            }
            
        }
        
        found[tmpNextNode] = TRUE;
        nextNode = tmpNextNode;
        
    }
    
    return;
}

void traceRoute(int start, int end){
    
    int nextNode = end, i;
    
    route[--top] = end;
    
    while (nextNode != start) {
        route[--top] = distance[nextNode][1];
        nextNode = distance[nextNode][1];
    }
    
    for (i = 0; i < MAX_GRAPH - 1; i++) {
        if (route[i] != -1) {
            printf("%d ", route[i]);
        }
    }
    
    printf("%d", route[MAX_GRAPH - 1]);
    printf("\n%d\n", distance[end][0]);
    
}

void initialize(){
    int i, j;
    for (i = 0; i < MAX_GRAPH; i++) {
        distance[i][0] = INF;
        distance[i][1] = FALSE;
        found[i] = FALSE;
        route[i] = -1;
        for (j = 0; j < MAX_GRAPH; j++) {
            cost[i][j] = INF;
            
        }
    }
    return;
}



int main(int argc, char *argv[]) {
    
    FILE *inputFile;
    int count, i;
    int beginNode, endNode, start, end, costValue, maxVertex = 0;
    
    inputFile = fopen("map.txt", "r");
    initialize();
    
    fscanf(inputFile,"%d", &count);
    fflush(stdin);
    
    
    for (i = 0; i < count; i++){
        fscanf(inputFile,"%d%d%d", &beginNode, &endNode, &costValue);
        if (maxVertex < beginNode) {
            maxVertex = beginNode;
        }
        cost[beginNode][endNode] = costValue;
        
    }
    
    fscanf(inputFile,"%d%d", &start, &end);
    
    dijkstra(start, end, maxVertex);
    traceRoute(start, end);
    
    return 0;
}