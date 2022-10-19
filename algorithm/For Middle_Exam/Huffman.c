/*
학번: 20204624
이름: 박윤아

프로그램 설명: 허프만 트리 작성
*/
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100

typedef struct TreeNode {
	int weight;
	char ch;
	struct TreeNode* left, *right;
}TreeNode;

typedef struct {
	TreeNode* ptr;
	char ch;
	int key;
}element;

typedef struct {
	element heap[MAX_SIZE];
	int heap_size;
}HeapType;

// create
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

//init
void init(HeapType*h) {
	h->heap_size = 0;
}

//insert_min
void insert_min_heap(HeapType*h, element item) {
	int i = ++(h->heap_size);
	
	while ((i != 1) && item.key < h->heap[i / 2].key) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

// destroy_min
element delete_min_heap(HeapType* h) {
	int p = 1, c = 2;
	element item, temp;
	
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];

	while (c <= h->heap_size) {
		if (c<h->heap_size && h->heap[c].key > h->heap[c + 1].key)
			c += 1;
		if (temp.key < h->heap[c].key) break;
		h->heap[p] = h->heap[c];
		p = c;
		c *= 2;
	}
	h->heap[p] = temp;
	return item;
}


// make _bt
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

	node->left = left;
	node->right = right;

	return node;
}

void destroy_tree(TreeNode*root) {
	if (!root) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}


int is_leaf(TreeNode *root) {
	return(!root->left) && (!root->right);
}

void print_array(int codes[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d", codes[i]);
	}
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top) {

	//1을 저장하고 순환호출한다.
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}

	//0을 저장하고 순환호출한다.
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}

	//단말노드이면 코드를 출력한다.
	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

//허프만 코드 생성 함수
void huffman_tree(int freq[], char ch_list[], int n) {

	int i;
	TreeNode* node, *x;
	HeapType* h;
	element e, e1, e2;
	int codes[3];
	int top = 0;

	h = create();
	init(h);

	for (i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptr = node;
		insert_min_heap(h, e);
	}

	for (i = 1; i < n; i++) {
		//최소값을 가지는 두 개의 노드 삭제
		e1 = delete_min_heap(h);
		e2 = delete_min_heap(h);

		//두 개의 노드 합치기
		x = make_tree(e1.ptr, e2.ptr);
		e.key = x->weight = e1.key + e2.key;
		e.ptr = x;
		printf("%d + %d -> %d\n", e1.key, e2.key, e.key);
		insert_min_heap(h, e);
	}

	e = delete_min_heap(h); //최종트리
	print_codes(e.ptr, codes, top);
	destroy_tree(e.ptr);
	free(h);
}

int main() {
	char ch_list[] = { 's','i','n','t','e' };
	int freq[] = { 4,6,8,12,15 };
	huffman_tree(freq, ch_list, 5);

	return 0;
}
