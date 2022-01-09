#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

//Build a new graph with the given amount of nodes
void build_graph_cmd(pnode *head, int num_of_nodes){
    removeGraph(head);
    int i;
    for (i = 0; i < num_of_nodes; i++)
        add_node(head,i);
}

void printGraph_cmd(pnode head){
    node *current = head;
    while(current != NULL){
        printf("Id: %d, egdes{",current->node_num);
        edge *cur = current -> edges;
        while(cur != NULL){
            printf("d:%d w:%d, ",cur -> endpoint -> node_num,cur -> weight);
            cur = cur->next;
        }
        printf("}\n");
        current = current->next;
    }
}

void add_node(pnode *head, int node_id){
    pnode newNode = (pnode)malloc(sizeof(node));
    newNode -> node_num = node_id;
    newNode -> edges = NULL;
    newNode -> next = *head;
    *head = newNode;
}

pnode getNode(pnode *head, int node_id){
    node *current = *head;
    while (current != NULL) {
        if (current -> node_num == node_id) return current;
        current = current -> next;
    }
    return NULL;
}

void addEdge(pnode node, int dest, int w, pnode *head){
    pedge newEdge = (pedge)malloc(sizeof(edge));
    newEdge -> weight = w;
    newEdge -> endpoint = getNode(head,dest);
    newEdge -> next = node -> edges;
    node -> edges = newEdge;
}

void removeGraph(pnode *head){
    while (*head != NULL) removeNode(head,(*head) -> node_num);
}

void removeNode(pnode *head, int node_id){
    if( *head == NULL) return;
    node *current = *head;
    node **prev = head;
    int found = 0;
    while (current != NULL && found == 0) {
        if (current -> node_num == node_id) {
            *prev = current -> next;
            found = 1;
        }
        else {
            prev = &(current->next);
            current = current->next;
        }
    }
    if(current != NULL) {
        while (current->edges != NULL)
            removeEdge(current);
        free(current);
    }
}

void removeEdgeFromNode(pnode node){
    edge *newEdge = (node->edges);
    if(newEdge != NULL){
        node -> edges = newEdge -> next;
        free(newEdge);
    }
}

void removeEdgeByDest(pnode node,int node_id){
    edge *newEdge = (node->edges);
    edge **prev = &(node->edges);
    int found = 0;
    while(newEdge != NULL && found == 0){
        if(newEdge -> endpoint -> node_num == node_id){
            *prev = newEdge->next;
            found = 1;
        }
        else{
            prev = &(newEdge->next);
            newEdge = newEdge -> next;
        };
    }
    if(found==1){
        free(newEdge);
    }
}