/**
 * CCDSALG MCO2 GROUP 24
 * Description: Implementation of helper functions for graph traversal algorithms (BFS and DFS)
 * 
 * Authors:
 * Laborada, Nathan
 * Lee, Ashley Fiona
 * Villorente, Khyle Raeke
 */

 #include "traversal-helper.h"

/**
 * Creates a new queue for BFS/DFS traversal.
 * 
 * @return Pointer to the newly created Queue.
 */
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

/**
 * Adds a vertex index to the queue.
 * 
 * @param q Pointer to the Queue.
 * @param vertexIndex Index of the vertex to add.
 */
void enqueue(Queue* q, int vertexIndex) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->vertexIndex = vertexIndex;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    
    q->rear->next = newNode;
    q->rear = newNode;
}

/**
 * Removes and returns the front vertex index from the queue.
 * 
 * @param q Pointer to the Queue.
 * @return Index of the vertex at the front of the queue, or -1 if empty.
 */
int dequeue(Queue* q) {
    if (q->front == NULL) return -1;
    
    QueueNode* temp = q->front;
    int vertexIndex = temp->vertexIndex;
    q->front = q->front->next;
    
    if (q->front == NULL) q->rear = NULL;
    
    free(temp);
    return vertexIndex;
}

/**
 * Checks if the queue is empty.
 * 
 * @param q Pointer to the Queue.
 * @return 1 if empty, 0 otherwise.
 */
int isEmpty(Queue* q) {
    return q->front == NULL;
}

/**
 * Frees the memory allocated for the queue.
 * 
 * @param q Pointer to the Queue to free.
 */
void freeQueue(Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
    free(q);
}


/**
 * Helper function for DFS traversal that stores results in an array.
 * When multiple candidates exist, visits vertex with lowest ID first.
 * 
 * @param g Pointer to the Graph structure.
 * @param vertexIndex Index of the current vertex.
 * @param visited Array to track visited vertices.
 * @param result Array to store the traversal sequence.
 * @param resultCount Pointer to the count of vertices in result.
 * @return Number of vertices visited from this call.
 */
int DFSUtil(Graph* g, int vertexIndex, int visited[], char result[][MAX_NLENGTH], int* resultCount) {
    visited[vertexIndex] = 1;
    strcpy(result[*resultCount], g->vertices[vertexIndex].vertexName);
    (*resultCount)++;
    
    char adjacentVertices[MAX_VERTICES][MAX_NLENGTH];
    int adjacentCount = 0;
    
    AdjListNode* adjNode = g->vertices[vertexIndex].head;
    while (adjNode != NULL) {
        int adjIndex = adjNode->vertexIndex;
        if (!visited[adjIndex]) {
            strcpy(adjacentVertices[adjacentCount], g->vertices[adjIndex].vertexName);
            adjacentCount++;
        }
        adjNode = adjNode->next;
    }
    
    if (adjacentCount > 1) {
        quickSortVertices(adjacentVertices, 0, adjacentCount - 1);
    }
    
    for (int i = 0; i < adjacentCount; i++) {
        int adjIndex = getVertexIndex(g, adjacentVertices[i]);
        if (!visited[adjIndex]) {
            DFSUtil(g, adjIndex, visited, result, resultCount);
        }
    }
    
    return *resultCount;
}