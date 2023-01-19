/*
프로그램 설명: KEY 값과 data(문자)를 갖는 구조체를 최소힙으로 구성 후 출력 프로그램
*/


#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 200

typedef struct {
	int key;
	char data;
}element;


typedef struct {
	element heap[MAX_SIZE];
	int heap_size;
}HeapType;

void insert_min(HeapType* h, int p, char c) {
	int i;
	element tmp;
	i = ++(h->heap_size);

	//new node added is not root &&
	while ((i != 1) && p < h->heap[i / 2].key) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	tmp.key = p;
	tmp.data = c;

	h->heap[i] = tmp;
}

element delete_min(HeapType *h) {

	int parent, child; // index of array

	element item; // delete node
	element last;

	item = h->heap[1];
	last = h->heap[h->heap_size--];

	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		// choose left or right
		if ((child < h->heap_size) &&
			(h->heap[child].key > h->heap[child + 1].key)) {
			child = child + 1;
		}

		if (last.key <= h->heap[child].key)
			break;

		// last.key > child.key
		else {
			h->heap[parent] = h->heap[child];
			parent = child;
			child *= 2;
		}
		
	}
	h->heap[parent] = last;
	printf("%c\n", item.data);
	
	return item;
}


void display(HeapType *h) {
	int i = 0;


	while (i < h->heap_size) {
		printf("%c\n",h->heap[i++].data);
	}
}

int main() {

	HeapType h;
	init(&h);

	insert_min(&h,  1, 'A');
	insert_min(&h, 2, 'B');
	insert_min(&h, 3, 'C');
	insert_min(&h, 4, 'D');
	insert_min(&h, 3, 'C');
	insert_min(&h, 2, 'B');

	element tmp;
	//error
	for (int i = 0; i <= 6; i++)
		delete_min(&h);

}