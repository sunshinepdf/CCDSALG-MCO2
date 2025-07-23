/**
 * CCDSALG MCO2 GROUP 24
 * Description: Input/Output functions for reading graph data from file
 * 
 * Authors:
 * Laborada, Nathan
 * Lee, Ashley Fiona
 * Villorente, Khyle Raeke
 */

#ifndef IO_H
#define IO_H

#include "IO-helper.h"

int readGraphFromFile(const char* filename, Graph* g);
int parseVertexLine(const char* line, Graph* g);
void writeOutput1(const char* filename, Graph* g);
void writeOutput2(const char* filename, Graph* g);
void writeOutput3(const char* filename, Graph* g);
void writeOutput4(const char* filename, Graph* g);
void writeOutput5(const char* filename, Graph* g, char startVertex[MAX_NLENGTH]);
void writeOutput6(const char* filename, Graph* g, char startVertex[MAX_NLENGTH]);

#endif
