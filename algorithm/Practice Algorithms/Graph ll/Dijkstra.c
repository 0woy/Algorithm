/*
이름: 박윤아
작성일: 2022.11.04.

설명: Dijkstra 알고리즘을 이용한 최단경로.
 - 다익스트라 알고리즘의 간선의 가중치는 항상 양수.
 - Greedy approach algorithm
 - 각 스텝별로 가장 적은 비용의 간선 선택

 다익스트라 완성한 거 출력화면이랑 같이 출력
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GrephType {
	int n;			// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];		// 가중치 인접 행렬
}GraphType;


// 시작점을 기준으로 각 정점까지의 가중치, 
// if(start = 0), 0을 기준으로 각 정점까지의 최단 거리
int distance[MAX_VERTICES];

// S = { 0 };
int found[MAX_VERTICES]; // 최단 거리 정점 집합


void shortest_path(GraphType* g, int start);
void print_status(GraphType *g);
int choose(int distance[], int n, int found[]);

int main() {

	printf("학번: 20204624\n이름: 박윤아\n제출일: 2022.11.10.\n\n");

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
	// 초기화: distance, found
	for (int i = 0; i < g->n; i++) {
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	
	// 출발 노드를 S 집합에 추가
	found[start] = TRUE;
	
	// 정점의 개수 만큼 최단 거리 정점 선택하고 distance[] 업데이트 반복
	for (int i = 0; i < g->n; i++) {
		print_status(g);
		
		u = choose(distance, g->n, found); // 1. 최단 거리 정점 선택
		found[u] = TRUE; //  s ={ 0, u }

		// 2. 선택된 정점을 경유했을 때 나머지 정점으로 이동하기 위한 distance[] 업데이트
		for (int i = 0; i < g->n; i++) {
			// i 정점이 아직 선택되지 않고, i 정점까지 u를 경유해서 가는 게 i까지 직접 가는 거리보다 작을 경우
			if (!found[i] && distance[i] > g->weight[u][i] + distance[u])
				distance[i] = g->weight[u][i] + distance[u];	// distance[i] 값 갱신
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

	//static으로 선언하면 함수가 종료되어도 그 값이 휘발되지 않음,
	//즉 다시 함수를 호출했을 때 그 값이 유지.
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