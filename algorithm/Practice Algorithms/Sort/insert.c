/*
���� ���α׷�
���Ͽ� �л��� ������ �̸�, �й�, ��� ������ ����Ǿ� �ִ�.
�̸� �о�� �����Ͽ� ���.
- �� ������ ������ ������� ����
- ���� �Ҵ��� �̿��Ͽ� ������ ����
- ��� ������������ ����
- ����ð��� �˻��ϰ� ��

�ۼ���: 2022.11.18.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //�̸��� ���� ��

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
	char buffer[20]; // �̸� �޸� �����Ҵ��� ���� �̸� �ӽ� ����
	int count = 0; // ���ڵ� ����(�л� ��)

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

	printf("<������>\n");
	print(list, count);
	printf("\n");

	printf("<���� ����- �����>\n");
	selection_sort(list, count);
	print(list, count);
	printf("\n");

	printf("<���� ����- �й���>\n");
	insertion_sort(list, count);
	print(list, count);
	printf("\n");

	printf("<���� ����- �̸���>\n");
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

// ������ ����
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

// �й��� ����
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

// �̸���
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

