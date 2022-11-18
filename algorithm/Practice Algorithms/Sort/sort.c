/*
정렬 프로그램
파일에 학생의 정보가 이름, 학번, 등수 순서로 저장되어 있다.
이를 읽어와 정렬하여 출력.
- 각 정렬은 정해진 양식으로 구현
- 동적 할당을 이용하여 데이터 저장
- 모두 오름차순으로 정렬
- 수행시간을 검사하고 비교

작성일: 2022.11.18.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //이름을 비교할 때

typedef struct Student {
	char* name;
	int id;
	int grade;
}element;

void print(element list[], int n);
void selection_sort(element list[], int n);
void insertion_sort(element list[], int n);
void bubble_sort(element list[], int n);


int main() {

	FILE *fp;
	element tmp;
	element *list;
	char buffer[20]; // 이름 메모리 동적할당을 위한 이름 임시 공간
	int count = 0; // 레코드 갯수(학생 수)

	fp = fopen("Sort.txt", "r");
	if (!fp) {
		printf("CAN NOT OPEN FILE");
		return;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s %d %d", buffer, &tmp.id, &tmp.grade);
		count++;
	}

	list = (element*)malloc(sizeof(element)* count);
	rewind(fp);

	count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s %d %d", buffer, &list[count].id, &list[count].grade);
		int len = strlen(buffer);
		list[count].name = (char*)malloc(sizeof(char)*(len+1));
		strcpy(list[count].name, buffer);
		count++;
	}

	printf("<정렬전>\n");
	print(list, count);
	printf("\n");

	printf("<선택 정렬- 등수순>\n");
	selection_sort(list, count);
	print(list, count);
	printf("\n");

	printf("<삽입 정렬- 학번순>\n");
	insertion_sort(list, count);
	print(list, count);
	printf("\n");

	printf("<버블 정렬- 이름순>\n");
	bubble_sort(list, count);
	print(list, count);
	printf("\n");

	fclose(fp);
	free(list);

	return 0;
}

void print(element list[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%s %d %d\n", list[i].name, list[i].id, list[i].grade);
	}
}

// 성적순 정렬
void selection_sort(element list[], int n) {

	int min;
	element tmp;

	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
			if (list[j].grade < list[min].grade)
				min = j;
		}
		tmp = list[i];
		list[i] = list[min];
		list[min] = tmp;
	}
}

// 학번순 정렬
void insertion_sort(element list[], int n) {
	element tmp;
	int j;

	for (int i = 1; i < n; i++) {
		tmp = list[i];

		for (j = i - 1; j >= 0 && list[j].id > tmp.id; j--)
			list[j + 1] = list[j];

		list[j + 1] = tmp;
	}
}

// 이름순
void bubble_sort(element list[], int n) {
	element tmp;
	int j;

	for (int i = n-1; i >0 ; i--) {
		for (j = 0; j < i; j++) {
			if (strcmp(list[j].name, list[j + 1].name) > 0) {
				tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
		}
	}
}

