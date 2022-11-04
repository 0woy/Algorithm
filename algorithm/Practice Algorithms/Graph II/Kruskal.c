#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];

typedef struct {
	int key;	// 정점 간 가중치
	int u;	// 연결 정점1
	int v;	// 연결 정점 2
}element;

typedef struct {
	element heap[MAX_VERTICES];
	int heap_size;
}HeapType;

void init(HeapType* h) {
	h->heap_size = 0;
}

int is_empty(HeapType*h) {
	if (h->heap_size == 0)
		return 1;
	else
		return 0;
}


void insert_min(HeapType*h, element item) {
	int i = ++(h->heap_size);

	while (i != 1 && item.key < h->heap[i / 2].key) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[h->heap_size--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && h->heap[child].key > h->heap[child + 1].key){
			child++;
		}
		if (temp.key <= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// 정점 집합 초기화
void set_init(int n) {
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

//cur가 속하는 집합 반환
int set_find(int curr) {
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1)
		curr = parent[curr];
	return curr;
}

// 두 개의 원소가 속한 집합을 합친다.
void set_union(int a, int b) {
	int root1 = set_find(a);
	int root2 = set_find(b);

	if (root1 != root2)
		parent[root1] = root2;
}

/*
struct Edge {
	int start, end, weight;
};


//qsort에 사용되는 함수
int compare(const void *a, const void *b) {
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}
*/


// 파일에 저장된 정점간 간선 입력 받아 설정
void insert_all_edge(HeapType *h) {
	FILE *fp;
	int a, b, w;
	element e;

	fp = fopen("Kruskal.txt", "r");

	if (!fp) {
		printf("CAN NOT OPEN FILE");
		return;
	}
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &a, &b, &w);
		e.u = a;
		e.v = b;
		e.key = w;

		insert_min(h, e);
	}

	fclose(fp);

}


//Kruskal
void Kruskal(int n) {
	
	// spanning tree = n of vertex and (n-1) of edges
	HeapType h;
	element e;	// struct of edge;
	int uset, vset;

	int edge_accepted = 0;	// 연결된 간선 갯수
	init(&h);
	insert_all_edge(&h);

	set_init(n);
	while (edge_accepted < n - 1) {
		e = delete_min(&h);	// 힙 트리에 있는 최소 값 e에 저장

		uset = set_find(e.u); // 정점1이 속한 집합 uset에 저장
		vset = set_find(e.v);	// 정점2가 속한 집합을 vset에 저장

		if (uset != vset) {	// 같은 집합에 속하지 않았다면, 
			printf("(%d %d) %d\n", e.u, e.v, e.key);	// 출력
			edge_accepted++;	// 연결 간선 갯수 1증가
			set_union(uset, vset);	// uset, vset을 합집합으로 만들기.
		}
	}

}

int main() {

	FILE *fp;
	int a, b, w;
	int max = 0; //파일에 포함된 정점 개수

	int num = 0;

	fp = fopen("Kruskal.txt", "r");

	if (!fp) {
		printf("CAN NOT OPEN FILE");
		return 0;
	}
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &a, &b, &w);
		if (max < b)
			max = b;
	}
	Kruskal(max+1);

	fclose(fp);
	return;

}






