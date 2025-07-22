/**
 * CCDSALG MCO2 GROUP 24
 * Description: design and implement an undirected graph 
 * representation of relationships among members of a Social Networking Site (SNS)
 * and  implement graph traversal algorithms (BFS and DFS).
 * 
 * Authors:
 * Laborada, Nathan
 * Lee, Ashley Fiona
 * Villorente, Khyle Raeke
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

/**
 * To create a new adjacency list node.
 * @param index points to the index of the node.
 * @return a pointer to the newly created AdjListNode.
 */
AdjListNode* createAdjListNode(int index) {
    AdjListNode* node = (AdjListNode*)malloc(sizeof(AdjListNode));
    node->vertexIndex = index;
    node->next = NULL;
    return node;
}

/**
 * Finds the index of a vertex by its label. Adds vertex if not found.
 * 
 * @param g pointer to the graph structure.
 * @param label the name of the vertex.
 * @return the index of the vertex in the graph's array.
 */
int getVertexIndex(Graph* g, const char* label) {
    for (int i = 0; i < g->numVertices; i++) {
        if (strcmp(g->vertices[i].vertexName, label) == 0)
            return i;
    }
    
    if (g->numVertices < MAX_VERTICES) {
        strcpy(g->vertices[g->numVertices].vertexName, label);
        g->vertices[g->numVertices].head = NULL;
        return g->numVertices++; // If not found, add new vertex
    }
    return -1;  // Max vertices reached
}

/**
 * Initializes the graph structure and sets number of vertices to 0 and all adjacency list heads to NULL.
 * 
 * @param g Pointer to the Graph structure to initialize.
 */
void initializeGraph(Graph* g) {
    g->numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->vertices[i].vertexName[0] = '\0';   // Empty name
        g->vertices[i].head = NULL;            // No adjacent nodes
    }
}

/**
 * Adds an undirected edge between two vertices in the graph.
 * Since the graph is undirected, both adjacency lists are updated.
 * 
 * @param g Pointer to the Graph.
 * @param from Name of the first vertex.
 * @param to Name of the second vertex.
 */
void addEdge(Graph* g, const char* from, const char* to) {
    int fromIdx = getVertexIndex(g, from);
    int toIdx = getVertexIndex(g, to);

    if (fromIdx == -1 || toIdx == -1) return;

    // Add edge to both directions
    AdjListNode* node1 = createAdjListNode(toIdx);
    node1->next = g->vertices[fromIdx].head;
    g->vertices[fromIdx].head = node1;

    AdjListNode* node2 = createAdjListNode(fromIdx);
    node2->next = g->vertices[toIdx].head;
    g->vertices[toIdx].head = node2;
}

