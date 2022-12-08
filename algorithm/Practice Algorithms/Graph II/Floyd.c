/*
최단 경로 알고리즘: Dijkstra, Floyd
- Floyd: 모든 정점에서 모든 정점까지 가는 최단 경로 구할 때 사용.

출발 정점을 알고 있을 때 = Dijkstra
어디서 출발하는지 알 수 없을 때 = Floyd

작성일: 2022.11.11.
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define INF 100000
#define MAX_VERTICES 7

int a[MAX_VERTICES][MAX_VERTICES];	// 반복 하면서 가중치를 업데이트 함
int weight[MAX_VERTICES][MAX_VERTICES]; //원본 가중치 저장


void floyd(int n) {		//number of vertex
	
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			a[i][j] = weight[i][j];
		
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			if (a[i][j] == INF)
				printf("*    ");
			else
				printf("%-4d ", a[i][j]);

		}
		printf("\n");
	}

	//floyd 
	//min(A[i][j] , a[i][k] + a[k][j])
	//triple loop i, j, k

	for (int k = 0; k < n; k++) {
		printf("정점 %d 경유한 최단 거리\n", k);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (a[i][j] > a[i][k] + a[k][j]) //경유하는 게 더 작으면
					a[i][j] = a[i][k] + a[k][j];

				if (a[i][j] == INF)
					printf("*    ");
				else
					printf("%-4d ", a[i][j]);
			
			}
			printf("\n");
		}
		printf("\n");
	}
	
}


int main() {
	FILE *fp;
	fp = fopen("Floyd.txt", "r");

	if (!fp) {
		printf("CAN NOT OPEN FILE");
		return;
	}

	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			if (i == j)
				weight[i][j] = 0;
			weight[i][j] = INF;	
		}
	}
	int from, to, w;

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &from, &to, &w);
		weight[from][to] = w;
		weight[to][from] = w;
	}

	floyd(7);

}

