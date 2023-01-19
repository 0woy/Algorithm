#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX 4

typedef struct {
	int data; 
	int adj_mat[MAX_VERTEX][MAX_VERTEX];
}GraphType;


//Init Graph
void init(GraphType * g) {
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

void main() {

	GraphType *g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	for (int i = 0; i < 4; i++)
		insert_vertex(g,i);

	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);

	print_adj_mat(g);
	free(g);
}