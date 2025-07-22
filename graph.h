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

#ifndef GRAPH_H
#define GRAPH_H
#define MAX_VERTICES 20
#define MAX_NLENGTH 9

/** 
 * This structure is for the node in the adjacency list.
 */
typedef struct AdjListNode {
    int vertexIndex;              // Index of the adjacent vertex
    struct AdjListNode* next;     // Pointer to next node in the list
} AdjListNode;

/** 
 * This structure is for the list of adjacency nodes for a vertex.
 */
typedef struct {
    char vertexName[MAX_NLENGTH];     // Name of the vertex
    AdjListNode* head;                // Pointer to the head of the adjacency list
} Vertex;

/** 
 * This structure is for the graph and how much vertices it has.
 */
typedef struct {
    int numVertices;                    // Number of vertices
    Vertex vertices[MAX_VERTICES];      // Array of all vertices
} Graph;

//function prototypes
int getVertexIndex(Graph* g, const char* label);
void addEdge(Graph* g, const char* from, const char* to);
int addVertex(Graph* g, const char* label);
AdjListNode* createAdjListNode(int index);

#endif
