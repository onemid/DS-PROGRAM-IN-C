//
//  main.c
//  DS_HW2_HuffmanCode
//
//  Created by GONG, YI-JHONG on 2015/11/22.
//  Copyright © 2015年 GONG, YI-JHONG. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 5000
#define MAX_INPUT 5000
#define TRUE 1
#define FALSE 0

int topTree = -1, topTrace = -1;

typedef struct huffmanTree *treePtr;  //Building the Self-Reference Tree
typedef struct huffmanTree{
    treePtr leftPtr;
    treePtr rightPtr;
    int data;
}huffmanTree;

huffmanTree stackTree[MAX_STACK] = {0};
int stackTrace[MAX_STACK] = {0};



void insertTreeStack();
huffmanTree popTreeStack();

void insertTraceStack();
void popTraceStack();

int compareTree();

void huffmanProcedure();
int encodingPrintOut();

void FAIL_HANDLER();


int main(int argc, const char * argv[]) {
    
    char inputTmpLine[MAX_INPUT];
    int inputWordCount[MAX_INPUT][2];
    char *splitWord;
    int inputCount = 0;
    
    fgets(inputTmpLine, MAX_INPUT, stdin);
    splitWord = strtok(inputTmpLine, " ");
    
    while (splitWord) {
        
        inputWordCount[inputCount][0] = *splitWord;
        splitWord = strtok(NULL, " ");
        inputCount++;
        
    }
    
    inputCount=0;
    
    fgets(inputTmpLine, MAX_INPUT, stdin);
    splitWord = strtok(inputTmpLine, " ");
    
    while (splitWord) {
        
        inputWordCount[inputCount][1] = atoi(splitWord);
        splitWord = strtok(NULL, " ");
        inputCount++;
        
    }
    
    for (int i = 0 ; i<inputCount; i++) {
        huffmanTree tmp;
        tmp.data = inputWordCount[i][1];
        tmp.leftPtr = NULL;
        tmp.rightPtr = NULL;
        insertTreeStack(&tmp);
    }
    
    huffmanProcedure(inputCount);
    
    int compressionTotalBit = 0, originalTotalBit = 0;
    
    for (int i = inputCount - 1 ; i >= 0; i--) {
        
        encodingPrintOut(inputWordCount[i][1],&stackTree[0],&stackTree[0],0);
        
        printf("%c : ", inputWordCount[i][0]);
        
        compressionTotalBit += (topTrace+1)*inputWordCount[i][1];
        originalTotalBit += 8 * inputWordCount[i][1];
        
        while (topTrace >= 0) {
            popTraceStack();
        }
        
        printf("\n");
    }
    
    float compressionRatio = 1-((float)compressionTotalBit/(float)originalTotalBit);
    
    printf("Total Bits : %d\n", compressionTotalBit);
    printf("Compression Ratio : %.0f%%\n", compressionRatio*100);
    
    return 0;
}

void insertTreeStack (treePtr data){
    
    if (topTree == MAX_STACK - 1) FAIL_HANDLER(0);
    
    stackTree[++topTree] = *data;
    
}

huffmanTree popTreeStack (){
    
    if (topTree == -1) FAIL_HANDLER(1);
    
    return stackTree[topTree--];
    
}

void insertTraceStack (int data){
    
    if (topTrace == MAX_STACK - 1) FAIL_HANDLER(0);
    
    stackTrace[++topTrace] = data;
}

void popTraceStack (){
    
    if (topTrace == -1) FAIL_HANDLER(1);
    
    printf("%d",stackTrace[topTrace--]);
    
}

int compareTree (huffmanTree *ele1, huffmanTree *ele2){
    
    return ele2->data - ele1->data;
    
}

void huffmanProcedure(int inputSize){
    
    while (topTree != 0) {
        
        qsort(stackTree, inputSize--, sizeof(huffmanTree), (void*)compareTree);
        
        treePtr right, left, parent;
        
        right = malloc(sizeof(*right));
        *right = popTreeStack();
        
        left = malloc(sizeof(*left));
        *left = popTreeStack();
        
        parent = malloc(sizeof(*parent));
        parent->data = right->data + left->data;
        
        parent->leftPtr = left;
        parent->rightPtr = right;
        
        insertTreeStack(parent);
        
    }
    
}

int encodingPrintOut(int target, treePtr root, treePtr Curiosity, int encode){
    
    if (Curiosity) {
        
        if (!Curiosity->leftPtr && !Curiosity->rightPtr) {
            
            if (Curiosity->data == target) return TRUE;
            else return FALSE;
            
        }
        
        if (encodingPrintOut(target, root, Curiosity->leftPtr, 0)) {
            
            insertTraceStack(0);
            return TRUE;
            
        }else if (encodingPrintOut(target, root, Curiosity->rightPtr, 1)) {
            
            insertTraceStack(1);
            return TRUE;
            
        }
        
    }
    
    return FALSE;
}

void FAIL_HANDLER(int ERROR_TYPE){
    
    if (ERROR_TYPE == 0) {
        
        printf("ERROR: Stack is Full.\n");
        exit(EXIT_FAILURE);
        
    }else if (ERROR_TYPE == 1){
        
        printf("ERROR: Stack is Empty.\n");
        exit(EXIT_FAILURE);
        
    }
    
}