/*

4-Venns. 
N. Kobald 2016-11-27
*/
#include <stdio.h>
#include "fhc.h" 
#include "fhchelper.h"



int main(int argc, char *argv[]){
	//printf("Welcome to the Venn Store.\n");
	FILE *fp = fopen(argv[1], "r");
	int p;
	int numgraphs = 0;
	int G [NMAX][DEGREE];
	Node GF[FMAX]; 

	load_line_from_file(fp, G);

	compute_dual(G, GF); 
	//printf("New print statement"); 

	int visited[FMAX];
	n_info conflict_arr[FMAX];
	int i;

	for(i=0;i<FMAX;i++){
		visited[i] = 0;
		conflict_arr[i].used_degree = 0;
		conflict_arr[i].max_degree = GF[i].degree;
		//printf(" max degree: %d, \n", conflict_arr[i].max_degree);
	}
	pal(GF);

	int path[FMAX]; 
	for(i=0;i<FMAX;i++) path[i] = -1; 
	int dist = 0; 
	int map[FMAX]; 

	
	create_bfs_labeling(GF, map);
	for(i = 0; i<FMAX; i++){ 
		printf("%d ", map[i]);
	}
	relabel_graph(GF, map); 
	pal(GF); 
	printf("Starting fhc.\n");

	if(fhc_five(0, 0, GF, visited, path, dist, conflict_arr) == 1) {
		//printf("Successful"); 
	} else {
		//printf("No HC found.");
	}
	printf("\n"); 
	for(i=0;i<FMAX;i++){
		printf("%d ", path[i]); 		
	}
}