#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>


/* Heap's Characteristics
 Complete Binary Tree
 allow Duplicate values
 Max or Min Heap
 upheap, down heap
*/
typedef struct {
	int key;
	char animal[100];
}element;


/* left node = parents' index *2;
right node = parent's index *2 + 1
*/

typedef struct {
	element heap[100];
	int heap_size;
}HeapType;

void insert_max_heap(HeapType *heap, element key);
void display(HeapType *heap);

int main() {

	FILE *fp;
	element tmp;
	HeapType heap;

	heap.heap_size = 0;
	fp = fopen("animal.txt", "r");

	if (fp == NULL) {
		printf("CAN NOT OPEN FILE");
		return;
	}

	printf("Up Heap\n");
	while (!feof(fp)) {
		fscanf(fp, "%d %s", &tmp.key, tmp.animal);
		printf("Insert %d %s\n", tmp.key, tmp.animal);

		insert_max_heap(&heap, tmp);
		 display(&heap);
	}
	fclose(fp);
}

void insert_max_heap(HeapType *h, element item) {
	int idx;
	h->heap_size++;

	idx = h->heap_size;

	// idx != root && idx node >  parents
	while ((idx != 1) && (item.key > h->heap[idx / 2].key)) {
		h->heap[idx] = h->heap[idx / 2];
		idx = idx/2;
	}

	h->heap[idx] = item;
}

void display(HeapType *heap) {
	HeapType *h = heap;

	for (int i = 1; i < h->heap_size+1; i++) {
		printf("%d : %s -> ", h->heap[i].key, h->heap[i].animal);
	}
	printf("\n");
}