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



// 문자열을 비교하는 함수
int compare(element e1, element e2) {
	// -1, 0 ,1
	return strcpy(e1.name, e2.name);
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
}

void insert_node(TreeNode **root, element key) {
	TreeNode *p, *t;
	TreeNode *n;
	t = *root;
	p = NULL;

	// 삽입할 위치 찾기
	while (t != NULL) {
		switch (compare(key,t->data))
		{
		p = t;
		case 0:	//이미 노드가 있는 경우
			return;
		case -1:	// key값이 현재 노드 값보다 작은 경우
			t = t->left;
		case 1:		//key 값이 현재 노드 값보다 큰 경우
			t = t->right;
		default:
			break;
		}
	}

	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;	// 동적 할당을 실패한 경우

	n->data = key;
	n->left = n->right = NULL;

	if (p != NULL) {
		if (compare(key, p->data) < 0)	// 부모 노드보다 작은 경우
			p->left = n;

		else	// 부모 노드보다 큰 경우
			p->right = n;
	}

	// 새로 추가한 노드가 첫 노드인 경우
	else
		*root = n;
}

void display(TreeNode *root) {
	TreeNode *tmp = root;

	if (tmp != NULL) {
		display(tmp->left);
		printf("display:\n트리노드( %s : %s )", tmp->data.name, tmp->data.name);
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
		if (compare(key, t->data) < 0)	//key가 t보다 작으면
			t = t->left;
		else
			t = t->right;
	}
	
	if (t == NULL) {
		printf("삭제하려는 단어가 없습니다.\n");
		return;
	}

	//자식이 없을 경우
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
	// 자식이 하나만 있을 경우
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

	// 자식이 둘 다 있을 경우
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
	
	//단어, 의미를 동적할당 하기 위한 buffer
	char buffer_name[30], buffer_mean[30];
	element data;
	TreeNode *tmp;
	TreeNode *root = NULL;

	fp = fscanf("Dic_data.txt", "r");
	if (fp == NULL) {
		printf("파일을 찾을 수 없습니다.");
		return 1;
	}

	while (!feof(fp)) {
		fscanf(fp, "%c", &command);
		switch (command)
		{
		case 'i':
			fscanf(fp, "%s %s", &data.name,&data.mean);
			insert_node(root,data);
			printf("%s : %s 삽입\n", data.name, data.mean);
			break;
		
		case 's':
			fscanf(fp, "%s", &data.name);
			strcpy(data.mean, "");
			tmp = search_node(root, data);
			if (tmp != NULL)
				printf("단어 %s의 의미 : %s\n", tmp->data.name, tmp->data.mean);
			break;

		case 'd':
			fscanf(fp, "%s", &data.name);
			void delete_node(root, data);
			printf("%s 삭제\n", data.name);
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