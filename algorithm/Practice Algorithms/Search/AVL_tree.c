/*
���α׷� ���� 
: ���Ͽ��� ���� �����͸� �о�� AVL Ʈ���� ����� ���

���� ����
�ۼ���: 2022.12.02.
*/
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char word[50];
	char mean[50];
}element;

typedef struct {
	element data;
	struct AVLNode *left_child, *right_child;
}AVLNode;

AVLNode *root =NULL;

// �Լ� ���� �ۼ�
AVLNode* avl_add(AVLNode **root, element item);
AVLNode* rebalance(AVLNode** node);
AVLNode* avl_search(AVLNode *node, element key);
AVLNode* rotate_LL(AVLNode *parent);
AVLNode* rotate_LR(AVLNode *parent);
AVLNode* rotate_RR(AVLNode *parent);
AVLNode* rotate_RL(AVLNode *parent);

int maxs(int a, int b) {
	
	int result = 0;
	if (a > b)
		result = a;
	else if (a <= b)
		result = b;

	return result;
}

int get_height(AVLNode *node) {

	int height = 0;
	if (node != NULL) {
		height = 1 + maxs(get_height(node->left_child), get_height(node->right_child));
	}
	return height;
}

int get_height_diff(AVLNode *node) {
	if (node == NULL)
		return 0;

	return get_height(node->left_child) - get_height(node->right_child);
}

int i = 0;
void preorder(AVLNode *root)
{
	if (root != NULL)
	{
		
		if (i ==1 || i==3 || i ==7) {
			printf("\n");
		}
		printf("[%2s:%2s]", root->data.word, root->data.mean);
		i++;
		preorder(root->left_child);
		preorder(root->right_child);
	}
}

int main() {

	FILE *fp;  //���Ͽ��� �����͸� �о�������� ���� ������ ����
	char flag;	// ���Ͽ��� ��ɾ �о���� ����
	element tmp;
	AVLNode *AN;
	fp = fopen("AVL_data.txt", "r");

	if (!fp) { //������ �о���µ� ������ ���
		printf("CAN NOT OPEN FILE"); //�����޼��� ���
		return; //����
	}

	while (!feof(fp)) { //������ ������ �ݺ�
		fscanf(fp, "%c", &flag);	// i: ���� / s: Ž��
		if (flag == 'i') {
			fscanf(fp, "%s %s", tmp.word, tmp.mean);
			printf("����: %s %s\n", tmp.word, tmp.mean);
			avl_add(&root, tmp);


		}
		if (flag == 's') {
			fscanf(fp, "%s", tmp.word);
			strcpy(tmp.mean, "");
			AN = avl_search(root, tmp);
			printf("�ܾ� %s�� �ǹ� %s\n", AN->data.word, AN->data.mean);
		}
	}
	printf("\n\nAVL Ʈ�� ���\n");
	preorder(root);
	fclose(fp);
	return 0;
}


AVLNode* rebalance(AVLNode** node) {
	
	int height_diff = get_height_diff(*node);	//���ʰ� �������� ���� ��

	if (height_diff > 1 ) { //���� ����Ʈ���� �ұ����� ��� : LL, LR

		if (get_height_diff((*node)->left_child) > 0) { // LL�� ���
			*node = rotate_LL(*node);
		}
		else { //LR�� ���
			*node = rotate_LR(*node);
		}
	}
	else if (height_diff < -1) {  //������ ����Ʈ���� �ұ����� ���: RR, RL
		if (get_height_diff((*node)->right_child) < 0) { // RR�� ��� 
			*node = rotate_RR(*node);
		}
		else { //RL�� ���
			*node = rotate_RL(*node);
		}
	}

	return *node;
}

AVLNode* avl_add(AVLNode **root, element item) {
	AVLNode ** tmp = root;
	//����Ž��Ʈ���� Ž���� ������ ��ġ = ���� ��ġ
	if (*tmp == NULL) {
		*tmp = (AVLNode*)malloc(sizeof(AVLNode));
		if (*tmp == NULL) {
			printf("malloc failuer\n");
			exit(1);
		}
		(*tmp)->data = item;
		(*tmp)->left_child = (*tmp)->right_child = NULL;
	}
	
	// ���� ��庸�� ���� ���� ��尡 ���������� �ڿ� ��ġ�� ���
	else if (strcmp(item.word, (*tmp)->data.word) > 0) {
		 (*tmp)->right_child = avl_add(&((*tmp)->right_child), item);
		 (*tmp) = rebalance(tmp); 
		}
	 // ���� ��庸�� ���� ���� ��尡 ���������� �տ� ��ġ�� ���
	 else if (strcmp(item.word, (*root)->data.word) < 0) {
		 (*tmp)->left_child= avl_add(&((*tmp)->left_child), item);
		 (*tmp) = rebalance(tmp);
	 }
	 else {
		 printf("�ߺ��� ������ �Դϴ�.\n");
		 exit(1);
	 }
	return *tmp;
}

AVLNode* avl_search(AVLNode *node, element key) {
	if (node == NULL)
		return NULL;

	//Ž���ϴ� �ܾ ���� �ܾ�� ���������� �ڿ� �ִ� ���
	if (strcmp(key.word, node->data.word) == 0)
		return node;

	else {
		if (strcmp(key.word, node->data.word) > 0)
			return avl_search(node->right_child, key);
		else
			return avl_search(node->left_child, key);
	}
}

AVLNode* rotate_LL(AVLNode *parent) {
	AVLNode *child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;

	return child;
	
}
AVLNode* rotate_LR(AVLNode *parent) {
	AVLNode *child = parent->left_child;
	parent->left_child = rotate_RR(child);

	return rotate_LL(parent);
}
AVLNode* rotate_RR(AVLNode *parent) {
	AVLNode *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;

	return child;
}
AVLNode* rotate_RL(AVLNode *parent) {
	AVLNode *child = parent->right_child;
	parent->right_child = rotate_LL(child);

	return rotate_RR(parent);
}

