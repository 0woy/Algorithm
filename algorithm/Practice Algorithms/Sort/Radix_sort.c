/*
���α׷� ����: ���Ͽ� ����� 3�ڸ��� �����͸� �ҷ��� 
��� ������ ����Ͽ� ������������ �����ϴ� ���� �ۼ�

�ۼ���: 2022.11.25.
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_QUEUE_SIZE 100
#define BUCKETS 10 // ť�� ����
#define DIGIT 3 //�ڸ���

typedef int element;

typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front;
	int rear;
}QueueType;

void init(QueueType *q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType *q) {
	return(q->front == q->rear);
}

int is_full(QueueType *q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, element item) {

	if (is_full(q)) {
		printf("QUEUE IS FULL\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType *q) {
	if (is_empty(q)) {

	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

void print_list(int *list, int n) {
	for (int i = 0; i < n; i++) {
		printf("[%d] ", list[i]);
	}
}

// �Լ� ���� �ۼ�
void radix_sort(int list[], int n);

int main() {

	FILE *fp;	//������ �о���� ���� ���� ������ ����
	int list[MAX_QUEUE_SIZE] = { 0 }; //
	int n = 0;	//list �迭�� �ε���

	fp = fopen("Radix_data.txt", "r");

	if (!fp) { //������ �о���µ� ������ ���
		printf("CAN NOT OPEN FILE");	//�����޼��� ���
		return;	//����
	}

	while (!feof(fp)) { //������ ó������ ������ 
		fscanf(fp, "%d", &list[n++]);	//�����͸� �о�� list �迭�� ����
	}
	printf("�̸�: ������\n�й�: 20204624\n������: 2022.11.25.\n\n");

	printf("���� �� ������\n");
	print_list(&list, n);

	radix_sort(&list, n);	//��� ����

	printf("\n���� �� ������\n");
	print_list(&list, n);

	fclose(fp);	//���� �ݱ�

	return 0;
}

void radix_sort(int list[], int n) {
	QueueType queues[BUCKETS];	// 0~9���� ���ڿ� ���� ���� ���� �� �ִ� ť�迭 ���� 

	int i, b, d;
	int factor = 1; //�ڸ��� ��� �ÿ� ���

	;
	for (b = 0; b < BUCKETS; b++) {	// 0~9���� 
		init(&queues[b]);	// ť �迭 �ʱ�ȭ
	}
	printf("\n\n<���� ����>");

	for (d = 0; d < DIGIT; d++) { // 3�ڸ����̹Ƿ� 3�� �ݺ�
		printf("\nDigit %d\n", d + 1);
	
		for (i = 0; i < n; i++) { //�迭 ���� ������ ������ŭ �ݺ�
			enqueue(&queues[(list[i] / factor) % 10], list[i]); //ù° or ��° or ��° �ڸ����� �ִ� ���� �Ǻ��� �� ������ ť�� ����
		}

		for (b = i = 0; b < BUCKETS; b++) {	//10�� �ݺ�
			printf("���� [%d] : ", b);

			if (is_empty(&queues[b])) printf("EMPTY"); //ť�� ����ִٸ� EMPTY ���

			while (!is_empty(&queues[b])){	//ť�� �� ������ �ݺ�
				list[i] = dequeue(&queues[b]);	// list�迭�� ť�� �ִ� ��� ������� ����
				printf("%d ", list[i++]);	//������ ������ ���
			}
			printf("\n");
			
		}
		print_list(list, n);
		printf("\n");
		factor *= 10; //�� ���� �ڸ����� �̵�
	}
}