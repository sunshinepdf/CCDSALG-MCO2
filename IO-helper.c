/**
 * CCDSALG MCO2 GROUP 24
 * Description: Input/Output helper functions for reading and writing of graph data from file
 * 
 * Authors:
 * Laborada, Nathan
 * Lee, Ashley Fiona
 * Villorente, Khyle Raeke
 */

#include "IO-helper.h"

/**
 * Helper function to swap two vertex names.
 * 
 * @param a First vertex name
 * @param b Second vertex name
 */
void swapVertices(char a[MAX_NLENGTH], char b[MAX_NLENGTH]) {
    char temp[MAX_NLENGTH];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

/**
 * Helper function to swap two Edge structures.
 * 
 * @param a First edge
 * @param b Second edge
 */
void swapEdges(Edge* a, Edge* b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Helper function to swap two VertexDegree structures.
 * 
 * @param a First VertexDegree
 * @param b Second VertexDegree
 */
void swapVertexDegrees(VertexDegree* a, VertexDegree* b) {
    VertexDegree temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Quick Sort implementation for vertex names.
 * 
 * @param vertices 2D array of vertex names
 * @param low Starting index
 * @param high Ending index
 */
void quickSortVertices(char vertices[][MAX_NLENGTH], int low, int high) {
    if (low < high) {
        int pi = partitionVertices(vertices, low, high);
        
        quickSortVertices(vertices, low, pi - 1);
        quickSortVertices(vertices, pi + 1, high);
    }
}

/**
 * Partition function for vertex quick sort.
 * 
 * @param vertices 2D array of vertex names
 * @param low Starting index
 * @param high Ending index
 * @return Partition index
 */
int partitionVertices(char vertices[][MAX_NLENGTH], int low, int high) {
    char pivot[MAX_NLENGTH];
    strcpy(pivot, vertices[high]);
    
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(vertices[j], pivot) < 0) {
            i++;
            swapVertices(vertices[i], vertices[j]);
        }
    }
    
    swapVertices(vertices[i + 1], vertices[high]);
    
    return (i + 1);
}

/**
 * Quick Sort implementation for edges.
 * 
 * @param edges Array of Edge structures
 * @param low Starting index
 * @param high Ending index
 */
void quickSortEdges(Edge edges[], int low, int high) {
    if (low < high) {
        int pi = partitionEdges(edges, low, high);
        
        quickSortEdges(edges, low, pi - 1);
        quickSortEdges(edges, pi + 1, high);
    }
}

/**
 * Partition function for edge quick sort.
 * 
 * @param edges Array of Edge structures
 * @param low Starting index
 * @param high Ending index
 * @return Partition index
 */
int partitionEdges(Edge edges[], int low, int high) {
    Edge pivot = edges[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        int cmp = strcmp(edges[j].from, pivot.from);
        if (cmp < 0 || (cmp == 0 && strcmp(edges[j].to, pivot.to) < 0)) {
            i++;
            swapEdges(&edges[i], &edges[j]);
        }
    }
    swapEdges(&edges[i + 1], &edges[high]);
    
    return (i + 1);
}

/**
 * Quick Sort implementation for VertexDegree structures.
 * 
 * @param vertexDegrees Array of VertexDegree structures
 * @param low Starting index
 * @param high Ending index
 */
void quickSortVertexDegrees(VertexDegree vertexDegrees[], int low, int high) {
    if (low < high) {
        int pi = partitionVertexDegrees(vertexDegrees, low, high);
        
        quickSortVertexDegrees(vertexDegrees, low, pi - 1);
        quickSortVertexDegrees(vertexDegrees, pi + 1, high);
    }
}

/**
 * Partition function for VertexDegree quick sort.
 * 
 * @param vertexDegrees Array of VertexDegree structures
 * @param low Starting index
 * @param high Ending index
 * @return Partition index
 */
int partitionVertexDegrees(VertexDegree vertexDegrees[], int low, int high) {
    VertexDegree pivot = vertexDegrees[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(vertexDegrees[j].name, pivot.name) < 0) {
            i++;
            swapVertexDegrees(&vertexDegrees[i], &vertexDegrees[j]);
        }
    }
    swapVertexDegrees(&vertexDegrees[i + 1], &vertexDegrees[high]);
    
    return (i + 1);
}

/**
 * Helper function to remove a specific extension from a filename.
 * 
 * @param filename The filename to modify (modified in place)
 * @param extension The extension to remove (e.g., ".TXT")
 */
void removeExtension(char* filename, const char* extension) {
    char* dotPos = strrchr(filename, '.');
    if (dotPos != NULL) {
        if (strcmp(dotPos, ".TXT") == 0 || strcmp(dotPos, ".txt") == 0) {
            *dotPos = '\0';  
        }
    }
}

/**
 * Helper function to create output filename by removing extension and adding suffix.
 * 
 * @param outputFilename Buffer to store the result
 * @param inputFilename The input filename
 * @param suffix The suffix to append (e.g., "-DEGREE.TXT")
 */
void createOutputFilename(char* outputFilename, const char* inputFilename, const char* suffix) {
    strcpy(outputFilename, inputFilename);
    removeExtension(outputFilename, ".TXT");
    strcat(outputFilename, suffix);
}