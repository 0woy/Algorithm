#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>	// 제곱수를 구하기 위해 추가
#include<Windows.h>


// MAX 정의, 연산자 우선순위를 고려하여 괄호 안에 넣어주어야 함.
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;


TreeNode * create_node(int data) {
	TreeNode *n = (TreeNode*)malloc(sizeof(TreeNode));
	
	// 동적할당에 실패할 경우
	if (n == NULL) return;
	
	n->data = data;
	n->left = n->right = NULL;
	return n;
}

void Insert_node(TreeNode **root, int data) {
	TreeNode * tmp;
	TreeNode *p = NULL;
	tmp = *root;

	while (tmp != NULL) {

		if (tmp->data == data) {
			printf("이미 존재하는 값입니다.");
			return;
		}
		p = tmp;
		if (data < tmp->data)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	TreeNode *n = create_node(data);
	if (p != NULL) {
		if (n->data < p->data)
			p->left = n;
		else
			p->right = n;
	}
	else
		*root = n;
}

int get_height(TreeNode *root) {
	int height = 0; //트리 높이 

	// 현재 노드가 NULL이 아니면, 왼쪽 과 오른쪽 서브트리중 더 큰 값 반환
	if (root != NULL) {
		height = 1 +
			MAX(get_height(root->left), get_height(root->right));
	}
	return height;
}


int get_leaf_count(TreeNode *root) {

	int count = 0;
	if (root != NULL) {
		// 자식이 하나라도 있으면 바로 자식 노드로 넘어감.
		if (root->left != NULL || root->right != NULL) {
			count = get_leaf_count(root->left) +
				get_leaf_count(root->right);
		}

		// 자식이 하나도 없으면 1을 반환
		else
			return 1;
	}
	return count;
}



int main() {

	// 한글 깨짐 방지
	SetConsoleOutputCP(65001);
	FILE *fp;
	int data = 0;
	TreeNode *root = NULL;
	fp = fopen("CBT_data2.txt", "r");

	if (fp == NULL) {
		printf("파일이 존재하지 않습니다.");
		return;
	}

	while (!feof(fp)) {
		fscanf(fp, "%d", &data);
		printf("Inserted %d\n", data);
		Insert_node(&root, data);
	}
	
	// 트리의 높이
	int height = get_height(root);
//	printf("높이: %d", height);
	int cbt_node = pow(2, (height - 1));

	// 단말노드
	int leaf = get_leaf_count(root);

	if (cbt_node != leaf)
		printf("완전 이진트리가 이닙니다.");
	else
		printf("완전이진트리입니다.");
}