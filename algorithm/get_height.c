#include<stdio.h>
#include<stdlib.h>


// MAX ����, ������ �켱������ ����Ͽ� ��ȣ �ȿ� �־��־�� ��.
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

int get_height(TreeNode *root) {
	int height = 0; //Ʈ�� ���� 
	
	// ���� ��尡 NULL�� �ƴϸ�, ���� �� ������ ����Ʈ���� �� ū �� ��ȯ
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
	
	printf("Ʈ���� ����: %d\n", get_height(tmp));
	
}