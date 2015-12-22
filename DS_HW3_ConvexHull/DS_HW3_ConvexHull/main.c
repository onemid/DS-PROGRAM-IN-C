//
//  main.c
//  DS_HW3_ConvexHull
//
//  Created by GONG, YI-JHONG on 2015/12/21.
//  Copyright © 2015年 GONG, YI-JHONG. All rights reserved.
//

#include <stdio.h>

typedef struct point {
    int x, y;
}point;

point convexSet[100000];
int top = -1;

int orientation(point p, point q, point r){
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    
    if (!val) return 0;
    return (val > 0) ? 1 : 2;
}

void convexHull (point pointSet[], int n){
    if (n < 3) return;
    
    int left = 0;
    for (int i = 1; i < n; i++) {
        if (pointSet[i].x < pointSet[left].x) {
            left = i;
        }
    }
    int p = left, q;
    do{
        top++;
        convexSet[top].x = pointSet[p].x;
        convexSet[top].y = pointSet[p].y;
        
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientation(pointSet[p], pointSet[i], pointSet[q]) == 2) {
                q = i;
            }
        }
        p = q;
    }while (p != left);
    
    for (int i = 0; i <= top; i++) {
        printf("%d, %d\n", convexSet[i].x, convexSet[i].y);
    }
}

int main(int argc, const char * argv[]) {
    point pointSet[10000];
    int count = 0;
    
    while (1) {
        scanf("%d %d", &pointSet[count].x, &pointSet[count].y);
        if (!pointSet[count].x && !pointSet[count].y) {
            break;
        }
        count++;
    }
    
    convexHull(pointSet, count);
    
    return 0;
}
