/*
프로그램 설명 
: 파일에서 사전 데이터를 읽어와 AVL 트리를 만들고 출력

수정 요함
작성일: 2022.12.02.
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

// 함수 원형 작성
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

	FILE *fp;  //파일에서 데이터를 읽어오기위한 파일 포인터 선언
	char flag;	// 파일에서 명령어를 읽어오는 변수
	element tmp;
	AVLNode *AN;
	fp = fopen("AVL_data.txt", "r");

	if (!fp) { //파일을 읽어오는데 실패한 경우
		printf("CAN NOT OPEN FILE"); //에러메세지 출력
		return; //종료
	}

	while (!feof(fp)) { //파일의 끝까지 반복
		fscanf(fp, "%c", &flag);	// i: 삽입 / s: 탐색
		if (flag == 'i') {
			fscanf(fp, "%s %s", tmp.word, tmp.mean);
			printf("삽입: %s %s\n", tmp.word, tmp.mean);
			avl_add(&root, tmp);


		}
		if (flag == 's') {
			fscanf(fp, "%s", tmp.word);
			strcpy(tmp.mean, "");
			AN = avl_search(root, tmp);
			printf("단어 %s의 의미 %s\n", AN->data.word, AN->data.mean);
		}
	}
	printf("\n\nAVL 트리 출력\n");
	preorder(root);
	fclose(fp);
	return 0;
}


AVLNode* rebalance(AVLNode** node) {
	
	int height_diff = get_height_diff(*node);	//왼쪽과 오른쪽의 높이 차

	if (height_diff > 1 ) { //왼쪽 서브트리가 불균형인 경우 : LL, LR

		if (get_height_diff((*node)->left_child) > 0) { // LL인 경우
			*node = rotate_LL(*node);
		}
		else { //LR인 경우
			*node = rotate_LR(*node);
		}
	}
	else if (height_diff < -1) {  //오른쪽 서브트리가 불균형인 경우: RR, RL
		if (get_height_diff((*node)->right_child) < 0) { // RR인 경우 
			*node = rotate_RR(*node);
		}
		else { //RL인 경우
			*node = rotate_RL(*node);
		}
	}

	return *node;
}

AVLNode* avl_add(AVLNode **root, element item) {
	AVLNode ** tmp = root;
	//이진탐색트리의 탐색이 실패한 위치 = 삽입 위치
	if (*tmp == NULL) {
		*tmp = (AVLNode*)malloc(sizeof(AVLNode));
		if (*tmp == NULL) {
			printf("malloc failuer\n");
			exit(1);
		}
		(*tmp)->data = item;
		(*tmp)->left_child = (*tmp)->right_child = NULL;
	}
	
	// 현재 노드보다 새로 들어온 노드가 사전적으로 뒤에 위치한 경우
	else if (strcmp(item.word, (*tmp)->data.word) > 0) {
		 (*tmp)->right_child = avl_add(&((*tmp)->right_child), item);
		 (*tmp) = rebalance(tmp); 
		}
	 // 현재 노드보다 새로 들어온 노드가 사전적으로 앞에 위치한 경우
	 else if (strcmp(item.word, (*root)->data.word) < 0) {
		 (*tmp)->left_child= avl_add(&((*tmp)->left_child), item);
		 (*tmp) = rebalance(tmp);
	 }
	 else {
		 printf("중복된 데이터 입니다.\n");
		 exit(1);
	 }
	return *tmp;
}

AVLNode* avl_search(AVLNode *node, element key) {
	if (node == NULL)
		return NULL;

	//탐색하는 단어가 현재 단어보다 사전적으로 뒤에 있는 경우
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

