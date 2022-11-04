/*
�̸�: ������
�ۼ���: 2022.09.30.

����: ���Ͽ� �ۼ��� ������ ���� �о�ͼ� ���� ��ȸ�� Ʈ���� ������ ��,
����� ��尪�� �ּ�/ �ִ��� ���

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
	printf("�й�: 20204624\n�̸�: ������\n\n");
	fp = fopen("Random.txt", "r");
	if (fp == NULL) {
		printf("Can Not Open FILE");
		return;
	}

	// ���������Ͽ��� ������ �о Ʈ���� ����
	while (!feof(fp)) {
		fscanf(fp, "%d", &e);

		insert_node(&root, e);
		printf("Inserted %d\n", e);
	}


	printf("\n���� ��ȸ�� ������ ���\n");
	inorder(root);

	int max = get_max_node(root);
	int min = get_min_node(root);

	printf("\n\n");

	printf("Ʈ�� ��� ���� �ִ밪: %d\n", max);
	printf("Ʈ�� ��� ���� �ּҰ�: %d\n", min);

	free(root);
}

int flag = 0;

// ������ȸ�� ������ ���
void inorder(TreeNode *root) {
	TreeNode * tmp = root;

	// �� �ٿ� ��� 10����
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