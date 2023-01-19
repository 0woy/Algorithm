/*
프로그램 설명: 100미만의 난수 100개를 갖는 데이터 배열을 최대 힙을 이용해 정렬
*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h> //srand(), rand()
#include<time.h> // time()

#define MAX_ELEMENT 200

typedef struct {
	int heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void init(HeapType*h) {
	h->heap_size = 0;
}

void insert_max(HeapType *h, int item) {
	int i = ++(h->heap_size);

	while (i != 1 && item > h->heap[i / 2]) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

int delete_max_heap(HeapType *h) {
	int p, c;
	int item, tmp;
	item = h->heap[1];
	tmp = h->heap[h->heap_size--];

	p = 1; c = 2;

	while (c <= h->heap_size) {
		if (c < h->heap_size && h->heap[c] < h->heap[c + 1])
			c++;

		if (tmp >= h->heap[c])
			break;
		else {
			h->heap[p] = h->heap[c];
			p = c;
			c *= 2;
		}
	}
	h->heap[p] = tmp;
	return item;
}

void insert_min(HeapType *h, int item) {
	int i = ++(h->heap_size);
	
	while ((i != 1) && (item < h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

int delete_min_heap(HeapType *h) {
	int p, c;
	int item, tmp;
	item = h->heap[1];
	tmp = h->heap[h->heap_size--];

	p = 1; c = 2;

	while (c <= h->heap_size) {
		if (c < h->heap_size && h->heap[c] > h->heap[c + 1]) 
			c++;
	
		if (tmp <= h->heap[c])
			break;
		else {
			h->heap[p] = h->heap[c];
			p = c;
			c *= 2;
		}
	}
	h->heap[p] = tmp;
	return item;
}

void heap_min_sort(int a[], int n) {
	HeapType h;
	init(&h);

	for (int i = 0; i < n; i++)
		insert_min(&h, a[i]);

	for (int i = 0; i < 100; i++)
		a[i] = delete_min_heap(&h);
}

void heap_max_sort(int a[], int n) {
	HeapType h;
	init(&h);

	for (int i = 0; i < n; i++)
		insert_max(&h, a[i]);

	for (int i = 0; i < 100; i++)
		a[i] = delete_max_heap(&h);
}
int main() {
	int data[100];

	srand(time(NULL));

	for (int i = 0; i < 100; i++) {
		data[i] = rand() % 100;

		// 2차원 배열을 선언하여 십의 자릿수에다가 저장하고 비교하는 것도 좋을듯
		for (int j = 0; j < i; j++) {
			if (data[i] == data[j]) {
				i--;
				break;
			}
		}
	}

	printf("난수로 생성한 데이터\n");
	for (int i = 0; i < 100; i++)
	{	
		if ((i % 10 == 0) && i != 0)
			printf("\n");
		// .2: line을 맞추기 위함
		printf("%2d ", data[i]);
	}

	heap_max_sort(data, 100);

	printf("\n히프정렬\n");
	for (int i = 0; i < 100; i++)
	{
		if ((i % 10 == 0) && i != 0)
			printf("\n");
		// .2: line을 맞추기 위함
		printf("%2d ", data[i]);
	}

}

// 내림차순 max_sort() : 과제