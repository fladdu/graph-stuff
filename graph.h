//#include <SDL2/SDL2.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph Graph;
typedef struct vert Vert;
typedef struct edge Edge;

struct graph;
struct vert; 
struct edge;

//creation
Graph* createGraph();

//deletion
void destroyGraph(Graph* g);


//mutaion
void addVert(Graph* g, int label);
void addEdge(Graph* g, int lb1, int lb2);
//TODO void removeVert(Graph* g, int label);
//TODO void removeEdge(Graph* g, int lb1, int lb2);


//getters lel
int getDeg(Graph* g, int label);
//TODO const int* getLabels(Graph*g, int* size);//dont call this cunt
int adj(Graph* g, int lb1, int lb2);
const int* getAdj(Graph* g, int lb, int* size); //must free
#endif
