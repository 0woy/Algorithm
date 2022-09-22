#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

int get_leaf_count(TreeNode *root) {

	int count = 0;
	if (root != NULL) {
		// 자식이 하나라도 있으면 바로 자식 노드로 넘어감.
		if (root->left != NULL || root->right != NULL) {
			count = get_leaf_count(root->left) +
				get_leaf_count(root->right);
		}

		// 자식이 하나도 없으면 1을 반환
		else
			return 1;
	}
	return count;
}


int main() {

/*			n6
	 n3			   n5
  n1    n2	   n4	   n8
				  n7
 */

	TreeNode n1 = { 10, NULL,NULL };
	TreeNode n2 = { 20,NULL,NULL };
	TreeNode n3 = { 30, &n1, &n2 };
	TreeNode n7 = { 63 ,NULL,NULL };
	TreeNode n4 = { 60, NULL,&n7 };
	TreeNode n8 = { 70,NULL,NULL };
	TreeNode n5 = { 65, &n4, &n8 };
	TreeNode n6 = { 50, &n3,&n5 };

	TreeNode *tmp = &n6;
	printf("단말 노드의 개수: %d\n", get_leaf_count(tmp));

}