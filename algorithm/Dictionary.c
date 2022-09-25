#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>


typedef struct dic {
	char name [30];
	char mean [30];
}element;

typedef struct TreeNode {
	element data;
	struct TreeNode *left, *right;
}TreeNode;



// ���ڿ��� ���ϴ� �Լ�
int compare(element e1, element e2) {
	// -1, 0 ,1
	return strcpy(e1.name, e2.name);
}

// ��� Ž�� 
TreeNode *search_node(TreeNode *root, element key) {

	TreeNode *tmp = root;
	while (tmp != NULL) {
		switch (compare(key, tmp->data))
		{
		case -1:
			tmp = tmp->left;
			break;
		case 0:
			return tmp;
		case 1:
			tmp = tmp->right;
			break;

		default:
			break;
		}
	}
}

void insert_node(TreeNode **root, element key) {
	TreeNode *p, *t;
	TreeNode *n;
	t = *root;
	p = NULL;

	// ������ ��ġ ã��
	while (t != NULL) {
		switch (compare(key,t->data))
		{
		p = t;
		case 0:	//�̹� ��尡 �ִ� ���
			return;
		case -1:	// key���� ���� ��� ������ ���� ���
			t = t->left;
		case 1:		//key ���� ���� ��� ������ ū ���
			t = t->right;
		default:
			break;
		}
	}

	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;	// ���� �Ҵ��� ������ ���

	n->data = key;
	n->left = n->right = NULL;

	if (p != NULL) {
		if (compare(key, p->data) < 0)	// �θ� ��庸�� ���� ���
			p->left = n;

		else	// �θ� ��庸�� ū ���
			p->right = n;
	}

	// ���� �߰��� ��尡 ù ����� ���
	else
		*root = n;
}

void display(TreeNode *root) {
	TreeNode *tmp = root;

	if (tmp != NULL) {
		display(tmp->left);
		printf("display:\nƮ�����( %s : %s )", tmp->data.name, tmp->data.name);
		display(tmp->right);
		printf("->");
	}
}

void delete_node(TreeNode **root, element key) {

	TreeNode  *t, *succ, *succ_p;
	TreeNode *p = NULL, *child = NULL;
	t = *root;

	//search
	while (t != NULL && compare(key, t->data) != 0) {
		p = t;
		if (compare(key, t->data) < 0)	//key�� t���� ������
			t = t->left;
		else
			t = t->right;
	}
	
	if (t == NULL) {
		printf("�����Ϸ��� �ܾ �����ϴ�.\n");
		return;
	}

	//�ڽ��� ���� ���
	if (t->left == NULL && t->right == NULL) {
		if (p != NULL) {
			if (p->left == t)
				p->left = NULL;
			else
				p->right = NULL;
		}
		else
			*root = NULL;
	}
	// �ڽ��� �ϳ��� ���� ���
	else if (t->left == NULL || t->right == NULL) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t)
				p->left = child;
			else
				p->right = child;
		}
		*root = NULL;
	}

	// �ڽ��� �� �� ���� ���
	else {
		succ_p = t;
		succ = t->right;

		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}
		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;

		t->data = succ->data;
		t = succ;
	}
	free(t);
}

int main() {
	FILE *fp;
	char command;
	
	//�ܾ�, �ǹ̸� �����Ҵ� �ϱ� ���� buffer
	char buffer_name[30], buffer_mean[30];
	element data;
	TreeNode *tmp;
	TreeNode *root = NULL;

	fp = fscanf("Dic_data.txt", "r");
	if (fp == NULL) {
		printf("������ ã�� �� �����ϴ�.");
		return 1;
	}

	while (!feof(fp)) {
		fscanf(fp, "%c", &command);
		switch (command)
		{
		case 'i':
			fscanf(fp, "%s %s", &data.name,&data.mean);
			insert_node(root,data);
			printf("%s : %s ����\n", data.name, data.mean);
			break;
		
		case 's':
			fscanf(fp, "%s", &data.name);
			strcpy(data.mean, "");
			tmp = search_node(root, data);
			if (tmp != NULL)
				printf("�ܾ� %s�� �ǹ� : %s\n", tmp->data.name, tmp->data.mean);
			break;

		case 'd':
			fscanf(fp, "%s", &data.name);
			void delete_node(root, data);
			printf("%s ����\n", data.name);
			break;
		case 'p':
			display(root);
			break;
		case 'q':
			exit(0);
		default:
			break;
		}
	}

}