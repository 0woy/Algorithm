/*
�й�: 20204624
�̸�: ������
�ۼ���: 2022.11.04.

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

int weight[MAX_VERTICES][MAX_VERTICES];
int selected[MAX_VERTICES];
int distance[MAX_VERTICES];	// ������� �˷��� ����Ʈ�� ���� ���տ��� �� ���������� �Ÿ�

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

	//data ���Ͽ� ���Ե� ������ ����
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		if (count < temp2)
			count = temp2;
	}
	count += 1; // ������  zero base�̹Ƿ�

	rewind(fp);

	// ����ġ ������� �ʱ�ȭ
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

	//�ʱ�ȭ
	for (u = 0; u < n; u++) {
		distance[u] = INF;
		selected[u] = FALSE;
	}

	//�������� ����
	distance[s] = 0;
	for (int i = 0; i < n; i++) {
		u = get_min_vertex(n);	// ���� ���� ���� ����ġ�� ���� ������ u�� ����
		selected[u] = TRUE;

		if (distance[u] == INF)
			return;
		printf("%d ", u);

		// ���� �������� �ٸ� �������� �� �� �ִ� �Ÿ� update
		for (int v = 0; v < n; v++) {
			if (weight[u][v] != INF) { // u�� v�� ����� �ִ� ���
				if (!selected[v] && weight[u][v] < distance[v]) // v�� ���� ���õ��� �ʰ�, ���� �˷��� �ּ� �Ÿ����� u���� v�� ���� ����ġ�� �� ���� ���
					distance[v] = weight[u][v];	// v�� ���� �ּ� ���� update
			}
		}
	}

}

int get_min_vertex(int n) {

	int v;
	for (int i = 0; i < n; i++) {
		if (!selected[i])	//���� ���õ��� �ʾҴٸ�,
			v = i;	// v�� ����
	}

	for (int i = 0; i < n; i++) {
		if (!selected[i] && distance[i] < distance[v]) // i�� ���õ��� �ʰ�, ���� ����ġ�� v ���� �۴ٸ�,
			v = i;	// v�� i ��� ����
	}
	return v;	// ���� ���� ���� ����ġ�� ���� ���� ��ȯ
}


