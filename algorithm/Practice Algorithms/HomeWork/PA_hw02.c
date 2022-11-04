/*
이름: 박윤아
작성일: 2022.09.30.

설명: 파일에 작성된 랜덤한 수를 읽어와서 중위 순회로 트리에 저장한 후,
저장된 노드값의 최소/ 최댓값을 출력

*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef int element;

typedef struct TreeNode {
	element data;
	struct TreeNode* left, *right;
}TreeNode;

void insert_node(TreeNode ** root, element key);
void inorder(TreeNode *root);

int main() {
	FILE *fp;
	element e;
	TreeNode *root = NULL;
	TreeNode *tmp;
	printf("학번: 20204624\n이름: 박윤아\n\n");
	fp = fopen("Random.txt", "r");
	if (fp == NULL) {
		printf("Can Not Open FILE");
		return;
	}

	// 데이터파일에서 정수를 읽어서 트리에 저장
	while (!feof(fp)) {
		fscanf(fp, "%d", &e);

		insert_node(&root, e);
		printf("Inserted %d\n", e);
	}


	printf("\n중위 순회로 데이터 출력\n");
	inorder(root);

	int max = get_max_node(root);
	int min = get_min_node(root);

	printf("\n\n");

	printf("트리 노드 내의 최대값: %d\n", max);
	printf("트리 노드 내의 최소값: %d\n", min);

	free(root);
}

int flag = 0;

// 중위순회로 데이터 출력
void inorder(TreeNode *root) {
	TreeNode * tmp = root;

	// 한 줄에 노드 10개씩
	if (flag == 10) {
		printf("\n");
		flag = 0;
	}
	if(tmp) {
		inorder(tmp->left);
		printf("[%d] ", tmp->data);
		flag += 1;
		inorder(tmp->right);
	}
}

void insert_node(TreeNode ** root, element key) {
	TreeNode *p, *t;
	TreeNode *n;  

	t = *root;
	p = NULL;

	//search
	while (t != NULL) {
		if (key == t->data) //existing data
			return;
		p = t; // update parents node to current node
		if (key < p->data)
			t = p->left;
		else
			t = p->right;
	}

	//insert
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL)
		return;

	n->data = key;
	n->left = n->right = NULL;

	if (p != NULL) {
		if (key < p->data)
			p->left = n;
		else
			p->right = n;
	}
	else
		*root = n;
}

int get_max_node(TreeNode* root) {
	TreeNode *tmp = root;
	while (tmp->right != NULL) {
		tmp = tmp->right;
	}
	return tmp->data;
}

int get_min_node(TreeNode *root) {

	TreeNode *tmp = root;
	while (tmp->left!=NULL) {
		tmp = tmp->left;
	}
	return tmp->data;
}