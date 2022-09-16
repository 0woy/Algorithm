#include<stdio.h>

typedef int element;
typedef struct TreeNode {
	element data;
	struct TreeNode *left, *right;
}TreeNode;

int main() {

	TreeNode *n1, *n2, *n3;
	n1 = (TreeNode*)malloc(sizeof(TreeNode));
	n2 = (TreeNode*)malloc(sizeof(TreeNode));
	n3 = (TreeNode*)malloc(sizeof(TreeNode));

	n1->data = 10;
	n1->left = n2;
	n1->right = n3;
	n2->data = 20;
	n2->left = NULL;
	n2->right = NULL;
	n3->data = 30;
	n3->left = NULL;
	n3->right = NULL;

	if (n1->data != NULL) {
		printf("n1의 노드 : %d\n", n1->data);
		if (n1->left) {
			printf("n1의 왼쪽 자식 노드: %d\n", *n1->left);
		if(n1->right)
			printf("n1의 오른쪽 자식 노드: %d\n", *n1->right);
		}
	}

	free(n1);
	free(n2);
	free(n3);

	return 0;
}