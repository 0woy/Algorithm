#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];

typedef struct {
	int key;	// ���� �� ����ġ
	int u;	// ���� ����1
	int v;	// ���� ���� 2
}element;

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

// ���Ͽ� ����� ������ ���� �Է� �޾� ����
void insert_all_edge(element arr []) {
	FILE *fp;
	int a, b, w;
	element e;

	fp = fopen("Kruskal.txt", "r");

	if (!fp) {
		printf("CAN NOT OPEN FILE");
		return;
	}
	int i = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &a, &b, &w);
		e.u = a;
		e.v = b;
		e.key = w;

		arr[i++] = e;
	}

	fclose(fp);
}

int partition(element arr[], int left, int right) {
	element pivot = arr[left];
	element tmp;
	int low = left;
	int high = right + 1;

	do {
		do {
			low++;
		} while (low <= right && arr[low].key < pivot.key);
		do {
			high--;
		} while (high >= left && arr[high].key > pivot.key);
		if (low < high) SWAP(arr[low], arr[high], tmp);

	} while (low < high);

	SWAP(arr[left], arr[high], tmp);
	return high;
}

void quick_sort(element arr[], int left, int right) {
	if (left < right) {
		int q = partition(arr, left, right);
		quick_sort(arr, left, q - 1);
		quick_sort(arr, q + 1, right);
	}
}


//Kruskal
void Kruskal(int n, int edge_num) {

	// spanning tree = n of vertex and (n-1) of edges
	element *arr;
	arr = (element*)malloc(sizeof(element)*edge_num);
	element e;	// struct of edge;
	int uset, vset;

	int edge_accepted = 0;	// ����� ���� ����
	
	insert_all_edge(arr);
	quick_sort(arr,0,edge_num-1);

	set_init(n);
	int i = 0;
	while (edge_accepted < n - 1) {
		e = arr[i++];	// �� Ʈ���� �ִ� �ּ� �� e�� ����

		uset = set_find(e.u); // ����1�� ���� ���� uset�� ����
		vset = set_find(e.v);	// ����2�� ���� ������ vset�� ����

		if (uset != vset) {	// ���� ���տ� ������ �ʾҴٸ�, 
			printf("��� (%d %d): %d\n", e.u, e.v, e.key);	// ���
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
	int count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &a, &b, &w);
		count++;
		if (max < b)
			max = b;
	}
	Kruskal(max + 1,count);

	fclose(fp);
	return;

}






