#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	char data;
	struct TreeNode *left, *right;
	int is_thread;	//스레드면 TRUE
}TreeNode;

// 후속자 찾기
TreeNode *find_successor(TreeNode *node) {

	// rnode: 현재 노드의 오른쪽 노드 
	TreeNode *rnode = node->right;

	// rnode가 NULL이거나 현재 노드가 스레드라면 rnode 반환
	if (rnode == NULL || node->is_thread == TRUE)
		return rnode;

	// rnode가 오른쪽 자식이면 가장 왼쪽 노드로 이동
	while (rnode->left!=NULL)
		rnode = rnode->left;
	return rnode;
}

// 스레드 트리의 중위순회
void thread_inorder(TreeNode *root) {

	// 가장 왼쪽 노드로 이동
	while (root->left != NULL)
		root = root->left;

	do{
		printf("%c -> ", root->data); // 데이터 출력
		root = find_successor(root);
	} while (root);	// 노드가 NULL이 아니라면 반복
}

int main() {
/*
			G
	C				F
A		B		D		E

*/

	TreeNode n1 = { 'A',NULL,NULL,1 };
	TreeNode n2 = { 'B',NULL,NULL,1 };
	TreeNode n3 = { 'C',&n1,&n2,0 };
	TreeNode n4 = { 'D',NULL,NULL,1 };
	TreeNode n5 = { 'E',NULL,NULL,0 };
	TreeNode n6 = { 'F',&n4,&n5,0 };
	TreeNode n7 = { 'G',&n3,&n6 ,0 };

	n1.right = &n3;
	n2.right = &n7;
	n4.right = &n6;

	TreeNode *tmp = &n7;
	thread_inorder(tmp);



	
}
