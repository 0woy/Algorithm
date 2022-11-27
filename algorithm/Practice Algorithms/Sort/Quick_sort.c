#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

// �Լ� ���� ����
void print(int arr[], int left, int right);
void quick_sort(int arr[], int left, int right);
int partition(int arr[], int left, int right);


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
	rewind(fp); // ������ �ٽ� ó������ �б� ���� rewind

	int i = 0; // data �迭�� �ε���
	while (!feof(fp)) {
		fscanf(fp, "%d", &data[i++]); //������ �� �پ� �����鼭 �迭�� ����
	}

	printf("�̸�: ������\n�й�: 20204624\n������: 2022.11.26.\n\n");

	printf("���� ��\n");
	print(data, 0, count);  //���� �� ������ ���

	quick_sort(data, 0, count - 1); // ������ ����

	printf("���� ��\n");
	print(data, 0, count); //���� �� ������ ���


	free(data); // ���� �Ҵ� ����
	fclose(fp); // ���� �ݱ�

	return 0;
}

//�Ű� ������ �޾ƿ� �迭 ������ ������ ��� �Լ�
void print(int arr[], int left, int right) {
	printf("[");
	for (int i = left; i < right; i++) { //���� �ε��� ~ �� �ε������� 
		printf("%d > ", arr[i]);	//������ ���
	}
	printf("]\n");
}


//�� ����
void quick_sort(int arr[], int left, int right) {

	if (left < right) {	//���� �����Ͱ� 2�� �̻��̶��,
		int	p = partition(arr, left, right);	//partition �Լ� ȣ��, p �� pivot�� �ε��� ����
		quick_sort(arr, left, p- 1);	//pivot ���� ���� �迭 ������
		quick_sort(arr, p+ 1, right);	//pivot ���� ������ �迭 ������
	}
}


// ���������� ������ �ϴ� �Լ�
int partition(int arr[], int left, int right) {

	int pivot = arr[left]; // �迭�� ���� ���� ��Ҹ� pivot���� ����
	printf("\n-Pivot : %d -\n", pivot);


	int low, high, tmp;
	low = left;			// low�� left ����
	high = right + 1;	// high�� right+1 ����

	do { // low�� high�� ������ ������ �ݺ�

		//�迭���� low�� ��ġ�� �����Ͱ� pivot���� Ŭ ������ �ݺ�
		do {	
			low++; 
		} while (arr[low] < pivot && low <= right);


		//�迭���� high�� ��ġ�� �����Ͱ� pivot���� ���� ������ �ݺ�
		do {	
			high--;
		} while (arr[high] > pivot && high > left);

		printf("Low: %d High: %d\t", arr[low], arr[high]);
		print(arr, left, right + 1);	// ���� �迭 ���� ���

		//�������� �ʾҴٸ�
		if (low < high) { 
			printf("%d�� %d ����\n", arr[low], arr[high]);
			SWAP(arr[low], arr[high], tmp);	//low�� high�� ��ġ�� ������ SWAP
			print(arr, left, right + 1);	// SWAP �� �迭 ���� ���
			printf("\n");
		}
	} while (low < high);

	//low�� high�� ������ �� 
	SWAP(arr[left], arr[high], tmp);  //pivot�� ������ high�� �ִ� ���Ҹ� ��ȯ
	printf("\n");
	return high;	//pivot�� �ε��� ��ȯ

}
