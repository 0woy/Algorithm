#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];

typedef struct {
	int key;	// ���� �� ����ġ
	int u;	// ���� ����1
	int v;	// ���� ���� 2
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

// ���� ���� �ʱ�ȭ
void set_init(int n) {
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

//cur�� ���ϴ� ���� ��ȯ
int set_find(int curr) {
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1)
		curr = parent[curr];
	return curr;
}

// �� ���� ���Ұ� ���� ������ ��ģ��.
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


//qsort�� ���Ǵ� �Լ�
int compare(const void *a, const void *b) {
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}
*/


// ���Ͽ� ����� ������ ���� �Է� �޾� ����
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

	int edge_accepted = 0;	// ����� ���� ����
	init(&h);
	insert_all_edge(&h);

	set_init(n);
	while (edge_accepted < n - 1) {
		e = delete_min(&h);	// �� Ʈ���� �ִ� �ּ� �� e�� ����

		uset = set_find(e.u); // ����1�� ���� ���� uset�� ����
		vset = set_find(e.v);	// ����2�� ���� ������ vset�� ����

		if (uset != vset) {	// ���� ���տ� ������ �ʾҴٸ�, 
			printf("(%d %d) %d\n", e.u, e.v, e.key);	// ���
			edge_accepted++;	// ���� ���� ���� 1����
			set_union(uset, vset);	// uset, vset�� ���������� �����.
		}
	}

}

int main() {

	FILE *fp;
	int a, b, w;
	int max = 0; //���Ͽ� ���Ե� ���� ����

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






