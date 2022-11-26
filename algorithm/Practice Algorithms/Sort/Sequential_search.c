/*
프로그램 설명: 순차탐색과 개선된 순차탐색을 작성하여
약 10000000개의 정수들의 탐색 시간을 비교.

이름: 0woy
작성일: 2022.11.25.
*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>	//수행 시간 비교를 위한 헤더파일

typedef int element;

int flag_s, flag_i; //배열 안에 찾고자 하는 요소가 있는지 확인하는 flag 변수(-1: 요소가 없음)
clock_t  start_s, end_s, start_i, end_i;

//함수 원형 선언
int sequential(element arr[], int key, int count);			//순차탐색
int improved_sequential(element arr[], int key, int count);	//개선된 순차탐색

int main() {

	printf("이름: 박윤아\n학번: 20204624\n제출일: 2022.11.26.\n\n");

	FILE *fp; // 데이터 파일을 읽어오기 위한 파일 포인터 선언
	element tmp; // 임시로 데이터를 읽기 위한 변수 선언
	element *data; //데이터를 저장하기 위한 배열 선언
	int count = 0; //파일에 있는 데이터의 갯수를 세는 변수
	int key; //찾고자 하는 요소


	fp = fopen("Sequential_data.txt", "r"); // 데이터 파일 읽어오기

	if (!fp) { //만일 파일이 비어있다면(없다면)
		printf("CAN NOT OPEN FILE"); // 에러메세지 출력
		return; // 프로그램 종료
	}

	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp); //데이터를 읽어와 tmp에 저장
		count ++; // 데이터 갯수 증가
	}

	rewind(fp); //배열에 데이터를 저장하기 위해 파일 포인터를 파일의 맨 위로 다시 올림
	data = (element*)malloc(sizeof(element)*(count+1)); //데이터의 개수만큼 메모리 동적할당
	
	int i = 0; //배열의 인덱스
	while (!feof(fp)) {
		fscanf(fp, "%d", &data[i++]);  //데이터를 읽어와 배열에 저장
	}

	printf("데이터의 개수: %d\n", count);
	printf("찾고자 하는 요소를 입력하세요 >>");
	scanf("%d", &key);

		
	sequential(data, key,count);	// 순차탐색 호출
	end_s = clock();		// 시간 측정 종료

		
	improved_sequential(data, key,count);		//개선된 순차탐색 호출
	end_i = clock();		//시간 측정 종료


	float result1 = (float)(end_s - start_s) / CLOCKS_PER_SEC;
	float result2 = (float)(end_i- start_i) / CLOCKS_PER_SEC;

	if (flag_s != -1 && flag_i != -1) {
		printf("\n탐색 성공!!\n");
		printf("순차 탐색: %f\n", result1);
		printf("개선된 순차 탐색: %f\n", result2);
	}
	else
		printf("탐색 실패!");

	free(data); //동적 할당 해제
	fclose(fp);	//파일 닫기


	return 0;
}

int sequential(element arr[], int key, int count) {

	start_s = clock();	// 시간 측정 시작
	for (int i = 0; i < count; i++) { // 배열의 끝까지 돌면서
		if (arr[i] == key)			// 요소를 찾았다면
			return i;				// return index	
	}
	return -1; //찾지 못했다면 -1 return
}

int improved_sequential(element arr[], int key, int count) {
	
	int i;
	arr[count] = key;	//찾는 요소를 배열의 맨 끝에 넣는다.

	start_i = clock(); 	//시간 측정 시작
	for (i = 0; arr[i] != key; i++)	// index 0 부터 key를 찾을 때까지 반복
		;
	if (i == (count)) return -1;	// for문이 끝난후 만일 index가 count와 같다면 탐색에 실패했으므로 -1 return
	else return i;	// 그렇지 않다면 return index
	
}
