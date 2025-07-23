/**
 * CCDSALG MCO2 GROUP 24
 * Description: Main module that integrates other modules and appropriate functions
 * 
 * Authors:
 * Laborada, Nathan
 * Lee, Ashley Fiona
 * Villorente, Khyle Raeke
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "IO.h"

int main() {
    char inputFileName[100]; // buffer to store user-input filename
    Graph graphData;
    int loadedSuccessfully = 0;

    // Prompt user to enter input file name
    printf("Enter input file name: ");
    scanf("%s", inputFileName);

    // Try loading the graph
    if (readGraphFromFile(inputFileName, &graphData) != 0) {
        printf("Failed to load graph from: %s\n", inputFileName);
    } else {
        loadedSuccessfully = 1;
        printf("Graph loaded from: %s\n", inputFileName);
        printf("Total number of vertices: %d\n", graphData.numVertices);
    }

    // If graph loaded, print adjacency list
    if (loadedSuccessfully) {
        for (int vertexIndex = 0; vertexIndex < graphData.numVertices; vertexIndex++) {
            printf("%s: ", graphData.vertices[vertexIndex].vertexName);

            AdjListNode* currentNeighbor = graphData.vertices[vertexIndex].head;
            while (currentNeighbor != NULL) {
                printf("%s -> ", graphData.vertices[currentNeighbor->vertexIndex].vertexName);
                currentNeighbor = currentNeighbor->next;
            }

            printf("NULL\n");
        }
    } else {
        printf("Graph was not loaded. Cannot display adjacency list.\n");
    }

    return 0;
}

