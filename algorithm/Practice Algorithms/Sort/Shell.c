/*
쉘 정렬 프로그램

작성일: 2022.11.18.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
	char* name;
	int id;
	char phone [20];
}element;

void print(element list[], int n);
void insertion_sort(element list[], int n);
void shell_sort(element list[], int n);

int main() {

	FILE *fp;	//파일을 읽어오기위한 파일포인터 선언
	element tmp;	// 임시로 데이터를 읽어오기 위한 변수
	element *list;	// 데이터를 저장할 배열
	char buffer[20]; // 이름 메모리 동적할당을 위한 이름 임시 공간
	int count = 0; // 레코드 갯수(학생 수)

	fp = fopen("shell.txt", "r");

	if (!fp) {	//파일을 읽어오는데 실패한 경우	
		printf("CAN NOT OPEN FILE");	//에러 메세지 출력
		return;	//종료
	}

	while (!feof(fp)) {	//파일의 처음부터 끝까지
		fscanf(fp, "%s %d %s", buffer, &tmp.id, tmp.phone); 
		count++;	// 레코드 갯수 증가
	}

	list = (element*)malloc(sizeof(element)* count); //파일에 저장된 레코드 수만큼 동적할당
	rewind(fp);	//파일을 다시 처음부터 읽기위해 맨 처음으로 이동

	count = 0;	// 배열의 인덱스 

	while (!feof(fp)) {
		fscanf(fp, "%s %d %s", buffer, &list[count].id, list[count].phone);

		int len = strlen(buffer); //문자열 길이 저장
		list[count].name = (char*)malloc(sizeof(char)*(len + 1)); //문자열 길이 만큼 동적할당
		strcpy(list[count].name, buffer);	//배열에 문자열 복사
		count++;
	}

	printf("<정렬전>\n");
	print(list, count);
	printf("\n");

	printf("<쉘 정렬- 학번순>\n");
	shell_sort(list, count);
	print(list, count);
	printf("\n");

	fclose(fp); //파일 닫기
	free(list);	//동적 할당 해제

	return 0;
}

// 배열 상태 출력
void print(element list[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%s %d %s\n", list[i].name, list[i].id, list[i].phone);
	}
}

//삽입 정렬
void insertion_sort(element list[], int first, int last, int gap) {
	element tmp;
	int j;
	
	for (int i = first + gap; i <= last; i = i + gap) {	//
		tmp = list[i];

		for (j = i - gap; j >= first && list[j].id > tmp.id; j = j - gap)
			list[j + gap] = list[j];

		list[j + gap] = tmp;
	}
}

//쉘 정렬
void shell_sort(element list[], int n) {

	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) { //gap을 절반씩 줄여나가면서 0이상일 때까지 반복
		if (gap % 2 == 0) gap+=1;	// gap이 짝수인 경우 홀수로 설정

		for (i = 0; i < gap; i = i++) {	//gap만큼 반복
			insertion_sort(list,i,n-1, gap);	//삽입 정렬 호출
		}
	}
}

