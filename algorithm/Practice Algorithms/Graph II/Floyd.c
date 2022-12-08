/*
�ִ� ��� �˰���: Dijkstra, Floyd
- Floyd: ��� �������� ��� �������� ���� �ִ� ��� ���� �� ���.

��� ������ �˰� ���� �� = Dijkstra
��� ����ϴ��� �� �� ���� �� = Floyd

�ۼ���: 2022.11.11.
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define INF 100000
#define MAX_VERTICES 7

int a[MAX_VERTICES][MAX_VERTICES];	// �ݺ� �ϸ鼭 ����ġ�� ������Ʈ ��
int weight[MAX_VERTICES][MAX_VERTICES]; //���� ����ġ ����


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
		printf("���� %d ������ �ִ� �Ÿ�\n", k);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (a[i][j] > a[i][k] + a[k][j]) //�����ϴ� �� �� ������
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

