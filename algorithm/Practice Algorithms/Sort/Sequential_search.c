/*
���α׷� ����: ����Ž���� ������ ����Ž���� �ۼ��Ͽ�
�� 10000000���� �������� Ž�� �ð��� ��.

�̸�: 0woy
�ۼ���: 2022.11.25.
*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>	//���� �ð� �񱳸� ���� �������

typedef int element;

int flag_s, flag_i; //�迭 �ȿ� ã���� �ϴ� ��Ұ� �ִ��� Ȯ���ϴ� flag ����(-1: ��Ұ� ����)
clock_t  start_s, end_s, start_i, end_i;

//�Լ� ���� ����
int sequential(element arr[], int key, int count);			//����Ž��
int improved_sequential(element arr[], int key, int count);	//������ ����Ž��

int main() {

	printf("�̸�: ������\n�й�: 20204624\n������: 2022.11.26.\n\n");

	FILE *fp; // ������ ������ �о���� ���� ���� ������ ����
	element tmp; // �ӽ÷� �����͸� �б� ���� ���� ����
	element *data; //�����͸� �����ϱ� ���� �迭 ����
	int count = 0; //���Ͽ� �ִ� �������� ������ ���� ����
	int key; //ã���� �ϴ� ���


	fp = fopen("Sequential_data.txt", "r"); // ������ ���� �о����

	if (!fp) { //���� ������ ����ִٸ�(���ٸ�)
		printf("CAN NOT OPEN FILE"); // �����޼��� ���
		return; // ���α׷� ����
	}

	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp); //�����͸� �о�� tmp�� ����
		count ++; // ������ ���� ����
	}

	rewind(fp); //�迭�� �����͸� �����ϱ� ���� ���� �����͸� ������ �� ���� �ٽ� �ø�
	data = (element*)malloc(sizeof(element)*(count+1)); //�������� ������ŭ �޸� �����Ҵ�
	
	int i = 0; //�迭�� �ε���
	while (!feof(fp)) {
		fscanf(fp, "%d", &data[i++]);  //�����͸� �о�� �迭�� ����
	}

	printf("�������� ����: %d\n", count);
	printf("ã���� �ϴ� ��Ҹ� �Է��ϼ��� >>");
	scanf("%d", &key);

		
	sequential(data, key,count);	// ����Ž�� ȣ��
	end_s = clock();		// �ð� ���� ����

		
	improved_sequential(data, key,count);		//������ ����Ž�� ȣ��
	end_i = clock();		//�ð� ���� ����


	float result1 = (float)(end_s - start_s) / CLOCKS_PER_SEC;
	float result2 = (float)(end_i- start_i) / CLOCKS_PER_SEC;

	if (flag_s != -1 && flag_i != -1) {
		printf("\nŽ�� ����!!\n");
		printf("���� Ž��: %f\n", result1);
		printf("������ ���� Ž��: %f\n", result2);
	}
	else
		printf("Ž�� ����!");

	free(data); //���� �Ҵ� ����
	fclose(fp);	//���� �ݱ�


	return 0;
}

int sequential(element arr[], int key, int count) {

	start_s = clock();	// �ð� ���� ����
	for (int i = 0; i < count; i++) { // �迭�� ������ ���鼭
		if (arr[i] == key)			// ��Ҹ� ã�Ҵٸ�
			return i;				// return index	
	}
	return -1; //ã�� ���ߴٸ� -1 return
}

int improved_sequential(element arr[], int key, int count) {
	
	int i;
	arr[count] = key;	//ã�� ��Ҹ� �迭�� �� ���� �ִ´�.

	start_i = clock(); 	//�ð� ���� ����
	for (i = 0; arr[i] != key; i++)	// index 0 ���� key�� ã�� ������ �ݺ�
		;
	if (i == (count)) return -1;	// for���� ������ ���� index�� count�� ���ٸ� Ž���� ���������Ƿ� -1 return
	else return i;	// �׷��� �ʴٸ� return index
	
}
