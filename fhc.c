/*
N. Kobald 2016-11-27

*/

#include "fhc.h" 
#include "fhchelper.h" 

int fhc_five(int startvert, int curvert, Node GF[FMAX], int visited[FMAX],
	int path[FMAX], int dist, n_info conflict_arr[FMAX]) {
	visited[curvert] = 1;
	int conflict_number = 0;
	int forced_edge; 
	int i, neighbour;
	int skip = 0 ;
	path[dist] = curvert; 
	dist++; 
	if(dist == FMAX) {
		for(i=0;i<GF[curvert].degree;i++) {
			neighbour=GF[curvert].adj_to[i]; 
			if(neighbour==startvert) {
				printf(" Soln found. \n");
				return 1; 

			} 
		}
	}
	for(i=0; i<GF[curvert].degree;i++) {
		neighbour=GF[curvert].adj_to[i]; 
		conflict_arr[neighbour].used_degree++;
		if((visited[neighbour] == 0 || (neighbour == startvert && dist+1 == FMAX)) &&
			conflict_arr[neighbour].used_degree == conflict_arr[neighbour].max_degree) {
			conflict_number++;
			forced_edge = neighbour; 
		}	
	}
	if(conflict_number==1) {
		skip=1;
		if(fhc_five(0, forced_edge, GF, visited, path, dist, conflict_arr)==1) {
			return 1; 
		}
	} else if(conflict_number>1) {
		skip = 1; 
	}
	if (skip==0) {
		for(i=0; i<GF[curvert].degree;i++) {
			neighbour = GF[curvert].adj_to[i]; 
			if(visited[neighbour] == 0) {
				if( fhc_five(0, neighbour, GF, visited, path, dist, conflict_arr)==1) {
					return 1;
				} 
			} 
		}
	} 

	for(i=0; i<GF[curvert].degree;i++) {
		neighbour=GF[curvert].adj_to[i]; 
		conflict_arr[neighbour].used_degree--; 
	}
	dist--;
	path[dist] = -1; 
	visited[curvert] = 0;
	return 0;	
}

void relabel_graph(Node G[FMAX], int map[FMAX]){
	int i,j, neighbour; 
	for(i = 0; i<FMAX; i++) {
		for(j = 0; j<G[i].degree; j++) {
			G[i].adj_to[j] = map[G[i].adj_to[j]]; 
		}
	}
}
void create_bfs_labeling(Node GF[FMAX], int mapping[FMAX]) { 
	int bfs_que[FMAX];
	int visited[FMAX]; 
	int i;
	//init 
	for(i=0;i<FMAX;i++) {
		bfs_que[i] = -1; 
		mapping[i] = -1;
		visited[i] = 0;
	}

	int neighbour; 
	int seen = -1; 
	int cur = 0;
	int q_start = 0;
	int q_end = 0;

	while(q_start<=q_end) {
		mapping[cur] = seen++;
		for(i = 0; i<GF[cur].degree; i++){
			neighbour = GF[cur].adj_to[i]; 
			if(visited[neighbour] == 0) { // Unvisited 
				bfs_que[q_end++] = neighbour;
				visited[neighbour] = 1; 
			}
		}
		cur = bfs_que[q_start++]; 
	}
}

void print_path(int path[FMAX], int len) {
	int i;
	for(i=0; i<len;i++){
		printf("%d ", path[i]); 
	}
	printf("\n"); 
}
int all_visited(int visited[FMAX]) {
	int i;
	for(i=0; i<FMAX;i++){
		if(visited[i]==0) {
			return 0; 
		}
	}
	return 1;
}
/*
	Index 0 in GD will be degree of the face. 
*/
void compute_dual(int G[NMAX][DEGREE], 	Node GF[FMAX]){
	edge visited[EMAX*2];
	int num_inserted = 0;
	edge GD[FMAX][FMAX]; 
	int i, j;
	edge next, start;
	int count_faces = 0;
	while(num_inserted<EMAX*2) {
		i = 1;
		next = find_next_edge(visited, G, num_inserted);
		start = copy_edge(next); //thats the start edge
		visited[num_inserted++]=copy_edge(next); //put it in visited
		GD[count_faces][i++] = copy_edge(next); 
		next = rotate_edge(next, G); //rotate once to start

		while(equalEdge(start, next)==0) { //rotate till we get back to the start
			visited[num_inserted++] = copy_edge(next);
			GD[count_faces][i++] = copy_edge(next); 
			next = rotate_edge(next, G); 
		}
		//Use an edge to store the degree temporararily b/c I'm scared of structs
		edge count;
		count.v = i;
		count.u = -1; 
		GD[count_faces][0] = count; 
		count_faces++; 
	}
	construct_adjlist(GD, GF);	
}

void construct_adjlist(edge GD[FMAX][FMAX], Node GF[FMAX]) {
	int i, j, k;
	edge curedge; 
	for(i=0; i<FMAX;i++){
		GF[i].degree = GD[i][0].v-1; 
		for(j=1;j<GF[i].degree+1;j++){
			curedge = GD[i][j]; 
			for(k=0;k<FMAX;k++){
				if(uses_edge(curedge, GD, k) == 1 && i!=k) 
					GF[i].adj_to[j-1]=k;
			}
		}
	}
}
