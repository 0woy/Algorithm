#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h> // 출력창에서 한글 폰트 깨져서 바꾸기 위해 추가

#define MAX_WORD_SIZE 100
#define MAX_meaningING_SIZE 100

typedef struct  {
	char name [MAX_WORD_SIZE];
	char meaning [MAX_meaningING_SIZE];
}element;

typedef struct TreeNode {
	element data;
	struct TreeNode *left, *right;
}TreeNode;



// 문자열 비교 함수
int compare(element e1, element e2) {
	// -1, 0 ,1
	return strcmp(e1.name, e2.name);
}

// 노드 탐색
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
	return tmp;
}

void insert_node(TreeNode **root, element key) {
	TreeNode *p, *t;
	TreeNode *n;

	t = *root;
	p = NULL;


	while (t != NULL) {

		// 만일 노드가 이미 존재한다면 return
		if (compare(key, t->data) == 0)
			return;

		// 부모 노드를 알 수 있도록 
		p = t;
		if (compare(key, t->data) < 0)
			t = t->left;
		else
			t = t->right;
	}

	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;	// 메모리 할당에 실패한 경우

	n->data = key;
	n->left = n->right = NULL;

	// 부모 노드가 존재한다면
	if (p != NULL) {
		if (compare(key, p->data) < 0)	
			p->left = n;
		else	
			p->right = n;
	}

	// 부모 노드가 존재하지 않는다면(트리가 비어 있다면)
	else
		*root = n;

}

void display(TreeNode *root) {
	TreeNode *tmp = root;
	
	if (tmp != NULL) {
		display(tmp->left);
		printf("트리노드( %s : %s )", tmp->data.name, tmp->data.meaning);
		display(tmp->right);
		printf("->");
	}
}

void delete_node(TreeNode **root, element key) {

	TreeNode *tmp;	// 현재 노드 tmp
	TreeNode *p;			// tmp의 부모 노드
	 
	TreeNode *child;		//tmp의 자식노드 위치

	TreeNode * succ;	// 후계자(삭제 노드가 자식이 2개인 경우)
	TreeNode *succ_p;// 후계자 노드의 부모

	tmp = *root;
	p = NULL;
	// 탐색
	while (tmp != NULL && compare(tmp->data, key)!=0) {
		p = tmp;
		tmp = compare(key, tmp->data) ? tmp->left : tmp->right;
	}

	// 삭제하려는 노드가 트리 안에 없다면
	if (tmp == NULL) {
		printf("삭제하려는 %s 노드가 없습니다.\n", key.name);
		return;
	}

	//삭제
	// CASE 1. 삭제하려는 노드가 단말 노드인 경우
	if ((tmp->left == NULL) && (tmp->right == NULL)) {
		 
		// 부모 노드가 존재한다면
		if (p != NULL) {
			if (p->left == tmp)
				p->left = NULL;
			else
				p->right = NULL;
		}

		// 부모노드가 존재하지 않는다면
		else
			*root = NULL;
	}

	//CASE 2. 자식 노드가 하나만 있는 경우
	else if ((tmp->left == NULL) || (tmp->right == NULL)) {

		// 현재 노드의 자식 노드를 child에 넣어줌
		child = (tmp->left != NULL) ? tmp->left : tmp->right;

		if (p != NULL) {
			// 삭제하려는 노드가 부모 노드의 왼쪽/ 오른쪽 찾기
			if (p->left == tmp)
				p->left = child;
			else
				p->right = child;
		}
		// 부모노드가 없다면 (현재 노드가 root 노드였다면)
		else
			*root = child;
	}

	/*
	CASE 3. 자식 노드가 두개 존재하는 경우
	삭제하려는 노드 기준으로 
	오른쪽 서브트리에서 찾는 경우,가장 작은 값의 노드 검색
	 왼쪽 서브트리에서 찾는 경우, 가장 큰 값의 노드를 검색
	 */

	else {
		succ_p = tmp;	// 후계자의 부모 위치를 현재 노드로 설정
		succ = tmp->right;

		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}

		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;

		tmp->data = succ->data;
		tmp = succ;

	}

	printf("%s 삭제\n", key.name);
	free(tmp);
	
}

int main() {

	// 한글 폰트 제대로 나오게 설정
	SetConsoleOutputCP(65001);

	FILE *fp;
	char command;
	element data;
	TreeNode *tmp;
	TreeNode *root = NULL;

	fp = fopen("Dic_data.txt", "r");
	if (fp == NULL) {
		printf("파일을 읽을 수 없습니다.");
		return;
	}

	while (!feof(fp)) {
		fscanf(fp, "%c", &command);
		switch (command)
		{
		case 'i':
			printf("-------------------------------------\n");
			fscanf(fp, "%s %s", &data.name,&data.meaning);
			insert_node(&root,data);
			printf("%s : %s 삽입\n", data.name, data.meaning);
			printf("-------------------------------------\n");
			break;
		
		case 's':
			printf("-------------------------------------\n");
			fscanf(fp, "%s", &data.name);
			strcpy(data.meaning, "");
			tmp = search_node(root, data);
			if (tmp != NULL)
				printf("단어 %s의 의미 : %s\n", tmp->data.name, tmp->data.meaning);
			printf("-------------------------------------\n");
			break;

		case 'd':
			printf("-------------------------------------\n");
			fscanf(fp, "%s", &data.name);
			delete_node(&root, data);
			printf("-------------------------------------\n");
			break;
		case 'p':
			printf("-------------------------------------\n");
			printf("display : \n");
			display(root);
			printf("\n-------------------------------------\n");
			break;
		case 'q':
			exit(0);
		default:
			break;
		}
	}

}