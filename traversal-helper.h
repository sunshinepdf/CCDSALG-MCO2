/**
 * CCDSALG MCO2 GROUP 24
 * Description: Implementation of helper functions for graph traversal algorithms (BFS and DFS)
 * 
 * Authors:
 * Laborada, Nathan
 * Lee, Ashley Fiona
 * Villorente, Khyle Raeke
 */

#ifndef TRAVERSAL_HELPER_H
#define TRAVERSAL_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "IO-helper.h"

typedef struct QueueNode {
    int vertexIndex;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue();
void enqueue(Queue* q, int vertexIndex);
int dequeue(Queue* q);
int isEmpty(Queue* q);
void freeQueue(Queue* q);
int DFSUtil(Graph* g, int vertexIndex, int visited[], char result[][MAX_NLENGTH], int* resultCount);

#endif
