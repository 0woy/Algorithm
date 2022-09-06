#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main(void) {

	FILE *fp; //���� ������ ���� ����
	int m_row = 0, m_col = 3; // ����� ũ�⸦ 0���� �ʱ�ȭ
	int **matrix;
	int temp1, temp2, temp3;
	int i, j;

	 
	//data.txt������ �б���� ���� ������  FILE����ü�� fp�� �Ҵ�
	fp = fopen("data.txt", "r"); 

	//���� fopen �Լ����� ������ �߻��Ͽ� fp�� NULL���� ����Ǿ��ٸ� ���� ���� ����
	if (fp == NULL) {
		printf("������ ������ �ʾҽ��ϴ�.\n");
		return 0; //�޼��� ��� �� ���α׷� ����
	}

	// ����� ũ�� ���
	while (!feof(fp)) 
	{
		fscanf(fp, "%d%d%d", &temp1, &temp2, &temp3);
		m_row++;

	}

	//Dynamic �迭�� ũ�⿡ ���� �Ҵ�
	matrix = (int**)malloc(sizeof(int *)* m_row);
	for (i = 0; i < m_row; i++) {
		matrix[i] = (int*)malloc(sizeof(int)*m_col);

	}
	rewind(fp);

	printf("=== �Էµ� ��� ===\n");
	for (int i = 0; i < m_row; i++) {
		for (int j = 0; j < m_col; j++) {
			printf("%3d ", matrix[i][j]);
		}
		printf("\n");
	}

	//Dynamic���� �Ҵ�� �迭 ����
	for (int i = 0; i < m_row; i++)
		free(matrix[i]);
	free(matrix);

	return 0;

}