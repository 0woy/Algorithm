/*
�й�: 20204624
�̸�: ������
������: 2022.11.03.

����: ���Ͽ��� �����͸� �о��
Prim �˰����� �̿��� �̵� ���� ����ϱ�.

- ���� ���� ��ŭ �ݺ�, Prim: Greedy algorithm
- ���� �������� ����Ͽ� ������ ������ ������ ������ ���� ���� ����ġ ���� ���� �ݺ�

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
	int n; //������ ����
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

//�ּ� dist[v] ���� ���� ������ ��ȯ
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
		printf("���� %d �߰�\n", u);

		//���� �߰��� ��忡�� �� �� �ִ� �������� ������ ���̰� ���� �����ϴ� ������ ���̺��� ª�ٸ�
		// distance ������Ʈ.
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