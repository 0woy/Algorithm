#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 50

typedef struct {
	int data;
	struct GraphNode *link;
}GraphNode;

typedef struct {
	int n;	// number of vertices
	GraphNode *adj_list[MAX_VERTICES];
}GraphType;


void init(GraphType *g);
void insert_vertex(GraphType *g, int v);
void insert_edge(GraphType *g, int start, int end);
void print_adj_list(GraphType *g);

int main() {

	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	for (int i = 0; i < 4; i++)
		insert_vertex(g, i);

	insert_edge(g, 0, 1);
	insert_edge(g, 1, 0);
	insert_edge(g, 0, 2);
	insert_edge(g, 2, 0);
	insert_edge(g, 0, 3);
	insert_edge(g, 3, 0);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 3, 2);

	print_adj_list(g);
	free(g);

	return 0;
}

void init(GraphType *g) {
	g->n = 0;	// init vertex to 0

	for (int i = 0; i < MAX_VERTICES; i++) {
		g->adj_list[i]= NULL;
	}

}

void insert_vertex(GraphType* g, int v) {

	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "Exceed The Number of Vertex\n");
		return;
	}
	g->n++;
}
void insert_edge(GraphType *g, int u, int v) {
	GraphNode *node;

	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "Error Vertex Num");
		return;
	}

	node = (GraphNode*)malloc(sizeof(GraphNode));
	if (node == NULL) {
		printf("Fail to allocate Memory");
		return;
	}

	node->data = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void print_adj_list(GraphType*g) {
	for (int i = 0; i < g->n; i++) {
		GraphNode* p = g->adj_list[i];

		printf("정점 %d의 인접 리스트 ", i);

		while (p!= NULL) {
			printf(" -> %d", p->data);
			p = p->link;
		}
		printf("\n");
	}
}