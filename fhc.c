/*


N. Kobald 2016-11-27
*/

#include "fhc.h"
#include "fhchelper.h"
#include <time.h>
//For distance heuristic
extern int vertices_left;
extern int edges_left;

extern int dfo[FMAX];

extern int ham_cycle_count;
extern long int my_hc;

long int print_cutoff = 5000;

/*
Main recursive function
*/
int fhc_five(int startvert, int curvert, Node GF[FMAX], int visited[FMAX],
	int path[FMAX], int dist, n_info conflict_arr[FMAX]) {
	int skip = 0;
	int conflict_number = 0;
	int i, neighbour, forced_edge;
	visited[curvert] = 1;
	path[dist] = curvert;
	dist++;
	if(dist == FMAX) {
		for(i=0;i<GF[curvert].degree;i++) {
			neighbour=GF[curvert].adj_to[i];
			if(neighbour==startvert) {
				//remove the comment below to print the path out when its found
				//print_path(path, dist);
				my_hc++;
				//un-comment the return, to make it only find one cycle.
				//return 1;
				if(my_hc > print_cutoff) {
					printf("At: %ld cycles\n", my_hc);
					print_cutoff = print_cutoff * 2;
				}
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

	if(!is_connected(GF, visited, curvert, startvert)) {
		skip = 1;
	}
	if(skip==0 && conflict_number==1) {
		skip=1;
		if(fhc_five(0, forced_edge, GF, visited, path, dist, conflict_arr)==1) {
			return 1;
		}
	} else if(conflict_number>1) {
		skip = 1;
	}
	//Prune?
	if(((conflict_arr[startvert].used_degree == conflict_arr[startvert].max_degree) && dist<FMAX-1)) {
		skip = 1;
	}

	//Recurse
	if (skip==0) {
		for(i=0; i<GF[curvert].degree;i++) {
			neighbour = GF[curvert].adj_to[i];
			if(visited[neighbour] == 0) {
				if(fhc_five(0, neighbour, GF, visited, path, dist, conflict_arr)==1) {
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

/*
Permute array based on permutation in mapping.
*/
void relabel_graph(Node G[FMAX], Node GR[FMAX], int map[FMAX]){
	int i,j, vertex, d;
	for(i = 0; i<FMAX; i++) {
		vertex = map[i];
		GR[vertex].degree = G[i].degree;
		for(j = 0; j<G[i].degree; j++) {
			GR[vertex].adj_to[j] = map[G[i].adj_to[j]];
		}
	}
}


/*
Populate distance array with distance from vertex 0.
Why did I think this would help me?
*/
void create_distance_arr(Node G[FMAX], int da[FMAX]) {
	int bfs_que[FMAX], visited[FMAX];
	int i;

	//init
	for(i=0;i<FMAX;i++) {
		bfs_que[i] = -1;
		da[i] = -1;
		visited[i] = 0;
	}

	int dist, cur, q_start, q_end, neighbour;
	dist = cur = q_start = q_end = 0;

	visited[0] = 1;
	da[0] = 0;
	while(q_start<=q_end) {
		for(i = 0; i<G[cur].degree; i++){
			neighbour = G[cur].adj_to[i];
			if(visited[neighbour] == 0) { // Unvisited
				da[neighbour] = da[cur] + 1;
				bfs_que[q_end++] = neighbour;
				visited[neighbour] = 1;
			}
		}
		cur = bfs_que[q_start++];
	}
}

/*
Populate mapping array with a permutation of our vertices based on a
BFS on the graph.
*/
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

	int neighbour, seen, cur, q_start, q_end;
	seen = cur = q_start = q_end = 0;

	visited[0] = 1;
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



int is_connected_dfs(Node GF[FMAX], int visited[FMAX], int curvert, int num_visited) {
	int vis_local[FMAX];
	int i, dfsdepth, neighbour;
	dfsdepth = 0;

	for(i = 0; i<FMAX; i++) {
		vis_local[i] = visited[i];
	}
	/* Pick first neighbour in for dfs. */
	for(i = 0; i<GF[curvert].degree; i++) {
		neighbour = GF[curvert].adj_to[i];
		if(vis_local[neighbour] == 0) break;
	}
	vis_local[curvert] = 1;

	int dfs_counter;
	dfs_counter = recursive_dfs(GF, vis_local, neighbour) + 1;
	if(dfs_counter+num_visited == FMAX) return 0;
	return 1;
}

int recursive_dfs(Node GF[FMAX], int vis_local[FMAX], int curvert) {
	int i, neighbour;
	int num_found = 1;
	vis_local[curvert] = 1;
	for(i = 0; i<GF[curvert].degree; i++) {
		neighbour = GF[curvert].adj_to[i];
		if(vis_local[neighbour] == 0) {
			num_found += recursive_dfs(GF, vis_local, neighbour);
		}
	}
	return num_found;
}


/*
BFS to check if there exists any path to the start vertex,
using only vertices not yet in our cycle.
*/
int is_connected(Node GF[FMAX], int visited[FMAX], int curvert, int startvert) {
	int i;
	int vis_local[FMAX], bfs_que[FMAX];

	for (i = 0; i < FMAX; i++) {
		vis_local[i] = visited[i];
		bfs_que[i] = -1;
	}

	int neighbour, seen, cur, q_start, q_end;
	seen = cur = q_start = q_end = 0;
	/* Pretend start vertex is unvisited, and see if we ever reach it. */

	vis_local[startvert] = 0;
	vis_local[curvert] = 1;
	cur = curvert;
	while(q_start<=q_end) {
		for(i = 0; i<GF[cur].degree; i++){
			neighbour = GF[cur].adj_to[i];
			/* Found start vertex */
			if(neighbour == startvert) return 1;

			if(vis_local[neighbour] == 0) {
				bfs_que[q_end++] = neighbour;
				vis_local[neighbour] = 1;
			}
		}
		cur = bfs_que[q_start++];
	}
	return 0;
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

/*
Populate GF with the graph corresponding to GD.
*/
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
