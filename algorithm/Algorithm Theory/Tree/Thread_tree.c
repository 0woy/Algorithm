/*
�й�: 20204624
�̸�: ������

���α׷� ����: ������ ���� Ʈ���� �����Ͽ� Ʈ�� ���� ��ȸ �ϱ�
*/

#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	char data;
	struct TreeNode *left, *right;
	int is_thread;	//������� TRUE
}TreeNode;

// �ļ��� ã��
TreeNode *find_successor(TreeNode *node) {

	// rnode: ���� ����� ������ ��� 
	TreeNode *rnode = node->right;

	// rnode�� NULL�̰ų� ���� ��尡 �������� rnode ��ȯ
	if (rnode == NULL || node->is_thread == TRUE)
		return rnode;

	// rnode�� ������ �ڽ��̸� ���� ���� ���� �̵�
	while (rnode->left != NULL)
		rnode = rnode->left;
	return rnode;
}

// ������ Ʈ���� ������ȸ
void thread_inorder(TreeNode *root) {

	// ���� ���� ���� �̵�
	while (root->left != NULL)
		root = root->left;

	do {
		printf("%c -> ", root->data); // ������ ���
		root = find_successor(root);
	} while (root);	// ��尡 NULL�� �ƴ϶�� �ݺ�
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