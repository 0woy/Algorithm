/*
학번: 20204624
이름: 박윤아
제출일: 2022.11.03.

설명: 파일에서 데이터를 읽어와
Prim 알고리즘을 이용해 이동 정점 출력하기.

- 정점 개수 만큼 반복, Prim: Greedy algorithm
- 시작 정점에서 출발하여 마지막 정점에 도달할 때까지 가장 작은 가중치 정점 선택 반복

*/


#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct {
	int key;
	int u;
	int v;
}element;

typedef struct {
	element heap[MAX_VERTICES];
	int heap_size;
}HeapType;

typedef struct GraphType {
	int n; //정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

void init_g(GraphType* g, int n) {
	g->n = n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			g->weight[i][j] = INF;
	}
}

//최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n) {
	int v, i;
	for (int i = 0; i < n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}

	for (int i = 0; i < n; i++) {
		if (!selected[i] && (distance[i] < distance[v]))
			v = i;
	}

	return v;
}

void prim(GraphType* g, int s) {

	int u, v;
	for (u = 0; u < g->n; u++)
		distance[u] = INF;

	distance[s] = 0;
	for (int i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = TRUE;
		if (distance[u] == INF) return;
		printf("정점 %d 추가\n", u);

		//새로 추가된 노드에서 갈 수 있는 정점들의 간선의 길이가 현재 존재하는 간선의 길이보다 짧다면
		// distance 업데이트.
		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF) {
				if (!selected[v] && g->weight[u][v] < distance[v])
					distance[v] = g->weight[u][v];
			}
	}
}

int main() {
	FILE *fp;
	GraphType *g;
	int count = 0;
	g = (GraphType*)malloc(sizeof(GraphType));
	g->n = 0;

	fp = fopen("Kruskal.txt", "r");
	int u, v, weight;
	if (fp == NULL) {
		fprintf(stderr, "CAN NOT OPEN FILE");
		return;
	}

	int max = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &u, &v, &weight);
		if (max < v)
			max = v;
	}
	rewind(fp);
	init_g(g, max + 1);

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &u, &v, &weight);
		g->weight[u][v] = g->weight[v][u] = weight;
	}

	prim(g, 0);
}