/*
학번: 20204624
이름: 박윤아

문제: 동적 메모리 할당과 포인터를 이용해 값 변경하기
*/

#include<stdio.h>
#include<stdlib.h> // malloc, free 함수가 선언된 헤더파일

void allocMemory(int **ptr, int m_size) {

	*ptr = (int *)malloc(sizeof(int)*m_size);

	for (int i = 0; i < m_size; i++) {
		(*ptr)[i] = (i + 1) * 10;

	}

	printf("=== allocMemory 함수 내에서 출력 === \n");
	for (int i = 0; i < m_size; i++) {
		printf("%d\n", (*ptr)[i]);
	}
}

int main() {

	int *numPtr;
	int size = 10;

	allocMemory(&numPtr, size); //포인터 numPtr의 주소값을 보냄

	for (int i = 0; i < size; i++) {
		numPtr[i] = numPtr[i] + 1;
	}

	printf("=== main 함수 내에서 출력 ===\n");
	for (int i = 0; i < size; i++) {
		printf("%d\n", numPtr[i]);
	}

	free(numPtr);

	return 0;
}