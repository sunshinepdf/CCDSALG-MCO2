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
 * Prevents duplicate edges by checking before adding.
 * Ensures the 'from' vertex is added before the 'to' vertex to preserve input order.
 * 
 * @param g Pointer to the Graph.
 * @param from Name of the first vertex.
 * @param to Name of the second vertex.
 */
void addEdge(Graph* g, const char* from, const char* to) {
    // Ensure 'from' vertex is added first to preserve input file order
    int fromIdx = getVertexIndex(g, from);
    if (fromIdx == -1) return;
    
    // Then add 'to' vertex
    int toIdx = getVertexIndex(g, to);
    if (toIdx == -1) return;
    
    // Check if edge already exists (from -> to)
    AdjListNode* current = g->vertices[fromIdx].head;
    while (current != NULL) {
        if (current->vertexIndex == toIdx) {
            return; // Edge already exists, don't add again
        }
        current = current->next;
    }

    // Add edge from -> to (append to end to preserve input order)
    AdjListNode* node1 = createAdjListNode(toIdx);
    node1->next = NULL;
    
    if (g->vertices[fromIdx].head == NULL) {
        g->vertices[fromIdx].head = node1;
    } else {
        AdjListNode* temp = g->vertices[fromIdx].head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node1;
    }

    // Check if reverse edge already exists (to -> from)
    current = g->vertices[toIdx].head;
    while (current != NULL) {
        if (current->vertexIndex == fromIdx) {
            return; // Reverse edge already exists, don't add again
        }
        current = current->next;
    }

    // Add reverse edge to -> from (append to end to preserve input order)
    AdjListNode* node2 = createAdjListNode(fromIdx);
    node2->next = NULL;
    
    if (g->vertices[toIdx].head == NULL) {
        g->vertices[toIdx].head = node2;
    } else {
        AdjListNode* temp = g->vertices[toIdx].head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node2;
    }
}

