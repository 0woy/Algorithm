/*
�� ���� ���α׷�

�ۼ���: 2022.11.18.
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

	FILE *fp;	//������ �о�������� ���������� ����
	element tmp;	// �ӽ÷� �����͸� �о���� ���� ����
	element *list;	// �����͸� ������ �迭
	char buffer[20]; // �̸� �޸� �����Ҵ��� ���� �̸� �ӽ� ����
	int count = 0; // ���ڵ� ����(�л� ��)

	fp = fopen("shell.txt", "r");

	if (!fp) {	//������ �о���µ� ������ ���	
		printf("CAN NOT OPEN FILE");	//���� �޼��� ���
		return;	//����
	}

	while (!feof(fp)) {	//������ ó������ ������
		fscanf(fp, "%s %d %s", buffer, &tmp.id, tmp.phone); 
		count++;	// ���ڵ� ���� ����
	}

	list = (element*)malloc(sizeof(element)* count); //���Ͽ� ����� ���ڵ� ����ŭ �����Ҵ�
	rewind(fp);	//������ �ٽ� ó������ �б����� �� ó������ �̵�

	count = 0;	// �迭�� �ε��� 

	while (!feof(fp)) {
		fscanf(fp, "%s %d %s", buffer, &list[count].id, list[count].phone);

		int len = strlen(buffer); //���ڿ� ���� ����
		list[count].name = (char*)malloc(sizeof(char)*(len + 1)); //���ڿ� ���� ��ŭ �����Ҵ�
		strcpy(list[count].name, buffer);	//�迭�� ���ڿ� ����
		count++;
	}

	printf("<������>\n");
	print(list, count);
	printf("\n");

	printf("<�� ����- �й���>\n");
	shell_sort(list, count);
	print(list, count);
	printf("\n");

	fclose(fp); //���� �ݱ�
	free(list);	//���� �Ҵ� ����

	return 0;
}

// �迭 ���� ���
void print(element list[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%s %d %s\n", list[i].name, list[i].id, list[i].phone);
	}
}

//���� ����
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

//�� ����
void shell_sort(element list[], int n) {

	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) { //gap�� ���ݾ� �ٿ������鼭 0�̻��� ������ �ݺ�
		if (gap % 2 == 0) gap+=1;	// gap�� ¦���� ��� Ȧ���� ����

		for (i = 0; i < gap; i = i++) {	//gap��ŭ �ݺ�
			insertion_sort(list,i,n-1, gap);	//���� ���� ȣ��
		}
	}
}

