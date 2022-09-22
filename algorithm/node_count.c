#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNdoe;

int get_node_count(TreeNdoe *root) {
		
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

	TreeNdoe n1 = { 10, NULL,NULL };
	TreeNdoe n2 = { 20,NULL,NULL };
	TreeNdoe n3 = { 30, &n1, &n2 };
	TreeNdoe n4 = { 60, NULL,NULL };
	TreeNdoe n5 = { 65, &n4, NULL };
	TreeNdoe n6 = { 50, &n3,&n5 };
	
	TreeNdoe *tmp = &n6;
	TreeNdoe *none =NULL;	// ��尡 ���� ��

	int count = get_node_count(tmp);

	printf("��ü ����� ������: %d\n", count);

}