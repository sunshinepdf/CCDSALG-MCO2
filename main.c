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
#include <string.h>
#include "graph.h"
#include "IO.h"
#include "traversal.h"

int main() {
    char inputFileName[100];
    Graph graphData;

    // Takes the Input Filename
    printf("Input filename: ");
    scanf("%s", inputFileName);

    // Calls the readGraphFromFile function to read the graph data from the file, if the file is not found, 
    // it will print an error message and exit
    if (readGraphFromFile(inputFileName, &graphData) == 0) {
        printf("File %s not found.\n", inputFileName);
        return 1;
    }
    
    // Writes the outputs to files based on the graph data
    writeOutput1(inputFileName, &graphData);
    writeOutput2(inputFileName, &graphData);
    writeOutput3(inputFileName, &graphData);
    writeOutput4(inputFileName, &graphData);

    int found = 0;
    char startVertex[MAX_NLENGTH];

    // Checks if the start vertex exists in the graph
     while (!found) {
        printf("Input start vertex for the traversal: ");
        scanf("%s", startVertex);

        for (int i = 0; i < graphData.numVertices; i++) {
            if (strcmp(graphData.vertices[i].vertexName, startVertex) == 0) {
                found = 1;
                break;
                }
        }
            // If the start vertex is not found, print an error message and exit
            if (!found) {
                printf("Vertex %s not found.\n", startVertex);
                return 1; 
            }
    }
    
    // If the start vertex is found, write the BFS and DFS outputs
    if (found)
    {
        writeOutput5(inputFileName, &graphData, startVertex);
        writeOutput6(inputFileName, &graphData, startVertex);
    }
        
    return 0;
    
}
    
  

