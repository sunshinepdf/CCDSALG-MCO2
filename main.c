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

/**
 * This is the main function for running the social network graph program.
 * It asks the user for a filename, reads the graph data from a file,
 * then generates six output files based on the graph and traversal results.
 *
 * @return 0 if it runs successfully, 1 otherwise
 */
int main() {
    char inputFileName[100];
    Graph graphData;
    
    // Ask for filename input
    printf("Input filename: ");
    scanf("%s", inputFileName);

    ///Read graph from the input file
    if (readGraphFromFile(inputFileName, &graphData) == 1) {
        return 1;
    } 

    // Execute output files 1 to 4
    writeOutput1(inputFileName, &graphData);
    writeOutput2(inputFileName, &graphData);
    writeOutput3(inputFileName, &graphData);
    writeOutput4(inputFileName, &graphData);

    char startVertex[MAX_NLENGTH]; 
    int found = 0;

    //Checking if graph has more than 1 vertex
    if(graphData.numVertices > 1) {
         while (!found ) { //Loop until start vertex is found
             printf("Input start vertex for the traversal: ");
             scanf("%s", startVertex);
            
             // Search the graph's vertex list for a match with the user's input
             for (int i = 0; i < graphData.numVertices; i++) {
                 if (strcmp(graphData.vertices[i].vertexName, startVertex) == 0) {
                     found = 1; // vertext found
                     break;
                }
            }
    
            if (!found) { //Input vertext is not found
                printf("Vertex %s not found.\n", startVertex);
                return 1;
            }
         }
            //Execute output files 5 and 6
            writeOutput5(inputFileName, &graphData, startVertex);
            writeOutput6(inputFileName, &graphData, startVertex);
        }
    return 0;
}
