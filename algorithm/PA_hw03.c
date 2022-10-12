/*
학번: 20204624
이름: 박윤아

머신 스케줄링 구현하기
LPT(Longest Processing Time first) 방법을 사용.
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>


#define MAX_ELEMENT 200
typedef struct {
	int id;
	int avail;
}element;

typedef struct {
	element heap[MAX_ELEMENT];	// Data for heap
	int heap_size;	// heap index
}HeapType;


// Declare function prototype
HeapType* create();
void init(HeapType *h);
void insert_min_heap(HeapType* h, element item);
element delete_min_heap(HeapType *h);

#define JOBS 7	// number of work 
#define MACHINES 3	//number of machine

int main() {
	printf("이름: 박윤아\n학번: 20204624\n제출일: 2022.10.13.\n\n");
	int jobs[JOBS] = { 8,7,6,5,3,2,1 }; //Assume jobs are aligned
	element m = { 0,0 };

	HeapType* h;
	h = create();
	init(h);


	// avail value is Time that the machine becomes available
	for (int i = 0; i < MACHINES; i++) {
		m.id = i + 1;
		m.avail = 0;
		insert_min_heap(h, m);
	}

	
	for (int i = 0; i < JOBS; i++) {
		m = delete_min_heap(h);
		printf("JOB %d 을 시간= %d 부터 시간= %d까지 기계 %d 번에 할당한다.\n", i, m.avail, m.avail + jobs[i] - 1, m.id);
		m.avail += jobs[i];
		insert_min_heap(h, m);
	}

	return 0;

}

//Create New node
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// init heap
void init(HeapType *h) {
	
	h->heap_size = 0;	// init heap's index to 0
}

// Insert item into heap with current number of elements as heap_size 
void insert_min_heap(HeapType* h, element item) {
	
	int i = ++(h->heap_size); // increase 1 size of heap

	// compare parents node with item
	while ((i != 1) && (item.avail < h->heap[i / 2].avail)) {	// current index is not root && item's avail is smaller than parent's avail
		h->heap[i] = h->heap[i / 2]; // Move the parent node to where the current index points
		i /= 2; // Move index to parents index
	}

	h->heap[i] = item;	// insert item into heap
}

// delete func
element delete_min_heap(HeapType *h) {
	
	int parent, child;	// variables for moving
	element item, temp;	//	root & last node

	parent = 1;	// init parent points root
	child = 2;	// init child points left child

	item = h->heap[1]; // save root node
	temp = h->heap[(h->heap_size)--];	// temp points last node, decrease heap_size

	
	while (child <= h->heap_size) {	 // if child <= size, run

		// child < size and left child's value is bigger than right
		if ((child < h->heap_size) && (h->heap[child].avail > h->heap[child + 1].avail))
			child += 1;	//Let child points right child

		if (temp.avail < h->heap[child].avail) break;	//if last node is smaller than child, exit loop

		h->heap[parent] = h->heap[child]; //Set parent node to child node value
		parent = child;	// parent points child
		child *= 2; //child points its child
	}

	h->heap[parent] = temp;	// insert last node to its position
	return item; // return root node

}