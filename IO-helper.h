/**
 * CCDSALG MCO2 GROUP 24
 * Description: Input/Output helper functions for reading and writing of graph data from file
 * 
 * Authors:
 * Laborada, Nathan
 * Lee, Ashley Fiona
 * Villorente, Khyle Raeke
 */

#ifndef IO_HELPER_H
#define IO_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

typedef struct {
    char name[MAX_NLENGTH];
    int degree;
} VertexDegree;

typedef struct {
    char from[MAX_NLENGTH];
    char to[MAX_NLENGTH];
} Edge;

void quickSortVertexDegrees(VertexDegree vertexDegrees[], int low, int high);
int partitionVertexDegrees(VertexDegree vertexDegrees[], int low, int high);

void quickSortVertices(char vertices[][MAX_NLENGTH], int low, int high);
int partitionVertices(char vertices[][MAX_NLENGTH], int low, int high);

void quickSortEdges(Edge edges[], int low, int high);
int partitionEdges(Edge edges[], int low, int high);

void removeExtension(char* filename, const char* extension);
void createOutputFilename(char* outputFilename, const char* inputFilename, const char* suffix);

void swapVertices(char a[MAX_NLENGTH], char b[MAX_NLENGTH]);
void swapEdges(Edge* a, Edge* b);
void swapVertexDegrees(VertexDegree* a, VertexDegree* b);

#endif