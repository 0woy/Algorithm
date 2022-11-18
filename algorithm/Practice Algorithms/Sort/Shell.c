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

	FILE *fp;
	element tmp;
	element *list;
	char buffer[20]; // 이름 메모리 동적할당을 위한 이름 임시 공간
	int count = 0; // 레코드 갯수(학생 수)

	fp = fopen("shell.txt", "r");
	if (!fp) {
		printf("CAN NOT OPEN FILE");
		return;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s %d %s", buffer, &tmp.id, tmp.phone);
		count++;
	}

	list = (element*)malloc(sizeof(element)* count);
	rewind(fp);

	count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s %d %s", buffer, &list[count].id, list[count].phone);
		int len = strlen(buffer);
		list[count].name = (char*)malloc(sizeof(char)*(len + 1));
		strcpy(list[count].name, buffer);
		count++;
	}

	printf("<정렬전>\n");
	print(list, count);
	printf("\n");

	printf("<쉘 정렬- 학번순>\n");
	shell_sort(list, count);
	print(list, count);
	printf("\n");



	fclose(fp);
	free(list);

	return 0;
}

void print(element list[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%s %d %s\n", list[i].name, list[i].id, list[i].phone);
	}
}

void insertion_sort(element list[], int first, int last, int gap) {
	element tmp;
	int j;
	
	for (int i = first + gap; i <= last; i = i + gap) {
		tmp = list[i];

		for (j = i - gap; j >= first && list[j].id > tmp.id; j = j - gap)
			list[j + gap] = list[j];

		list[j + gap] = tmp;
	}
}

void shell_sort(element list[], int n) {

	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if (gap % 2 == 0) gap+=1;

		for (i = 0; i < gap; i = i++) {
			insertion_sort(list,i,n-1, gap);
		}
	}
}

