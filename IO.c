/**
 * CCDSALG MCO2 GROUP 24
 * Description: Input/Output functions for reading graph data from file
 * 
 * Authors:
 * Laborada, Nathan
 * Lee, Ashley Fiona
 * Villorente, Khyle Raeke
 */


#include "IO.h"
#include "traversal.h"

/**
 * This function reads graph data from a file and populates the graph structure.
 * 
 * @param filename filename to the input file
 * @param g pointer to the Graph structure to populate
 * @return 1 if successful, 0 if failed
 */
int readGraphFromFile(const char* filename, Graph* g) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("File %s not found.\n", filename);
        return 0;
    }
    
    initializeGraph(g);
    
    int numVertices;
    if (fscanf(file, "%d", &numVertices) != 1) {
        printf("Error: Could not read number of vertices\n");
        fclose(file);
        return 0;
    }
    
    
    char line[512];
    fgets(line, sizeof(line), file);

    for (int i = 0; i < numVertices; i++) {
        if (!fgets(line, sizeof(line), file)) {
            fclose(file);
            return 0;
        }
        
        if (!parseVertexLine(line, g)) {
            fclose(file);
            return 0;
        }
    }
    
    fclose(file);
    return 1;
}

/**
 * Parses a single line containing vertex adjacency information.
 * 
 * @param line the line to parse
 * @param g pointer to the Graph structure
 * @return 1 if successful, 0 if failed
 */
int parseVertexLine(const char* line, Graph* g) {
    char lineCopy[256];
    strcpy(lineCopy, line);
    
    char* token = strtok(lineCopy, " \t\n");
    if (!token) {
        return 0;
    }
    
    char vertexName[MAX_NLENGTH];
    strncpy(vertexName, token, MAX_NLENGTH - 1);
    vertexName[MAX_NLENGTH - 1] = '\0';
    
    int vertexIndex = getVertexIndex(g, vertexName);
    if (vertexIndex == -1) {
        return 0;
    }
    
    while ((token = strtok(NULL, " \t\n")) != NULL) {
        if (strcmp(token, "-1") == 0) {
            break;
        }
        
        char adjacentName[MAX_NLENGTH];
        strncpy(adjacentName, token, MAX_NLENGTH - 1);
        adjacentName[MAX_NLENGTH - 1] = '\0';

        addEdge(g, vertexName, adjacentName);
    }
    
    return 1;
}

/**
 * Output1: Writes vertices and edges in ascending order to a file.
 * 
 * @param filename filename of the original input file 
 * @param g pointer to the Graph structure
 */
