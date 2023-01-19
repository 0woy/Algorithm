#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


#define MAX_VERTEX 50

typedef struct {
	int data;
	int adj_mat[MAX_VERTEX][MAX_VERTEX];
}GraphType;

bool visited[MAX_VERTEX];

//Declare function prototype
void init_graph(GraphType * g);
void insert_vertex(GraphType* g, int item);
void insert_edge(GraphType *g, int start, int end);
void print_adj_mat(GraphType *g);
void bfs_mat(GraphType*g, int v);

void main() {

	GraphType *g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init_graph(g);

	for (int i = 0; i < 6; i++)
		insert_vertex(g, i);

	insert_edge(g, 0, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 0, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 1, 5);

		print_adj_mat(g);
	printf("Breadth First Search\n");
	//bfs_mat(g, 0); // start dfs from 0
	free(g);
}


//Init Graph
void init_graph(GraphType * g) {
	g->data = 0;
	for (int i = 0; i < MAX_VERTEX; i++) {
		for (int j = 0; j < MAX_VERTEX; j++) {
			g->adj_mat[i][j] = 0;
		}
	}
}

//Insert Node
void insert_vertex(GraphType* g, int item) {
	if (((g->data) + 1) > MAX_VERTEX) {
		fprintf(stderr, "Graph: Exceed The Number of Vertex");
		return;
	}

	g->data++;
}

//Insert Edge
void insert_edge(GraphType *g, int start, int end) {
	if (start >= g->data || end >= g->data) {	//if parameters exceed current graph's data_num 
		fprintf(stderr, "Graph: Vertex Number Error"); //print error message
		return;
	}
	//when the graph is undirected graph
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

//display adj_mat
void print_adj_mat(GraphType *g) {

	for (int i = 0; i < g->data; i++) {
		for (int j = 0; j < g->data; j++) {
			printf("%2d", g->adj_mat[i][j]);
		}
		printf("\n");
	}

}

void bfs_mat(GraphType*g, int v) {

	QueueType q;
	init_q(&q);


	visited[v];
	printf("%d ¹æ¹® -> ", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (int w = 0; w < g->data; w++) {
			if ((g->adj_mat[v][w]) && !visited[w])
				visited[w] = true;
				enqueue(&q, w);
	
		}
	}
}