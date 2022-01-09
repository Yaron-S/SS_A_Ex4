#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "Dijkstra.h"
#include "TSP.c"

int main(int argc, char const *argv[]){
    pnode head = NULL;
    char input;
    int node_id, num_of_Nodes, dest, weight;
    int res, i, city, num_of_cities;

    if(scanf("%c",&input)!=EOF){
        while (input == 'A' || input == 'B' || input =='D' || input=='S'|| input == 'T'){
            if (input == 'A'){
                scanf("%d",&num_of_Nodes);
                build_graph_cmd(&head,num_of_Nodes);
                scanf("%s",&input);
                while (input == 'n'){
                    scanf("%d",&node_id);
                    pnode currentNode = getNode(&head,node_id);
                    while(scanf("%d",&dest) == 1){
                        scanf("%d",&weight);
                        addEdge(currentNode,dest,weight,&head);
                    }
                    if(scanf("%c",&input)==EOF) input = 'N';
                }
            }
            if (input == 'B'){
                scanf("%d",&node_id);
                pnode currentNode = getNode(&head,node_id);
                if(currentNode != NULL){
                    while (currentNode->edges != NULL) removeEdge(currentNode);
                }
                else{
                    add_node(&head,node_id);
                    currentNode = getNode(&head,node_id);
                    num_of_Nodes++;
                }
                while(scanf("%d",&dest) == 1){
                    scanf("%d",&weight);
                    addEdge(currentNode,dest,weight,&head);
                }
                if(scanf("%c",&input)==EOF) input = 'N';
                if(input == ' '){
                    if(scanf("%c",&input)==EOF) input = 'N';
                }
            }
            if (input == 'D'){
                scanf("%d",&node_id);
                node *count = head;
                while (count != NULL){
                    removeEdge2(count, node_id);
                    count = count->next;
                }
                removeNode(&head,node_id);
                num_of_Nodes--;
                if(scanf("%c",&input)==EOF) input = 'N';
                if(input == ' '){
                    if(scanf("%c",&input)==EOF) input = 'N';
                }
            }
            if (input == 'S'){
                scanf("%d",&node_id);
                scanf("%d",&dest);
                res = dijkstra(&head, num_of_Nodes,node_id,dest);
                printf("Dijsktra shortest path: %d \n",res);
                if(scanf("%c",&input)==EOF) input = 'N';
                if(input == ' '){
                    if(scanf("%c",&input)==EOF) input = 'N';
                }
            }
            if (input == 'T') {
                scanf("%d",&num_of_cities);
                int *cities = (int*)malloc(sizeof(int)*num_of_cities);
                if(cities==NULL){
                    printf("Couldn't allocate memory");
                    exit(0);
                }
                for (i = 0; i < num_of_cities; i++){
                    scanf("%d",&city);
                    cities[i] = city;
                }
                res = TSP(&head,cities,num_of_cities, num_of_Nodes);
                printf("TSP shortest path: %d \n",res);
                if(scanf("%c",&input)==EOF) input = 'N';
                if(input == ' '){
                    if(scanf("%c",&input)==EOF) input = 'N';
                }
            }
        }
    }
    removeGraph(&head);
    return 0;
}