void writeOutput1(const char* filename, Graph* g) {
    char outputFilename[256];
    createOutputFilename(outputFilename, filename, "-SET.TXT");
    
    FILE* file = fopen(outputFilename, "w");
    
    char sortedVertices[MAX_VERTICES][MAX_NLENGTH];
    int vertexCount = g->numVertices;
    
    for (int i = 0; i < vertexCount; i++) {
        strcpy(sortedVertices[i], g->vertices[i].vertexName);
    }
    
    if (vertexCount > 1) {
        quickSortVertices(sortedVertices, 0, vertexCount - 1);
    }
    

    fprintf(file, "V(G)={");
    for (int i = 0; i < vertexCount; i++) {
        fprintf(file, "%s", sortedVertices[i]);
        if (i < vertexCount - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "}\n");
    

    Edge edges[MAX_VERTICES * MAX_VERTICES];
    int edgeCount = 0;
    
    for (int i = 0; i < g->numVertices; i++) {
        AdjListNode* current = g->vertices[i].head;
        while (current != NULL) {
            char vertex1[MAX_NLENGTH], vertex2[MAX_NLENGTH];
            strcpy(vertex1, g->vertices[i].vertexName);
            strcpy(vertex2, g->vertices[current->vertexIndex].vertexName);
            
            if (strcmp(vertex1, vertex2) < 0) {
                strcpy(edges[edgeCount].from, vertex1);
                strcpy(edges[edgeCount].to, vertex2);
                edgeCount++;
            }

            current = current->next;
        }
    }
    
    if (edgeCount > 1) {
        quickSortEdges(edges, 0, edgeCount - 1);
    }
    
    fprintf(file, "E(G)={");
    for (int i = 0; i < edgeCount; i++) {
        fprintf(file, "(%s,%s)", edges[i].from, edges[i].to);
        if (i < edgeCount - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "}\n");
    
    fclose(file);
}

/**
 * Output2: Writes vertex IDs with their corresponding degrees in alphabetical order.
 * 
 * @param filename filename of the original input file 
 * @param g pointer to the Graph structure
 */
void writeOutput2(const char* filename, Graph* g) {
    char outputFilename[256];
    createOutputFilename(outputFilename, filename, "-DEGREE.TXT");
    FILE* file = fopen(outputFilename, "w");
    
    VertexDegree vertexDegrees[MAX_VERTICES];
    int vertexCount = g->numVertices;
    for (int i = 0; i < vertexCount; i++) {
        strcpy(vertexDegrees[i].name, g->vertices[i].vertexName);

        int degree = 0;
        AdjListNode* current = g->vertices[i].head;
        while (current != NULL) {
            degree++;
            current = current->next;
        }
        vertexDegrees[i].degree = degree;
    }
    
    if (vertexCount > 1) {
        quickSortVertexDegrees(vertexDegrees, 0, vertexCount - 1);
    }
    
    for (int i = 0; i < vertexCount; i++) {
        fprintf(file, "%s \t%d\n", vertexDegrees[i].name, vertexDegrees[i].degree);
    }
    
    fclose(file);
}

/**
 * Output3: Writes adjacency list representation of the graph.
 * 
 * @param filename filename of the original input file 
 * @param g pointer to the Graph structure
 */
void writeOutput3(const char* filename, Graph* g) {
    char outputFilename[256];
    createOutputFilename(outputFilename, filename, "-LIST.TXT");
    
    FILE* file = fopen(outputFilename, "w");    
    for (int i = 0; i < g->numVertices; i++) {
        fprintf(file, "%s", g->vertices[i].vertexName);
        
        AdjListNode* current = g->vertices[i].head;
        while (current != NULL) {
            fprintf(file, "->%s", g->vertices[current->vertexIndex].vertexName);
            current = current->next;
        }
        fprintf(file, "->\\\n");
    }
    
    fclose(file);
}

/**
 * Output4: Writes adjacency matrix representation of the graph.
 * The matrix is printed with 1 for connected vertices and 0 for unconnected.
 * 
 * @param filename filename of the original input file 
 * @param g pointer to the Graph structure
 */
void writeOutput4(const char* filename, Graph* g) {
    char outputFilename[256];
    createOutputFilename(outputFilename, filename, "-MATRIX.TXT");
    
    FILE* file = fopen(outputFilename, "w");
    int vertexCount = g->numVertices;

    fprintf(file, "     "); 
    for (int i = 0; i < vertexCount; i++) {
        fprintf(file, "%8s", g->vertices[i].vertexName);
    }
    fprintf(file, "\n");

    for (int i = 0; i < vertexCount; i++) {
        fprintf(file, "%5s", g->vertices[i].vertexName);
        for (int j = 0; j < vertexCount; j++) 
        {
            int connected = 0;
            AdjListNode* current = g->vertices[i].head;
            while (current != NULL) {
                if (current->vertexIndex == j) 
                {
                    connected = 1;
                    break;
                }
                current = current->next;
            }
            fprintf(file, "%8d", connected);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
}

/**
 * Output5: Writes BFS traversal sequence from a specified start vertex.
 * When multiple candidates exist, visit vertex with lowest ID (alphabetically first).
 * Uses BFS function from traversal.c to get the traversal data.
 * 
 * @param filename filename of the original input file 
 * @param g pointer to the Graph structure
 */
void writeOutput5(const char* filename, Graph* g) {
    char outputFilename[256];
    char startVertex[MAX_NLENGTH];
    char bfsResult[MAX_VERTICES][MAX_NLENGTH];
    int count = BFSTraversal(g, startVertex, bfsResult);

    createOutputFilename(outputFilename, filename, "-BFS.TXT");
    
    FILE* file = fopen(outputFilename, "w");
    if (g->numVertices == 0) {
        fclose(file);
        return;
    }
    
    strcpy(startVertex, g->vertices[0].vertexName);

    for (int i = 0; i < count; i++) {
        if (i > 0) {
            fprintf(file, " ");
        }
        fprintf(file, "%s", bfsResult[i]);
    }
    fprintf(file, "\n");
    
    fclose(file);
}

/**
 * Output6: Writes DFS traversal sequence from a specified start vertex.
 * When multiple candidates exist, visit vertex with lowest ID (alphabetically first).
 * Uses DFS function from traversal.c to get the traversal data.
 * 
 * @param filename filename of the original input file 
 * @param g pointer to the Graph structure
 */
void writeOutput6(const char* filename, Graph* g) {
    char outputFilename[256];
    char startVertex[MAX_NLENGTH];
    char dfsResult[MAX_VERTICES][MAX_NLENGTH];
    int count = DFSTraversal(g, startVertex, dfsResult);

    createOutputFilename(outputFilename, filename, "-DFS.TXT");
    
    FILE* file = fopen(outputFilename, "w");
    if (g->numVertices == 0) {
        fclose(file);
        return;
    }
    
    strcpy(startVertex, g->vertices[0].vertexName);
    
    for (int i = 0; i < count; i++) {
        if (i > 0) {
            fprintf(file, " ");
        }
        fprintf(file, "%s", dfsResult[i]);
    }
    fprintf(file, "\n");
    
    fclose(file);
}  


// /**
//  * Output5: Writes BFS traversal sequence from a specified start vertex.
//  * When multiple candidates exist, visit vertex with lowest ID (alphabetically first).
//  * Uses BFS function from traversal.c to get the traversal data.
//  * 
//  * @param filename filename of the original input file 
//  * @param g pointer to the Graph structure
//  */
// void writeOutput5(const char* filename, Graph* g, const char* startVertex) {
//     char outputFilename[256];
//     char bfsResult[MAX_VERTICES][MAX_NLENGTH];
//     int count = BFSTraversal(g, startVertex, bfsResult);

//     createOutputFilename(outputFilename, filename, "-BFS.TXT");
    
//     FILE* file = fopen(outputFilename, "w");
//     if (!file || g->numVertices == 0) {
//         fclose(file);
//         return;
//     }
    
//     for (int i = 0; i < count; i++) {
//         if (i > 0) {
//             fprintf(file, " ");
//         }
//         fprintf(file, "%s", bfsResult[i]);
//     }
//     fprintf(file, "\n");

//     fclose(file);
// }

// /**
//  * Output6: Writes DFS traversal sequence from a specified start vertex.
//  * When multiple candidates exist, visit vertex with lowest ID (alphabetically first).
//  * Uses DFS function from traversal.c to get the traversal data.
//  * 
//  * @param filename filename of the original input file 
//  * @param g pointer to the Graph structure
//  */
// void writeOutput6(const char* filename, Graph* g, const char* startVertex) {
//     char outputFilename[256];
//     char dfsResult[MAX_VERTICES][MAX_NLENGTH];
//     int count = DFSTraversal(g, startVertex, dfsResult);

//     createOutputFilename(outputFilename, filename, "-DFS.TXT");
    
//     FILE* file = fopen(outputFilename, "w");
//     if (!file || g->numVertices == 0) {
//         fclose(file);
//         return;
//     }
    
//    for (int i = 0; i < count; i++) {
//         if (i > 0) {
//             fprintf(file, " ");
//         }
//         fprintf(file, "%s", dfsResult[i]);
//     }
//     fprintf(file, "\n");

//     fclose(file);
// }  
