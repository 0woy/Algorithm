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

#include<time.h> // ����ð�

typedef struct Student {
	char* name;
	int id;
	int grade;
}element;

void print(element list[], int n);
void selection_sort(element list[], int n);
void insertion_sort(element list[], int n);
void bubble_sort(element list[], int n);


double selection_time, insertion_time, bubble_time;

int main() {

	FILE *fp;		//������ �о���� ���� ���������� ����
	element tmp;	// �����͸� �ӽ÷� �����ϴ� ����
	element *list;	// �����͸� �����ϴ� �迭
	char buffer[20]; // �̸� �޸� �����Ҵ��� ���� �̸� �ӽ� ����
	int count = 0;	// ���ڵ� ����(�л� ��)

	fp = fopen("random_data.txt", "r");
	if (!fp) {	//������ �о���µ� ������ ���
		printf("CAN NOT OPEN FILE");	//�����޼��� ���
		return;	//����
	}

	while (!feof(fp)){	//������ ó������ ������
		fscanf(fp, "%s %d %d", buffer, &tmp.id, &tmp.grade); // �����͸� �а�
		count++;	//������ ���� ����
	}

	list = (element*)malloc(sizeof(element)* count);	//������ ������ŭ �����Ҵ�
	rewind(fp);	//�ٽ� ������ ó������ �б� ���� rewind

	count = 0; //�迭�� �ε���
	while (!feof(fp)) {
		fscanf(fp, "%s %d %d", buffer, &list[count].id, &list[count].grade);	//�����͸� �о�� ����

		int len = strlen(buffer);		//�о�� �̸��� ���� ���� ����
		list[count].name = (char*)malloc(sizeof(char)*(len+1));	//�о�� �̸��� ũ�⸸ŭ �����Ҵ�
		strcpy(list[count].name, buffer); // �̸��� �����ؼ� �迭�� �ٿ� ����

		count++; //�ε��� ����
	}

	printf("�̸�: ������\n�й�: 20204624\n������: 2022.11.24.\n\n");

	printf("�������� ����: %d\n", count);
//	printf("<������>\n");
	printf("\n");

	printf("<���� ����- �����>\n");
	selection_sort(list, count);
	printf("����ð�: %lf\n\n", selection_time);

	printf("<���� ����- �й���>\n");
	insertion_sort(list, count);
	printf("����ð�: %lf\n\n", insertion_time);

	printf("<���� ����- �̸���>\n");
	bubble_sort(list, count);
	printf("����ð�: %lf\n\n", bubble_time);

	fclose(fp);
	free(list);

	return 0;
}

// �迭 ���� ���
void print(element list[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%s %d %d\n", list[i].name, list[i].id, list[i].grade);
	}
}

// ���������� ����� ���������� ����
void selection_sort(element list[], int n) {

	int min;
	element tmp;
	clock_t start, end; //����ð��� ����ϱ� ���� ����
	 
	start = clock(); //�ð� ���� ����
	for (int i = 0; i < n - 1; i++) {
		min = i;	//��ó�� �ε����� min�� ����
		for (int j = i + 1; j < n; j++) {	//i�� �� ��ҵ��� ũ������� ������ �� ����

			if (list[j].grade < list[min].grade) //���� min ��ġ�� �ִ� �������� j��ġ�� �ִ� ������ ���ٸ�
				min = j;	//min�� j����
		}

		// ���� ũ�Ⱑ ���� ��Ҹ� �� ������ ������
		tmp = list[i]; 
		list[i] = list[min];
		list[min] = tmp;
	}
	end = clock(); //�ð� ���� ����
	selection_time = (double)(end - start) / CLOCKS_PER_SEC;
}

// ���� ������ �̿��� �й��� ����
void insertion_sort(element list[], int n) {
	element tmp;
	int j;

	clock_t start, end;

	start = clock();
	for (int i = 1; i < n; i++) {
		tmp = list[i];	// list[i]��° ��� tmp�� ����

		for (j = i - 1; j >= 0 && list[j].id > tmp.id; j--) //j�� i��° ��� �պ���, 0���� ���� j�� �й��� tmp�� �й����� ũ�ٸ�
			list[j + 1] = list[j];	//j��° ��Ҹ� j+1��° ��ҷ� �־� �ڷ� �б�

		list[j + 1] = tmp;	//�ݺ����� �������� �� j+1��°�� tmp ����.
	}
	end = clock();
	insertion_time = (double)(end - start) / CLOCKS_PER_SEC;
}

// �̸���
void bubble_sort(element list[], int n) {
	element tmp;
	int j;
	clock_t start, end;
	start = clock();

	for (int i = n-1; i >0 ; i--) { //�� �ڿ������� �ݺ�
		for (j = 0; j < i; j++) {	
			if (strcmp(list[j].name, list[j + 1].name) > 0) { //j��°�� �̸��� j+1��°�� �̸����� ���������� �ڿ� �ִٸ�

				// j�� j+1��°�� �ִ� data SWAP
				tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
		}
	}
	end = clock();

	bubble_time = (double)(end - start) / CLOCKS_PER_SEC;
}

