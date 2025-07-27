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
    fgets(line, sizeof(line), file); // consume the newline after numVertices

    // First pass: Add all main vertices in the order they appear in the file
    long filePos = ftell(file); // Save current position
    for (int i = 0; i < numVertices; i++) {
        if (!fgets(line, sizeof(line), file)) {
            fclose(file);
            return 0;
        }
        
        char lineCopy[256];
        strcpy(lineCopy, line);
        char* token = strtok(lineCopy, " \t\n");
        if (token) {
            char vertexName[MAX_NLENGTH];
            strncpy(vertexName, token, MAX_NLENGTH - 1);
            vertexName[MAX_NLENGTH - 1] = '\0';
            getVertexIndex(g, vertexName); 
        }
    }

    fseek(file, filePos, SEEK_SET); // Reset file position to beginning of vertex list to re-read lines
    for (int i = 0; i < numVertices; i++) { // Second pass: parse each vertex line and build adjacency lists
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
 * Only adds edges in the direction specified by the line to preserve exact input order.
 * 
 * @param line the line to parse
 * @param g pointer to the Graph structure
 * @return 1 if successful, 0 if failed
 */
int parseVertexLine(const char* line, Graph* g) {
    char lineCopy[256];
    strcpy(lineCopy, line);

    // Get the first token 
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

    // Process each adjacent vertex in the line
    while ((token = strtok(NULL, " \t\n")) != NULL) {
        if (strcmp(token, "-1") == 0) {
            break;
        }
        
        char adjacentName[MAX_NLENGTH];
        strncpy(adjacentName, token, MAX_NLENGTH - 1);
        adjacentName[MAX_NLENGTH - 1] = '\0';

        int toIdx = getVertexIndex(g, adjacentName);
        if (toIdx != -1) {
            AdjListNode* current = g->vertices[vertexIndex].head; // Check if edge already exists
            int exists = 0;
            while (current != NULL) {
                if (current->vertexIndex == toIdx) {
                    exists = 1;
                    break;
                }
                current = current->next;
            }
            
            if (!exists) {  // Add edge if not already connected
                AdjListNode* newNode = createAdjListNode(toIdx);
                newNode->next = NULL;
                
                if (g->vertices[vertexIndex].head == NULL) {
                    g->vertices[vertexIndex].head = newNode;
                } else { // Append to end of adjacency list
                    AdjListNode* temp = g->vertices[vertexIndex].head;
                    while (temp->next != NULL) {
                        temp = temp->next;
                    }
                    temp->next = newNode;
                }
            }
        }
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
    createOutputFilename(outputFilename, filename, "-SET.TXT"); // Create output filename
    
    FILE* file = fopen(outputFilename, "w"); // Open file for writing

    char baseName[256];
    strncpy(baseName, filename, sizeof(baseName));
    baseName[sizeof(baseName) - 1] = '\0';

    char *dot = strrchr(baseName, '.');
    if (dot) {
        *dot = '\0';
    }
    
    char sortedVertices[MAX_VERTICES][MAX_NLENGTH];
    int vertexCount = g->numVertices;

    // Copy vertex for sorting
    for (int i = 0; i < vertexCount; i++) {
        strcpy(sortedVertices[i], g->vertices[i].vertexName);
    }

    // Sort vertex in ascending order
    if (vertexCount > 1) {
        quickSortVertices(sortedVertices, 0, vertexCount - 1);
    }
    
    // Write the vertex set V(G)
    fprintf(file, "V(%s)={", baseName);
    for (int i = 0; i < vertexCount; i++) {
        fprintf(file, "%s", sortedVertices[i]);
        if (i < vertexCount - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "}\n");
    
    // Gather all undirected edges
    Edge edges[MAX_VERTICES * MAX_VERTICES];
    int edgeCount = 0;
    
    for (int i = 0; i < g->numVertices; i++) {
        AdjListNode* current = g->vertices[i].head;
        while (current != NULL) {
            char vertex1[MAX_NLENGTH], vertex2[MAX_NLENGTH];
            strcpy(vertex1, g->vertices[i].vertexName);
            strcpy(vertex2, g->vertices[current->vertexIndex].vertexName);

            // Add edge only if vertex1 < vertex2 to avoid duplicates
            if (strcmp(vertex1, vertex2) < 0) { 
                strcpy(edges[edgeCount].from, vertex1);
                strcpy(edges[edgeCount].to, vertex2);
                edgeCount++;
            }

            current = current->next;
        }
    }
    
    if (edgeCount > 1) {  // Sort edges lexicographically
        quickSortEdges(edges, 0, edgeCount - 1);
    }

    // Write the edge set E(G)
    fprintf(file, "E(%s)={", baseName); 
    for (int i = 0; i < edgeCount; i++) {
        fprintf(file, "(%s,%s)", edges[i].from, edges[i].to);
        if (i < edgeCount - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "}\n");
    
    fclose(file); // Close the output file
}

/**
 * Output2: Writes vertex IDs with their corresponding degrees in alphabetical order.
 * 
 * @param filename filename of the original input file 
 * @param g pointer to the Graph structure
 */
void writeOutput2(const char* filename, Graph* g) {
    char outputFilename[256];
    createOutputFilename(outputFilename, filename, "-DEGREE.TXT"); // Create output filename
    FILE* file = fopen(outputFilename, "w");  // Open file for writing

    VertexDegree vertexDegrees[MAX_VERTICES];
    int vertexCount = g->numVertices;
    for (int i = 0; i < vertexCount; i++) {  // Count degree for each vertex
        strcpy(vertexDegrees[i].name, g->vertices[i].vertexName);

        int degree = 0;
        AdjListNode* current = g->vertices[i].head;
        while (current != NULL) {
            degree++;
            current = current->next;
        }
        vertexDegrees[i].degree = degree;
    }
    
    if (vertexCount > 1) { // Sort vertices in ascending order
        quickSortVertexDegrees(vertexDegrees, 0, vertexCount - 1);
    }
    
    for (int i = 0; i < vertexCount; i++) { // Output format 
        fprintf(file, "%s \t%d\n", vertexDegrees[i].name, vertexDegrees[i].degree);
    }
    
    fclose(file); // Close the output file
}

/**
 * Output3: Writes adjacency list representation of the graph.
 * 
 * @param filename filename of the original input file 
 * @param g pointer to the Graph structure
 */
void writeOutput3(const char* filename, Graph* g) {
    char outputFilename[256];
    createOutputFilename(outputFilename, filename, "-LIST.TXT"); //Create output filename
     
    FILE* file = fopen(outputFilename, "w");   // Open file for writing
    for (int i = 0; i < g->numVertices; i++) { // Print its adjacency list for each vertex
        fprintf(file, "%s", g->vertices[i].vertexName); 
        
        AdjListNode* current = g->vertices[i].head;
        while (current != NULL) {
            fprintf(file, "->%s", g->vertices[current->vertexIndex].vertexName);
            current = current->next;
        }
        fprintf(file, "->\\\n");
    }
    
    fclose(file); //Close file
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
    createOutputFilename(outputFilename, filename, "-MATRIX.TXT"); //Create ourput filname
     
    FILE* file = fopen(outputFilename, "w");  // Open file for writing
    int vertexCount = g->numVertices;

     // Print header row (column labels)
    fprintf(file, "     "); 
    for (int i = 0; i < vertexCount; i++) {
        fprintf(file, "%8s", g->vertices[i].vertexName); // Col header
    }
    fprintf(file, "\n");

    for (int i = 0; i < vertexCount; i++) { // Print each row
        fprintf(file, "%5s", g->vertices[i].vertexName);   // Row label
        for (int j = 0; j < vertexCount; j++) 
        {
            int connected = 0;
            // Check if j is adjacent to i
            AdjListNode* current = g->vertices[i].head; 
            while (current != NULL) {
                if (current->vertexIndex == j) 
                {
                    connected = 1;
                    break;
                }
                current = current->next;
            }
            fprintf(file, "%8d", connected); // Print 1 if edge exists, else 0
        }
        fprintf(file, "\n");
    }
    
    fclose(file); //Close file
}

/**
 * Output5: Writes BFS traversal sequence from a specified start vertex.
 * When multiple candidates exist, visit vertex with lowest ID (alphabetically first).
 * Uses BFS function from traversal.c to get the traversal data.
 * 
 * @param filename filename of the original input file 
 * @param g pointer to the Graph structure
 */
void writeOutput5(const char* filename, Graph* g, char startVertex[MAX_NLENGTH]) {
    char outputFilename[256];
    createOutputFilename(outputFilename, filename, "-BFS.TXT"); //Create output filename
    
    FILE* file = fopen(outputFilename, "w"); // Open file for writing

    if (g->numVertices == 0) {
        fclose(file);
        return;
    }
    
    char bfsResult[MAX_VERTICES][MAX_NLENGTH];
    int count = BFSTraversal(g, startVertex, bfsResult); // Perform BFS starting from startVertex

    for (int i = 0; i < count; i++) { // Write result to file
        if (i > 0) {
            fprintf(file, " ");
        }
        fprintf(file, "%s", bfsResult[i]);
    }
    fprintf(file, "\n");
    
    fclose(file); //Close file
}

/**
 * Output6: Writes DFS traversal sequence from a specified start vertex.
 * When multiple candidates exist, visit vertex with lowest ID (alphabetically first).
 * Uses DFS function from traversal.c to get the traversal data.
 * 
 * @param filename filename of the original input file 
 * @param g pointer to the Graph structure
 */
void writeOutput6(const char* filename, Graph* g, char startVertex[MAX_NLENGTH]) {
    char outputFilename[256];
    createOutputFilename(outputFilename, filename, "-DFS.TXT"); //Create output filename
    
    FILE* file = fopen(outputFilename, "w"); // Open file for writing

    if (g->numVertices == 0) {
        fclose(file);
        return;
    }
    
    char dfsResult[MAX_VERTICES][MAX_NLENGTH];
    int count = DFSTraversal(g, startVertex, dfsResult); // Perform DFS starting from startVertex
    
    for (int i = 0; i < count; i++) { // Write traversal result
        if (i > 0) {
            fprintf(file, " ");
        }
        fprintf(file, "%s", dfsResult[i]);
    }
    fprintf(file, "\n");
    
    fclose(file); //Close file
}  
