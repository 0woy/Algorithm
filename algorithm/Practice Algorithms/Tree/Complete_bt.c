/*
학번: 20204624
이름: 박윤아

프로그램 설명: 완전이진트리 여부 판별하기
*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>	// 제곱근을 구하기 위해 추가

// a와 b중 더 큰것을 반환 하는 MAX 정읜
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;


TreeNode * create_node(int data) {
	TreeNode *n = (TreeNode*)malloc(sizeof(TreeNode));
	
	// 동적 할당에 실패하면 return;
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
			printf("이미 중복된 값이 있습니다.\n");
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
	int height = 0; // 트리 높이

	//  왼쪽 오른쪽 서브트리의 높이를 비교하여 반복.
	if (root != NULL) {
		height = 1 +
			MAX(get_height(root->left), get_height(root->right));
	}
	return height;
}


int get_leaf_count(TreeNode *root) {

	int count = 0;
	if (root != NULL) {
		// 자식이 하나라도 있으면 get_leaf_count 호출
		if (root->left != NULL || root->right != NULL) {
			count = get_leaf_count(root->left) +
				get_leaf_count(root->right);
		}

		// 단말 노드면 1 return;
		else
			return 1;
	}
	return count;
}


int get_nonleaf_count(TreeNode *root) {

	int count = 0;
	if (root != NULL) {
		// 자식이 하나라도 있으면 get_leaf_count 호출
		if (root->left != NULL || root->right != NULL) {
			count = 1 + get_nonleaf_count(root->left) +
				get_nonleaf_count(root->right);
		}

		// 단말 노드면 1 return;
		else
			return count;
	}
	return count;
}

int main() {
	FILE *fp;
	int data = 0;
	TreeNode *root = NULL;
	fp = fopen("CBT_data1.txt", "r");

	if (fp == NULL) {
		printf("파일을 열 수 없습니다.");
		return;
	}

	while (!feof(fp)) {
		fscanf(fp, "%d", &data);
		printf("Inserted %d\n", data);
		Insert_node(&root, data);
	}
	
	// 트리 높이
	int height = get_height(root);
//	printf("?믪씠: %d", height);
	int cbt_node = pow(2, (height - 1));

	// 단말 노드 개수
	int leaf = get_leaf_count(root);
	int non = get_nonleaf_count(root);

	if (cbt_node != leaf)
		printf("완전 이진트리가 아닙니다.");
	else
		printf("완전 이진트리 입니다.\n");
	printf("\n단말노드의 수: %d\n", leaf);
	printf("비단말노드의 수: %d", non);
	fclose(fp);

	if (root != NULL) 
		free(root);
	
	
}