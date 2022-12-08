#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

int *sorted;// �߰� ������ �ʿ�

//�Ű� ������ �޾ƿ� �迭 ������ ������ ��� �Լ�
void print(int arr[], int left, int right) {
	printf("[");
	for (int i = left; i < right; i++) { //���� �ε��� ~ �� �ε������� 
		printf("%d > ", arr[i]);	//������ ���
	}
	printf("]\n");
}

void merge(int list[], int left, int mid, int right);
void merge_sort(int list[], int left, int right);

int main() {

	FILE *fp; //������ ������ �о���� ���� ���� ������ ����

	fp = fopen("Quick_data.txt", "r");

	int tmp;	//�����͸� �ӽ÷� �����ϴ� ����
	int count = 0; //�������� ����
	int *data; //�����͸� ������ �迭

	if (!fp) { //������ �о���µ� ������ ���
		printf("CAN NOT OPEN FILE"); //�����޼��� ���
		return 0; //return
	}

	while (!feof(fp)) {			//������ ������
		fscanf(fp, "%d", &tmp); //�����͸� �а�
		count++;				//������ ���� ����
	}

	data = (int*)malloc(sizeof(int)*count); //������ ������ŭ �����Ҵ�
	sorted = (int*)malloc(sizeof(int)*count);
	rewind(fp); // ������ �ٽ� ó������ �б� ���� rewind

	int i = 0; // data �迭�� �ε���
	while (!feof(fp)) {
		fscanf(fp, "%d", &data[i++]); //������ �� �پ� �����鼭 �迭�� ����
	}

	printf("�̸�: ������\n�й�: 20204624\n������: 2022.11.26.\n\n");

	printf("���� ��\n");
	print(data, 0, count);  //���� �� ������ ���

	merge_sort(data, 0, count - 1); // ������ ����

	printf("���� ��\n");
	print(data, 0, count); //���� �� ������ ���


	free(data); // ���� �Ҵ� ����
	free(sorted);
	fclose(fp); // ���� �ݱ�

	return 0;
}


/* i�� ���ĵ� ���� ����Ʈ�� ���� �ε���
		j�� ���ĵ� ������ ����Ʈ�� ���� �ε���
		k�� ���ĵ� ����Ʈ�� ���� �ε��� */
void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left;  j = mid + 1;  k = left;
	printf("left: %d, mid: %d, right: %d\n", list[left], list[mid],list[right]);

	/* ���� ���ĵ� list�� �պ� */
	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i > mid)	/* ���� �ִ� ���ڵ��� �ϰ� ���� */
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else	/* ���� �ִ� ���ڵ��� �ϰ� ���� */
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	/* �迭 sorted[]�� ����Ʈ�� �迭 list[]�� �纹�� */
	for (l = left; l <= right; l++)
		list[l] = sorted[l];

//	print(list, left, right+1);
	
}


void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2;     /* ����Ʈ�� �յ� ���� */
		merge_sort(list, left, mid);    /* �κ� ����Ʈ ���� */
		merge_sort(list, mid + 1, right); /* �κ� ����Ʈ ���� */
		merge(list, left, mid, right);    /* �պ� */
	//	print(list, left, right);
	}
}