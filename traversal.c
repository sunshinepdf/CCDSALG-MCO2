/**
 * CCDSALG MCO2 GROUP 24
 * Description: Implementation of graph traversal algorithms (BFS and DFS)
 * 
 * Authors:
 * Laborada, Nathan
 * Lee, Ashley Fiona
 * Villorente, Khyle Raeke
 */

#include "traversal.h"

/**
 * Performs BFS traversal and returns the sequence in an array.
 * When multiple candidates exist, visits vertex with lowest ID first.
 * 
 * @param g Pointer to the Graph structure.
 * @param startVertex Name of the starting vertex for BFS.
 * @param result Array to store the traversal sequence (vertex names).
 * @return Number of vertices in the traversal sequence.
 */
int BFSTraversal(Graph* g, const char* startVertex, char result[][MAX_NLENGTH]) {
       int startIndex = getVertexIndex(g, startVertex);
    if (startIndex == -1) {
        return 0;
    }
    
    int visited[MAX_VERTICES] = {0};
    Queue* q = createQueue();
    
    visited[startIndex] = 1;
    enqueue(q, startIndex);
    
    int resultCount = 0;
    
    while (!isEmpty(q)) {
        int currentIndex = dequeue(q); // Dequeue the next vertex to visit
        strcpy(result[resultCount], g->vertices[currentIndex].vertexName); // Store the vertex
        resultCount++;
        
        char adjacentVertices[MAX_VERTICES][MAX_NLENGTH];
        int adjacentCount = 0;

        // Gather all unvisited adjacent vertex labels
        AdjListNode* adjNode = g->vertices[currentIndex].head;
        while (adjNode != NULL) {
            int adjIndex = adjNode->vertexIndex;
            if (!visited[adjIndex]) {
                strcpy(adjacentVertices[adjacentCount], g->vertices[adjIndex].vertexName);
                adjacentCount++;
            }
            adjNode = adjNode->next;
        }

         // Sort adjacent vertex labels for lexicographic priority
        if (adjacentCount > 1) {
            quickSortVertices(adjacentVertices, 0, adjacentCount - 1);
        }

        // Enqueue unvisited adjacent vertices in sorted order
        for (int i = 0; i < adjacentCount; i++) {
            int adjIndex = getVertexIndex(g, adjacentVertices[i]);
            if (!visited[adjIndex]) {
                visited[adjIndex] = 1;
                enqueue(q, adjIndex);
            }
        }
    }
    
    freeQueue(q);
    return resultCount;
}

/**
 * Performs DFS traversal and returns the sequence in an array.
 * When multiple candidates exist, visits vertex with lowest ID first.
 * 
 * @param g Pointer to the Graph structure.
 * @param startVertex Name of the starting vertex for DFS.
 * @param result Array to store the traversal sequence (vertex names).
 * @return Number of vertices in the traversal sequence.
 */
int DFSTraversal(Graph* g, const char* startVertex, char result[][MAX_NLENGTH]) {
      int startIndex = getVertexIndex(g, startVertex);
    if (startIndex == -1) {
        return 0;
    }
    
    int visited[MAX_VERTICES] = {0};
    int resultCount = 0;

    // Recursive DFS from the start vertex
    DFSUtil(g, startIndex, visited, result, &resultCount);
    
    return resultCount; 
}