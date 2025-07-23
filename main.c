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

    // Ask for the input filename (e.g., G.TXT)
    printf("Input filename: ");
    scanf("%s", inputFileName);

    // Try to read graph from the input file
    if (readGraphFromFile(inputFileName, &graphData) == 0) {
        printf("File %s not found.\n", inputFileName);
        return 1;
    }

    writeOutput1(inputFileName, &graphData);
    writeOutput2(inputFileName, &graphData);
    writeOutput3(inputFileName, &graphData);
    writeOutput4(inputFileName, &graphData);

    char startVertex[MAX_NLENGTH]; 
    int found = 0;
    
    if(graphData.numVertices > 1) {

     while (!found ) {
            printf("Input start vertex for the traversal: ");
            scanf("%s", startVertex);

             for (int i = 0; i < graphData.numVertices; i++) {
                if (strcmp(graphData.vertices[i].vertexName, startVertex) == 0) {
                    found = 1;
                    break;
                 }
             }
            
            if (!found) {
                 printf("Vertex %s not found.\n", startVertex);
                 return 1;
             }
     }

        writeOutput5(inputFileName, &graphData, startVertex);
        writeOutput6(inputFileName, &graphData, startVertex);
    }
    return 0;
}
