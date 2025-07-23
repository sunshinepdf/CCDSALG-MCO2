/**
 * CCDSALG MCO2 GROUP 24
 * Description: Header file for graph traversal algorithms (BFS and DFS)
 * 
 * Authors:
 * Laborada, Nathan
 * Lee, Ashley Fiona
 * Villorente, Khyle Raeke
 */

#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traversal-helper.h"


int BFSTraversal(Graph* g, const char* startVertex, char result[][MAX_NLENGTH]);
int DFSTraversal(Graph* g, const char* startVertex, char result[][MAX_NLENGTH]);

#endif
