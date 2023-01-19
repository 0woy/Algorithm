/*
이름: 박윤아
학번: 20204624

프로그램 설명: 이진트리를 이용해 핸드폰 번호, 사용자 이름을 갖는 구조체를 선언하여
데이터 삽입/삭제/탐색 과 이진트리 출력 프로그램.
*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct {
	char name[100];
	char phone[100];
	struct TreeNode* left, *right;
}TreeNode;

TreeNode* insert_node(TreeNode* root, char name[], char phone[]);
TreeNode* new_node(char name[], char phone[]);
void inorder(TreeNode * root);
TreeNode* search(TreeNode* root, char name[]);
TreeNode *delete_node(TreeNode * root, char name[]);

TreeNode * min_value_node(TreeNode *node);

int main() {
	char command;

	char name[100];
	char phone[100];

	TreeNode * root = NULL;
	TreeNode *tmp;

	printf("Input(i), Output(p), Search(s), Delete(d), EXIT(q) : ");

	do {
		scanf("%c", &command);

		switch (command)
		{
		case 'i':
			printf("Input Name: ");
			scanf("%s", name);
			printf("Input Phone-Number: ");
			scanf("%s", phone);
	
			root = insert_node(root, name, phone);
			break;
		case 'd':
			printf("Enter a name to delete for: ");
			scanf("%s", name);
			root = delete_node( root, name);
			break;
		case 'p':
			inorder(root);
			break;
		case 's':
			printf("Enter a name to search for: ");
			scanf("%s", name);
			tmp = search(root, name);

			if (tmp != NULL)
				printf("%s's Phone-Number is %s\n", name, tmp->phone);
			break;
		}
	} while (command != 'q');

	free(root);
}

TreeNode * new_node(char name[], char phone[]) {
	TreeNode * n = (TreeNode*)malloc(sizeof(TreeNode));
	strcpy(n->name, name);
	strcpy(n->phone, phone);
	n->right = n->left = NULL;

	return n;
}

// Binary Tree don't allow duplicate values
TreeNode* insert_node(TreeNode *root, char name[], char phone[]) {

	TreeNode * tmp = root;

	if (tmp == NULL) {
		return new_node(name, phone);
	}

	//
	// Search Tree
	if (strcmp(name, tmp->name) < 0)
		tmp->left = insert_node(tmp->left, name, phone);

	else if(strcmp(name, tmp->name) > 0)
		tmp->right = insert_node(tmp->right, name, phone);

	else {
		printf("There are duplicate values in the tree");
		return;
	}

	
	return tmp;

}

// Inorder using Recursive
void inorder(TreeNode * root) {
	TreeNode *tmp = root;

	if (tmp != NULL) {
		inorder(tmp->left);
		printf("%s %s\n", tmp->name, tmp->phone);
		inorder(tmp->right);
	}
}

TreeNode* search(TreeNode* root, char name[]) {
	TreeNode * tmp = root;

	if (tmp == NULL) {
		printf("There are not the name : %s\n", name);
		return;
	}
		

	if (strcmp(name, tmp->name) == 0)
		return tmp;

	else if (strcmp( name, tmp->name) < 0)
		 return search(tmp->left, name);
	else
		return search(tmp->right, name);
	
}

TreeNode *delete_node(TreeNode * root, char name[]) {

	TreeNode * tmp = root;

	if (tmp == NULL)
		return tmp;

	if (strcmp(name, tmp->name) < 0)
		tmp->left = delete_node(tmp->left, name);
	else if (strcmp(name, tmp->name) > 0)
		tmp->right = delete_node(tmp->right, name);

	// matched
	else {
		if (tmp->left == NULL) {
			TreeNode * dno = tmp->right;
			free(tmp);
			return dno;
		}
		else if (tmp->right == NULL) {
			TreeNode * dno = tmp->left;
			free(tmp);
			return dno;
		}

		else
		{		// delete_node has two sub trees
			TreeNode * succ = min_value_node(tmp->right);

			// in Inorder - copy succ node
			strcpy(tmp->name, succ->name);
			strcpy(tmp->phone, succ->phone);

			// in Inorder - delete succ node
			tmp->right = delete_node(tmp->right, succ->name);

		}
	}
	return tmp;
}

TreeNode * min_value_node(TreeNode *node) {
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}
