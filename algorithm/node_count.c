#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

int get_node_count(TreeNode *root) {
		
	int count = 0;	//��� ����

	// ���� ��尡 NULL�� �ƴϸ� ����, ������ �ڽ����� �̵�.
	if (root != NULL) {

		// �ڱ� �ڽ� = 1
		count = 1 +
			get_node_count(root->left) +
			get_node_count(root->right);
	}
	return count;
}


int main() {

	TreeNode n1 = { 10, NULL,NULL };
	TreeNode n2 = { 20,NULL,NULL };
	TreeNode n3 = { 30, &n1, &n2 };
	TreeNode n4 = { 60, NULL,NULL };
	TreeNode n5 = { 65, &n4, NULL };
	TreeNode n6 = { 50, &n3,&n5 };
	
	TreeNode *tmp = &n6;
	TreeNode *none =NULL;	// ��尡 ���� ��

	int count = get_node_count(tmp);

	printf("��ü ����� ������: %d\n", count);

}