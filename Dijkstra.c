#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "Dijkstra.h"

int dijkstra(pnode *head,int amount_of_Nodes,  int src, int dest);
int get_Id_by_Pos(pnode *head, int pos, int amount_of_Nodes);
int placeCalc(pnode *head, int node_id,int amount_of_Nodes);
int min(int x,int y,int w);

int dijkstra(pnode *head,int amount_of_Nodes,  int src, int dest){
    pnode sourceNode = getNode(head,src);
    pnode destinationNode = getNode(head,dest);
    if(sourceNode==NULL || destinationNode==NULL){
        return -1;
    }
    int *d = (int*)malloc(sizeof(int)*amount_of_Nodes);
    int *Queue = (int*)malloc(sizeof(int)*amount_of_Nodes);
    int start = 0,end =amount_of_Nodes-1, Min, min_id, edge_dest_id;
    if (d==NULL || Queue ==NULL)
    {
        printf("Couldn't allocate memory");
        exit(0);
    }
    int i;
    for (i = 0; i < amount_of_Nodes; i++){
        d[i] = -1;
        Queue[i] = i;
    }
    d[placeCalc(head,src,amount_of_Nodes)] = 0;
    while (start<end){
        Min = start;
        for (i = start+1; i <= end; i++){
            if(d[Queue[i]] == min(d[Queue[Min]],d[Queue[i]],0))
                Min = i;
        }
        min_id = Queue[Min];
        Queue[Min] = Queue[start];
        Queue[start] = min_id;
        start++;
        pnode minNode = getNode(head,get_Id_by_Pos(head,min_id,amount_of_Nodes));
        edge *curEdge = minNode -> edges;
        while (curEdge != NULL){
            edge_dest_id = curEdge->endpoint->node_num;
            d[placeCalc(head,edge_dest_id,amount_of_Nodes)] = min(d[placeCalc(head,edge_dest_id,amount_of_Nodes)],d[min_id],curEdge->weight);
            curEdge = curEdge-> next;
        }
    }
    int res = d[placeCalc(head,dest,amount_of_Nodes)];
    free(d);
    free(Queue);
    return res;
}

//calculate the node id by its positon in the graph
int get_Id_by_Pos(pnode *head, int pos, int amount_of_Nodes){
    int place = amount_of_Nodes-1;
    int found = 0;
    node *current = *head;
    while (current!= NULL && found == 0){
        if(place == pos) found = 1;
        else{
            place--;
            current = current -> next;
        }
    }
    return current-> node_num;
}

//calculate the place, will return -1 in case the node doesn't exist
int placeCalc(pnode *head, int node_id,int amount_of_Nodes){
    int place = amount_of_Nodes-1;
    int found = 0;
    node *current = *head;
    while (current!= NULL && found == 0){
        if(current -> node_num == node_id)
            found = 1;
        else{
            place--;
            current = current -> next;
        }
    }
    return place;
}

// get the minimum path
int min(int x,int y,int w){
    if(x==-1 && y==-1)
        return -1;
    if(x==-1)
        return y + w;
    if(y==-1)
        return x;
    if(x<=(y+w))
        return x;
    return y+w;
}
