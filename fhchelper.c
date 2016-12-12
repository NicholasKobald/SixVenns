/*
6-Venns
N. Kobald 2016-11-27
*/	
#include "fhc.h" 
#include "fhchelper.h" 
#include <math.h>
#include <stdio.h>

//Print Adjacency List
void pal(Node GF[FMAX]) {
	int i, j;
	printf("In pal\n");
	for(i=0; i<FMAX; i++){
		printf("Vertex %d: ", i);
		for(j=0;j<GF[i].degree;j++){
			printf(" %d", GF[i].adj_to[j]);
		}
		printf("\n"); 
	}
}

int uses_edge(edge e, edge GD[FMAX][FMAX], int face){ 
	int i;
	for(i=1; i<GD[face][0].v;i++) {
		if(weak_equiv(GD[face][i], e)==1) return 1;
	}
	return 0; 
}


int weak_equiv(edge a, edge b) {
	if(a.v == b.v && a.u==b.u || a.u == b.v && a.v==b.u) return 1;
	return 0;
}

int equalEdge(edge a, edge b) {
	if(a.v == b.v && a.u==b.u) return 1;
	return 0;
}

edge reverse_edge(edge e){
	edge new;
	new.v = e.u;
	new.u = e.v; 
	return new; 
}

void print_faces(edge GD[FMAX][FMAX]) {
	int i, j;
	printf("\nPrinting faces: ");
	for(i=0;i<FMAX;i++){
		printf("Face No. %d is associated with: \n", i);
		for(j=1; j<GD[i][0].v;j++) {
			print_edge(GD[i][j]); 
		}
		printf("\n");
	}
	printf("Done\n"); 
}

void print_edge(edge e){
	printf("v: %d, u: %d\n", e.v, e.u); 
}

//Finds next edge in a face walk of a planar embedding
edge rotate_edge(edge e, int G[NMAX][DEGREE]) {
	int i;
	edge new; 
	for(i=0; i<4; i++){
		if(G[e.u][i]==e.v) {
			new.v = e.u;
			new.u = G[e.u][(i+1)%4];
			return new;
		}
	}
}

edge copy_edge(edge e){
	edge n;
	n.u = e.u;
	n.v = e.v;
	return n; 
}


edge find_next_edge(edge visited[EMAX*2], int G[NMAX][DEGREE], int seen){
	int i, j;
	for(i=0; i<NMAX; i++) {
		for(j=0; j<DEGREE; j++) {
			edge temp;
			temp.v = i;
			temp.u = G[i][j];
			if(contains_edge(temp, visited, seen)==0) 
				return temp; 
		}
	}
}

void print_visited(edge visited[EMAX*2], int seen) {
	int i;
	printf("Current visited list: \n");
	for(i=0;i<seen;i++) {
		print_edge(visited[i]); 
	}
}

int contains_edge(edge check, edge visited[EMAX*2], int seen) {
	int i;
	for(i=0; i<seen;i++){
		edge te = visited[i]; 
		if(check.v == te.v && check.u==te.u) return 1;
	}
	return 0;
}

void load_line_from_file(FILE *fp, int G[NMAX][DEGREE]) {
	char line[1008];
	int i = 5;
	fgets(line, 1000, fp);
	int temp;
	int vertice = 0;
	int j=0;
	while(vertice<NMAX) {
		while(j<4){
			if(line[i] != ' ') {
				temp = atoi(&line[i]);
				G[vertice][j] = temp;
				if(temp>9) i++;
				j++; 
			}
			i++; 
		}
		j=0;
		i = i + 2;
		vertice++;
	}
}
void print_adjlist(int G[NMAX][DEGREE] ) {
	int i, j; 
	printf("\nNMAX: %d", NMAX);
	printf("Printing now:\n"); 

	for(i=0; i<NMAX; i++){
		printf("%d:", i);
		for(j=0;j<DEGREE;j++){
			printf(" %d", G[i][j]);
		}
		printf("\n"); 
	}
	printf("Dont printing"); 
}