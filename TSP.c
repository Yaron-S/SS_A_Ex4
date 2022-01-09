#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "Dijkstra.h"

int TSP(pnode *head,int *cities, int length,int amount_of_Nodes);
int TSPalgorithm(pnode *head,int *cities,int start,int length,int amount_of_Nodes);
int* copyArray(int *arr, int remove, int length);
int dijkstra(pnode *head,int amount_of_Nodes,  int src, int dest);

int TSP(pnode *head,int *cities, int length,int amount_of_Nodes){
    int minDist = -1, i;
    if(length == 0 || length == 1) minDist = 0;
    else{
        for (i = 0; i < length; i++){
            int *copy = copyArray(cities,i,length);
            minDist = min(minDist,TSPalgorithm(head,copy,cities[i],length-1, amount_of_Nodes),0);
        }
    }
    free(cities);
    return minDist;
}

int TSPalgorithm(pnode *head,int *cities,int start,int length,int amount_of_Nodes){
    int res = -1,minDist = -1,i, path,tsp;
    if(length == 0) res = 0;
    else if(length == 1) res =  dijkstra(head,amount_of_Nodes,start,cities[0]);
    else{
        for (i = 0; i < length; i++){
            int *copy = copyArray(cities,i,length);
            path = dijkstra(head,amount_of_Nodes,start,cities[i]);
            if(path != -1){
                tsp = TSPalgorithm(head,copy,cities[i],length-1,amount_of_Nodes);
                minDist = min(minDist, tsp,path);
            }
            else{
                free(copy);
            }

        }
        res = minDist;
    }
    free(cities);
    return res;
}

// given an array and an index, returns a copy of that array without the index
int* copyArray(int *arr, int remove, int length){
    int *copy = (int*)malloc(sizeof(int)*(length-1));
    if(copy==NULL){
        printf("Couldn't allocate memory");
        exit(0);
    }
    int i,count=0;
    for (i = 0; i < length; i++){
        if(i!=remove){
            copy[count] = arr[i];
            count++;
        }
    }
    return copy;
}