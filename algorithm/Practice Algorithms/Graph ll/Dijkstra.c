/*
�̸�: ������
�ۼ���: 2022.11.04.

����: Dijkstra �˰����� �̿��� �ִܰ��.
 - ���ͽ�Ʈ�� �˰����� ������ ����ġ�� �׻� ���.
 - Greedy approach algorithm
 - �� ���ܺ��� ���� ���� ����� ���� ����

 ���ͽ�Ʈ�� �ϼ��� �� ���ȭ���̶� ���� ���
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GrephType {
	int n;			// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];		// ����ġ ���� ���
}GraphType;


// �������� �������� �� ���������� ����ġ, 
// if(start = 0), 0�� �������� �� ���������� �ִ� �Ÿ�
int distance[MAX_VERTICES];

// S = { 0 };
int found[MAX_VERTICES]; // �ִ� �Ÿ� ���� ����


void shortest_path(GraphType* g, int start);
void print_status(GraphType *g);
int choose(int distance[], int n, int found[]);

int main() {

	printf("�й�: 20204624\n�̸�: ������\n������: 2022.11.10.\n\n");

	GraphType g = {
		7,
	{
		{0,7,INF,INF,3,10,INF},
		{7,0,4,10,2,6,INF},
		{INF,4,0,2,INF,INF,INF},
		{INF,10,2,0,11,9,4},
		{3,2,INF,11,0,INF,5},
		{10,6,INF,9,INF,0,INF},
		{INF,INF,INF,4,5,INF,0}
	}
	};

	shortest_path(&g, 0);
}


void shortest_path(GraphType* g, int start) {
	int u, v;
	// �ʱ�ȭ: distance, found
	for (int i = 0; i < g->n; i++) {
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	
	// ��� ��带 S ���տ� �߰�
	found[start] = TRUE;
	
	// ������ ���� ��ŭ �ִ� �Ÿ� ���� �����ϰ� distance[] ������Ʈ �ݺ�
	for (int i = 0; i < g->n; i++) {
		print_status(g);
		
		u = choose(distance, g->n, found); // 1. �ִ� �Ÿ� ���� ����
		found[u] = TRUE; //  s ={ 0, u }

		// 2. ���õ� ������ �������� �� ������ �������� �̵��ϱ� ���� distance[] ������Ʈ
		for (int i = 0; i < g->n; i++) {
			// i ������ ���� ���õ��� �ʰ�, i �������� u�� �����ؼ� ���� �� i���� ���� ���� �Ÿ����� ���� ���
			if (!found[i] && distance[i] > g->weight[u][i] + distance[u])
				distance[i] = g->weight[u][i] + distance[u];	// distance[i] �� ����
		}

	}
}

int choose(int distance[], int n, int found[]) {

	int min = INF;
	int minpos = -1;

	for(int i=0;i<n;i++){
		if (!found[i] && distance[i] < min) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}


void print_status(GraphType *g) {

	//static���� �����ϸ� �Լ��� ����Ǿ �� ���� �ֹߵ��� ����,
	//�� �ٽ� �Լ��� ȣ������ �� �� ���� ����.
	static int step = 1; 

	printf("STEP: %d: ", step++);
	printf("distance: ");

	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	

	printf("\nfound: ");
	
	for (int i = 0; i < g->n; i++) {
		printf("%2d", found[i]);
	}
	printf("\n");
}