#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct TreeNode {
	element data;
	struct TreeNode *left, *right;
}TreeNode;

void preorder(TreeNode *root);
void inorder(TreeNode *root);
void postorder(TreeNode *root);
int main() {

	// 노드를 3개 갖는 트리 생성.
	TreeNode *n1, *n2, *n3, *n4, *n5, *n6;
	n1 = (TreeNode*)malloc(sizeof(TreeNode));
	n2 = (TreeNode*)malloc(sizeof(TreeNode));
	n3 = (TreeNode*)malloc(sizeof(TreeNode));
	n4 = (TreeNode*)malloc(sizeof(TreeNode));
	n5 = (TreeNode*)malloc(sizeof(TreeNode));
	n6 = (TreeNode*)malloc(sizeof(TreeNode));

	n6->data = 15;
	n6->left = n2;
	n6->right = n5;
	n2->data = 4;
	n5->data = 20;
	n5->left = n3;
	n5->right = n4;
	n2->left = n1;
	n2->right = NULL;
	n1->data = 1;
	n3->data = 16;
	n4->data = 25;
	n1->left = n1->right = n3->left = n3->right = n4->left = n4->right = NULL;


	if (n1->data != NULL) {
		printf("n1의 노드 : %d\n", n1->data);
		if (n1->left) {
			printf("n1의 왼쪽 자식 노드: %d\n", *n1->left);
			if (n1->right)
				printf("n1의 오른쪽 자식 노드: %d\n", *n1->right);
		}
	}

	TreeNode *tmp = n6;

	inorder(tmp);
	printf("\n");
	preorder(tmp);
	printf("\n");
	postorder(tmp);


	free(n1);
	free(n2);
	free(n3);
	free(n4);
	free(n5);
	free(n6);

	return 0;
}

//전위순회
void preorder(TreeNode *root) {

	// 
	if (root) {
		printf("%d ", root->data);
		if (root->left)
			preorder(root->left);
		if (root->right)
			preorder(root->right);
	}
}
//중위순회
void inorder(TreeNode *root) {
	if (root) {
		inorder(root->left);	//왼쪽 서브트리 순회
		printf("%d ", root->data);
		inorder(root->right);	//오른쪽 서브트리 순회
	}

}
//후위순회
void postorder(TreeNode *root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}

}