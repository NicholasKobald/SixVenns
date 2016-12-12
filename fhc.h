/*
FIVE VENNS 
N. Kobald 2016-11-27

Six venns have 2^6 faces, 
*/
#ifndef FHC_H_   /* Include guard */
#define FHC_H_


#include <stdlib.h>
#include <stdio.h>

#define NMAX 62
#define DEGREE 4
#define FMAX 64//faces in original graph
#define EMAX 124 //edges in original graph


typedef struct {
	int v; 
    int u;
}edge; 

typedef struct {
	int degree;
	int adj_to[FMAX];
}Node; 

typedef struct {
	int max_degree;
	int used_degree; 
}n_info; 


int FHCtest(int startvert, int curvert, int GF[FMAX][FMAX], int visited[FMAX], int degree_used[FMAX][2]);
int fhc_five(int startvert, int curvert, Node GF[FMAX], int visited[FMAX],
	int path[FMAX], int, n_info[FMAX]);
int fhc_five_start(int startvert, int curvert, Node GF[FMAX], int visited[FMAX],
	int path[FMAX], int dist);

void print_path(int path[FMAX],  int); 
void print_visited(edge visited[EMAX*2], int seen);

void construct_adjlist(edge GD[FMAX][FMAX], Node GF[FMAX]);
void compute_dual(int G[NMAX][DEGREE], Node GF[FMAX]);
int all_visited(int visited[FMAX]);
int find_hamiltonian_cycle(int startvert, int curvert, Node GF[FMAX], 
	int visited[FMAX], int len_path, int path[FMAX], n_info[FMAX]);

void create_bfs_labeling(Node GF[FMAX], int [FMAX]); 
void relabel_graph(Node GF[FMAX], int [FMAX]); 
#endif