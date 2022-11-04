/*
학번: 20204624
이름: 박윤아
작성일: 2022.11.04.

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

int weight[MAX_VERTICES][MAX_VERTICES];
int selected[MAX_VERTICES];
int distance[MAX_VERTICES];	// 현재까지 알려진 신장트리 정점 집합에서 각 정점까지의 거리

int get_min_vertex(int n);
void prim(int s, int n);

int main() {

	FILE *fp;
	int count = 0;
	int temp1, temp2, temp3; // start, end, weight

	fp = fopen("Kruskal.txt", "r");
	if (!fp) {
		printf("CAN NOT OPEN FILE");
		return 0;
	}

	//data 파일에 포함된 정점의 개수
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		if (count < temp2)
			count = temp2;
	}
	count += 1; // 정점이  zero base이므로

	rewind(fp);

	// 가중치 인접행렬 초기화
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			if (i == j)
				weight[i][j] = 0;
			else
				weight[i][j] = INF;
		}
	}
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		weight[temp1][temp2] = temp3;
		weight[temp2][temp1] = temp3;
	}

	prim(0, count);

	fclose(fp);

	return 0;
}

void prim(int s, int n) {

	int u, v;

	//초기화
	for (u = 0; u < n; u++) {
		distance[u] = INF;
		selected[u] = FALSE;
	}

	//시작정점 설정
	distance[s] = 0;
	for (int i = 0; i < n; i++) {
		u = get_min_vertex(n);	// 현재 가장 작은 가중치를 갖는 정점을 u에 삽입
		selected[u] = TRUE;

		if (distance[u] == INF)
			return;
		printf("%d ", u);

		// 현재 정점에서 다른 정점으로 갈 수 있는 거리 update
		for (int v = 0; v < n; v++) {
			if (weight[u][v] != INF) { // u와 v간 연결돼 있는 경우
				if (!selected[v] && weight[u][v] < distance[v]) // v가 아직 선택되지 않고, 현재 알려진 최소 거리보다 u에서 v로 가는 가중치가 더 작은 경우
					distance[v] = weight[u][v];	// v로 가는 최소 간선 update
			}
		}
	}

}

int get_min_vertex(int n) {

	int v;
	for (int i = 0; i < n; i++) {
		if (!selected[i])	//아직 선택되지 않았다면,
			v = i;	// v에 저장
	}

	for (int i = 0; i < n; i++) {
		if (!selected[i] && distance[i] < distance[v]) // i가 선택되지 않고, 현재 가중치가 v 보다 작다면,
			v = i;	// v에 i 노드 저장
	}
	return v;	// 현재 가장 작은 가중치를 가진 정점 반환
}


