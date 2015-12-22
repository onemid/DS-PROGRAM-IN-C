//
//  main.c
//  DS_HW3_MergSort
//
//  Created by GONG, YI-JHONG on 2015/12/21.
//  Copyright © 2015年 GONG, YI-JHONG. All rights reserved.
//

#include <stdio.h>

void MergeSort(int unsortArray[], int workingArray[], int n);
void SplitMerge(int unsortArray[], int iBegin, int iEnd, int workingArray[]);
void Merge(int unsortArray[], int iBegin, int iMiddle, int iEnd, int workingArray[]);
void CopyArray(int workingArray[], int iBegin, int iEnd, int unsortArray[]);

int main(int argc, const char * argv[]) {
    int input[100000]={0}, inputB[100000]={0}, inputNum = 0;
    
    while (1) {
        scanf("%d", &input[inputNum]);
        if (input[inputNum] == -1) {
            break;
        }
        inputNum++;
    }
    
    MergeSort(input, inputB, inputNum);
    
    int middleNum = (inputNum % 2) ? input[(inputNum-1)/2] : (input[inputNum-1] + input[inputNum]) / 2;
    
    //printf("Min= %d, Mid= %d, Max= %d\n", input[0], middleNum, input[inputNum-1]);
    printf("%d\n", (input[0] + middleNum + input[inputNum-1])/3);
    
    return 0;
}


void MergeSort(int unsortArray[], int workingArray[], int n){
    SplitMerge(unsortArray, 0, n, workingArray);
}

void SplitMerge(int unsortArray[], int iBegin, int iEnd, int workingArray[]){
    if (iEnd - iBegin < 2) {    //if run size == 1
        return;
    }
    int iMiddle = (iEnd + iBegin) / 2;
    SplitMerge(unsortArray, iBegin, iMiddle, workingArray);
    SplitMerge(unsortArray, iMiddle, iEnd, workingArray);
    Merge(unsortArray, iBegin, iMiddle, iEnd, workingArray);
    CopyArray(workingArray, iBegin, iEnd, unsortArray);
    
}

void Merge(int unsortArray[], int iBegin, int iMiddle, int iEnd, int workingArray[]){
    int i = iBegin, j = iMiddle, k;
    
    for (k = iBegin; k < iEnd; k++) {
        if(i < iMiddle && (j >= iEnd || unsortArray[i] <= unsortArray[j])){
            workingArray[k] = unsortArray[i];
            i++;
        }else{
            workingArray[k] = unsortArray[j];
            j++;
        }
    }
}
void CopyArray(int workingArray[], int iBegin, int iEnd, int unsortArray[]){
    int k;
    for (k = iBegin; k < iEnd; k++) {
        unsortArray[k] = workingArray[k];
    }
}