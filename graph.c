#include "graph.h"

static void destroyVert(Vert*);
static void destroyEdge(Edge*);
static void addAdj(Vert*,int);
static Vert* getVert(Graph*,int);


struct edge {
    int lb1;
    int lb2;
};

struct vert {
    int label;
    int deg;
    int* adj;
};

struct graph {
    int* labels;
    int num_vert;
    int num_edge; 
    Vert* verts;
    Edge* edges;
};

//creation----------------------------------
Graph* createGraph() {
    Graph* g = malloc(sizeof(Graph));

    g->num_vert = 0;
    g->num_edge = 0;
    g->verts = NULL;
    g->edges = NULL;
    g->labels = NULL;
    return g;
}

static Edge* createEdge(int id1, int id2) {
    Edge* e = malloc(sizeof(Edge));

    e->lb1 = id1;
    e->lb2 = id2;
    return e;
}

static Vert* createVert(int lb) {
    Vert* n = malloc(sizeof(Vert));

    n->label = lb;
    n->deg = 0;
    n->adj = NULL;

    return n;
}

//deletion------------------------------------
void destroyGraph(Graph* g) {
    for (int i = 0; i < g->num_vert; ++i) {
        destroyVert(g->verts+i);
    }
    for (int i = 0; i < g->num_edge; ++i) {
        destroyEdge(g->edges+i);
    }
    free(g->verts);
    free(g->edges);
    free(g->labels);
    free(g);
}

static void destroyEdge(Edge* e) {
    //free(e);
}

static void destroyVert(Vert* n) {
    free(n->adj);
    //free(n);
}

//mutation---------------------------------------
//TODO void removeVert(Graph* g, int label);
//TODO void removeEdge(Graph* g, int lb1, int lb2);

//adds lb to g
//no regard for collisions
void addVert(Graph* g, int lb) {    
    //update verts
    Vert* n = createVert(lb);
    Vert* temp = g->verts;
    g->verts = malloc(sizeof(Vert) * ++g->num_vert);
    for (int i = 0; i < g->num_vert-1; ++i) {
        g->verts[i] = temp[i];
    }
    g->verts[g->num_vert-1] = *n;
    free(n);
    free(temp);
    
    //update labels
    int* tempL = g->labels;
    g->labels = malloc(sizeof(int) * g->num_vert);
    for (int i = 0; i < g->num_vert-1; ++i) {
        g->labels[i] = tempL[i];
    }
    g->labels[g->num_vert-1] = lb;
    free(tempL);
}

//adds edge between lb1 and lb2. if directional edges, adds lb1->lb2
//prints error message if one dne in g
void addEdge(Graph* g, int lb1, int lb2) {
    Vert* n1 = getVert(g, lb1);
    Vert* n2 = getVert(g, lb2);
    if (n1 && n2) {
        Edge* e = createEdge(lb1, lb2);

        Edge* temp = g->edges;
        g->edges = malloc(sizeof(Edge) * ++g->num_edge);

        for (int i = 0; i < g->num_edge - 1; ++i) {
            g->edges[i] = temp[i];
        }
        g->edges[g->num_edge-1] = *e;
        free(e);
        free(temp);

        //now add adjacencies to the verts
        addAdj(n1, lb2);
        addAdj(n2, lb1);
    } else {
       fprintf(stderr, "Could not make edge: %d to %d\n",lb1, lb2);
    }
} 


//add a label to the list of adjacent verts to n
//assumed lb is actually a valid node
static void addAdj(Vert* n, int lb) {
    int* temp = n->adj;
    n->deg+=1;
    n->adj = malloc(sizeof(int) * n->deg);
    for (int i = 0; i < n->deg - 1; ++i) {
        n->adj[i] = temp[i];
    }

    n->adj[n->deg-1] = lb;
    free(temp);

    /*temp = neigh->neigh;

   neigh->neigh = malloc(sizeof(Node) * ++neigh->deg);
    for (int i = 0; i < neigh->deg - 1; ++i) {
        neigh->neigh[i] = temp[i];
    }

    neigh->neigh[n->deg-1] = *n;
    
    free(temp);*/
}

//getters-------------------------------------
static Vert* getVert(Graph* g, int lb) {
    Vert* ret = NULL;

    for (int i = 0; i < g->num_vert; ++i) {
        if (lb == g->verts[i].label) {
            ret = g->verts+i;
        }
    }

    return ret;
}

//returns degree for vert with label lb in g
//returns -1 if lb dne in g
int getDeg(Graph* g, int lb) {
    Vert* n = getVert(g, lb);

    if (n) {
        return n->deg;
    } else {
        return -1;
    }
}

//returns true iff lb1 -> lb2 in g
//says nothing about existance
int adj(Graph* g, int lb1, int lb2) {
    Vert* n = getVert(g, lb1);
    if (n) {
        for (int i = 0; i < n->deg; ++i) {
            if ((n->adj[i] = lb2)) {
                return 1;
            }
        }
    }

    return 0;
}

//TODO figure out thing
//returns copy of integer array containing all teh labels of adjs
//size filled with size of array
//if lb does not exist, returns NULL and size is -1
const int* getAdj(Graph* g, int lb, int* size) {
    Vert* n = getVert(g, lb);
    *size = -1;
     int* ret = NULL;
    if (n) {
        *size = n->deg;
        ret = malloc(sizeof(int) * *size);
        for (int i = 0; i < *size; ++i) {
             ret[i] = n->adj[i];
        }
        //ret = n->adj;//probably this kike here
        //*size = n->deg;
    }
    return (const int *)ret;
}

//TODO FIGUE OUT THING
//returns ref to array of all labels of graph g
//size filled size of array
const int* getLabels(Graph* g, int* size) {
    *size = g->num_vert;
    return g->labels;
}
