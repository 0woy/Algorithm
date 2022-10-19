/*
학번: 20204624
이름: 박윤아

프로그램 설명: 수식 트리 계산
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

//		   *
//	   *	   +
//	  1	 4	 16   25


TreeNode n1 = { 1,NULL,NULL };
TreeNode n2 = { 4,NULL,NULL };
TreeNode n3 = { '*',&n1,&n2 };
TreeNode n4 = { 16,NULL,NULL };
TreeNode n5 = { 25,NULL,NULL };
TreeNode n6 = { '+',&n4,&n5 };
TreeNode n7 = { '+',&n3,&n6 };
TreeNode *exp = &n7;


// 수식 계산 함수

int evaluate(TreeNode *root) {

	if (!root)
		return 0;
	if (root->left == NULL && root->right == NULL) {
		return root->data;
	}
	else {
		int op1 = evaluate(root->left);
		int op2 = evaluate(root->right);
		printf("%d %c %d를 계산합니다.\n", op1, root->data, op2);
		switch (root->data) {

		case '+':
			return op1 + op2;
		case '-':
			return op1 - op2;
		case '*':
			return op1 * op2;
		case '/':
			return op1 / op2;

		default:
			break;
		}
	}
	return 0;
}


int main(void) {

	printf("수식의 값 : %d", evaluate(exp));
}