/**
 * CCDSALG MCO2 GROUP 24
 * Description: Main module that integrates other modules and appropriate functions
 * 
 * Authors:
 * Laborada, Nathan
 * Lee, Ashley Fiona
 * Villorente, Khyle Raeke
 */
#
include <stdio.h>
#include "graph.h"

/**
 * Displays the graph in adjacency linked representation format.
 *
 * @param g A pointer to the Graph struct to be displayed.
 */
void displayGraph(Graph* g) {
    for (int i = 0; i < g->numVertices; i++) {
        printf("%s ->", g->vertices[i].vertexName);
        AdjListNode* temp = g->vertices[i].head;
        while (temp != NULL) {
            printf(" %s", g->vertices[temp->vertexIndex].vertexName);
            temp = temp->next;
        }
        printf("\n");
    }
}

/**
 * The main function (Task 3) 
 */
int main() {
    Graph g;
    initializeGraph(&g);

    int n;
    scanf("%d", &n);  // Number of edges

    for (int i = 0; i < n; i++) {
        char from[MAX_NLENGTH], to[MAX_NLENGTH];
        scanf("%s %s", from, to);
        addEdge(&g, from, to);
    }

    printf("\nGraph adjacency list:\n");
    displayGraph(&g);

    return 0;
}
