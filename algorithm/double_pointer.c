#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main(void) {

	FILE *fp; //파일 포인터 변수 선언
	int m_row = 0, m_col = 3; // 행렬의 크기를 0으로 초기화
	int **matrix;
	int temp1, temp2, temp3;
	int i, j;

	 
	//data.txt파일을 읽기모드로 열어 생성된  FILE구조체를 fp에 할당
	fp = fopen("data.txt", "r"); 

	//만약 fopen 함수에서 에러가 발생하여 fp에 NULL값이 저장되었다면 파일 열기 실패
	if (fp == NULL) {
		printf("파일이 열리지 않았습니다.\n");
		return 0; //메세지 출력 후 프로그램 종료
	}

	// 행렬의 크기 계산
	while (!feof(fp)) 
	{
		fscanf(fp, "%d%d%d", &temp1, &temp2, &temp3);
		m_row++;

	}

	//Dynamic 배열의 크기에 따른 할당
	matrix = (int**)malloc(sizeof(int *)* m_row);
	for (i = 0; i < m_row; i++) {
		matrix[i] = (int*)malloc(sizeof(int)*m_col);

	}
	rewind(fp);

	printf("=== 입력된 행렬 ===\n");
	for (int i = 0; i < m_row; i++) {
		for (int j = 0; j < m_col; j++) {
			printf("%3d ", matrix[i][j]);
		}
		printf("\n");
	}

	//Dynamic으로 할당된 배열 해제
	for (int i = 0; i < m_row; i++)
		free(matrix[i]);
	free(matrix);

	return 0;

}
