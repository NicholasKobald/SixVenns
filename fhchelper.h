#ifndef FHCHELPER_H_   /* Include guard */
#define FHCHELPER_H_


#include "fhc.h"



int equalEdge(edge a, edge b);
int weak_equiv(edge e, edge t);

edge reverse_edge(edge e);
edge find_next_edge(edge visited[EMAX*2], int G[NMAX][DEGREE], int seen);
edge copy_edge(edge e);
edge rotate_edge(edge e, int G[NMAX][DEGREE]);
int contains_edge(edge check, edge visited[EMAX*2], int seen);
void pal(Node GF[FMAX]);
void print_edge(edge e);
void print_faces(edge GD[FMAX][FMAX]);
void print_adjlist(int G[NMAX][DEGREE]);
void load_line_from_file(FILE *fp, int[NMAX][DEGREE]);

void set_constants(int num_curves); 

int uses_edge(edge e, edge GD[FMAX][FMAX], int face);

#endif