//
//  main.c
//  DS_HW2_StackTrain
//
//  Created by GONG, YI-JHONG on 2015/11/22.
//  Copyright © 2015年 GONG, YI-JHONG. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATION_CAPACITY 10
#define MAX_CARRIAGE 1000
#define TRUE 1
#define FALSE 0

int frontATrain = -1, rearATrain = -1;
int front = -1, rear = -1;
int stationTop = -1;

int station[MAX_CARRIAGE]={0}, trainA[MAX_CARRIAGE] ={0}, trainB[MAX_CARRIAGE] = {0};
int trainBChk[MAX_CARRIAGE] = {FALSE};
int stationTotalWeight = 0;

void insertTrain();
int popTrain();

int insertStation();
int popStation();

int checkLegal();

int main(int argc, const char * argv[]) {
    
    char inputTmp[2000];
    char *splitWord;
    
    int count = 0;
    
    fgets(inputTmp, 2000, stdin);
    splitWord = strtok(inputTmp, " ");
    
    while (splitWord) {
        
        trainA[++rearATrain] = atoi(splitWord);
        splitWord = strtok(NULL, " ");
        
    }
    
    count = 0;
    fgets(inputTmp, 2000, stdin);
    splitWord = strtok(inputTmp, " ");
    
    while (splitWord) {
        
        trainB[count] = atoi(splitWord);
        splitWord = strtok(NULL, " ");
        count++;
        
    }
    
    if(checkLegal(count)) printf("YES\n");
    else printf("NO\n");
    
    return 0;
}

int insertStation(int data){
    
    if (stationTotalWeight + data <= MAX_STATION_CAPACITY) {
        
        station[++stationTop] = data;
        stationTotalWeight += data;
        return TRUE;
        
    }else{
        
        return FALSE;
        
    }
    
}

int popStation(){
    
    int popTmp = station[stationTop--];
    
    stationTotalWeight -= popTmp;
    
    return popTmp;
    
}

void insertTrain(int data){
    
    trainB[++rear] = data;
    
}

int popTrain(){
    
    return trainA[++frontATrain];
    
}

int checkTrainAElement (int data){
    
    int i;
    
    for (i = frontATrain; i <= rearATrain; i++) {
        
        if (trainA[i+1] == data) return TRUE;
        
    }
    
    return FALSE;
}

int checkStationTopElement (int data){
    
    if (station[stationTop] == data) return TRUE;
    return FALSE;
    
}

int checkLegal(int count){
    
    int i = 0, buffer, signal = TRUE;
    
    for (i = 0; i < count; i++) {
        
        if (checkTrainAElement(trainB[i])) {
            
            while (1) {
                
                buffer = popTrain();
                
                if(!insertStation(buffer)){
                    
                    trainBChk[i] = FALSE;
                    return FALSE;
                    
                }
                
                if (buffer == trainB[i]) {
                    
                    trainBChk[i] = TRUE;
                    popStation();
                    break;
                    
                }
            }
            
        }else if (checkStationTopElement(trainB[i])){
            
            popStation();
            trainBChk[i] = TRUE;
            
        }else{
            
            signal = FALSE;
            return FALSE;
            
        }
        
    }
    if (signal) return TRUE;
    
    return FALSE;
}
