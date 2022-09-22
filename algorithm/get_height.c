#include<stdio.h>
#include<stdlib.h>


// MAX 정의, 연산자 우선순위를 고려하여 괄호 안에 넣어주어야 함.
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

int get_height(TreeNode *root) {
	int height = 0; //트리 높이 
	
	// 현재 노드가 NULL이 아니면, 왼쪽 과 오른쪽 서브트리중 더 큰 값 반환
	if (root != NULL) {
		height = 1+	
			MAX(get_height(root->left), get_height(root->right));
	}
	return height;
}

int main() {
/*		  n6
	 n3			 n5
  n1    n2	  n4
				 n7
  */

	TreeNode n1 = { 10, NULL,NULL };
	TreeNode n2 = { 20,NULL,NULL };
	TreeNode n3 = { 30, &n1, &n2 };
	TreeNode n7 = { 63 ,NULL,NULL };
	TreeNode n4 = { 60, NULL,&n7 };
	TreeNode n5 = { 65, &n4, NULL };
	TreeNode n6 = { 50, &n3,&n5 };

	TreeNode *tmp = &n6;
	
	printf("트리의 높이: %d\n", get_height(tmp));
	
}