/*
프로그램 설명: 파일에 저장된 3자릿수 데이터를 불러와 
기수 정렬을 사용하여 오름차순으로 정렬하는 과정 작성

작성일: 2022.11.25.
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_QUEUE_SIZE 100
#define BUCKETS 10 // 큐의 개수
#define DIGIT 3 //자릿수

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

// 함수 원형 작성
void radix_sort(int list[], int n);

int main() {

	FILE *fp;	//파일을 읽어오기 위한 파일 포인터 선언
	int list[MAX_QUEUE_SIZE] = { 0 }; //
	int n = 0;	//list 배열의 인덱스

	fp = fopen("Radix_data.txt", "r");

	if (!fp) { //파일을 읽어오는데 실패한 경우
		printf("CAN NOT OPEN FILE");	//에러메세지 출력
		return;	//종료
	}

	while (!feof(fp)) { //파일의 처음부터 끝까지 
		fscanf(fp, "%d", &list[n++]);	//데이터를 읽어와 list 배열에 저장
	}
	printf("이름: 박윤아\n학번: 20204624\n제출일: 2022.11.25.\n\n");

	printf("정렬 전 데이터\n");
	print_list(&list, n);

	radix_sort(&list, n);	//기수 정렬

	printf("\n정렬 후 데이터\n");
	print_list(&list, n);

	fclose(fp);	//파일 닫기

	return 0;
}

void radix_sort(int list[], int n) {
	QueueType queues[BUCKETS];	// 0~9까지 숫자에 따라 각각 담을 수 있는 큐배열 선언 

	int i, b, d;
	int factor = 1; //자릿수 계산 시에 사용

	;
	for (b = 0; b < BUCKETS; b++) {	// 0~9까지 
		init(&queues[b]);	// 큐 배열 초기화
	}
	printf("\n\n<정렬 과정>");

	for (d = 0; d < DIGIT; d++) { // 3자릿수이므로 3번 반복
		printf("\nDigit %d\n", d + 1);
	
		for (i = 0; i < n; i++) { //배열 내의 데이터 개수만큼 반복
			enqueue(&queues[(list[i] / factor) % 10], list[i]); //첫째 or 둘째 or 셋째 자릿수에 있는 수를 판별한 후 각각의 큐에 삽입
		}

		for (b = i = 0; b < BUCKETS; b++) {	//10번 반복
			printf("버켓 [%d] : ", b);

			if (is_empty(&queues[b])) printf("EMPTY"); //큐가 비어있다면 EMPTY 출력

			while (!is_empty(&queues[b])){	//큐가 빌 때까지 반복
				list[i] = dequeue(&queues[b]);	// list배열에 큐에 있는 요소 순서대로 삽입
				printf("%d ", list[i++]);	//삽입한 데이터 출력
			}
			printf("\n");
			
		}
		print_list(list, n);
		printf("\n");
		factor *= 10; //그 다음 자릿수로 이동
	}
}