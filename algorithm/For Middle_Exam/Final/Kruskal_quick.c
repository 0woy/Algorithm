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
	int key;	// 정점 간 가중치
	int u;	// 연결 정점1
	int v;	// 연결 정점 2
}element;

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

// 파일에 저장된 정점간 간선 입력 받아 설정
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

	int edge_accepted = 0;	// 연결된 간선 갯수
	
	insert_all_edge(arr);
	quick_sort(arr,0,edge_num-1);

	set_init(n);
	int i = 0;
	while (edge_accepted < n - 1) {
		e = arr[i++];	// 힙 트리에 있는 최소 값 e에 저장

		uset = set_find(e.u); // 정점1이 속한 집합 uset에 저장
		vset = set_find(e.v);	// 정점2가 속한 집합을 vset에 저장

		if (uset != vset) {	// 같은 집합에 속하지 않았다면, 
			printf("노드 (%d %d): %d\n", e.u, e.v, e.key);	// 출력
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






