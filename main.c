/*
6-Venns.
N. Kobald 2016-11-27
*/
#include <stdio.h>
#include "fhc.h"
#include "fhchelper.h"
#include <time.h>
int vertices_left;
int edges_left;

int dfo[FMAX];

int ham_cycle_count;

long int my_hc;

/*  Main */
int main(int argc, char *argv[]){
	FILE *fp = fopen(argv[1], "r");
	int p;
	int numgraphs = 0;
	int G [NMAX][DEGREE];
	Node GF[FMAX];
	Node G_rel[FMAX];

	time_t seconds;
	time_t seconds_after;
	my_hc = 0;
	int visited[FMAX];
	n_info conflict_arr[FMAX];
	int path[FMAX], map[FMAX];
	int i;
	int total_count = 0;
	clock_t start, end, overallstart, overallend;
	int dist = 0;
	int count = 0;
	overallstart = clock();
	while(load_line_from_file(fp, G)==1) {

		compute_dual(G, GF);
		dist = 0;

		for(i=0;i<FMAX;i++){
			path[i] = -1;
			dfo[i] = -1;
			visited[i] = 0;
			conflict_arr[i].used_degree = 0;
			conflict_arr[i].max_degree = GF[i].degree;
		}

		vertices_left= 64;
		edges_left = 124;
		seconds = time(NULL);

		ham_cycle_count=0;
		//printf("Path: \n");
		start = clock();
		printf("(%d)\n",ham_cycle_count );
		if(!fhc_five(0, 0, GF, visited, path, dist, conflict_arr)==1) {
			printf("Did NOT find cycle in graph: %d", count++);
		}

		end = clock();
		printf("%f\n", ((double)(end-start))/CLOCKS_PER_SEC);
		printf(" Ham Cycle Count: %ld\n", my_hc);
		fflush( stdout );


	}

	overallend = clock();
	printf("\nTotalTime:\n %f", ((double)(overallend-overallstart))/CLOCKS_PER_SEC);

}
