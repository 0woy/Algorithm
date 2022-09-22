#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

int get_node_count(TreeNode *root) {
		
	int count = 0;	//노드 개수

	// 현재 노드가 NULL이 아니면 왼쪽, 오른쪽 자식으로 이동.
	if (root != NULL) {

		// 자기 자신 = 1
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
	TreeNode *none =NULL;	// 노드가 없을 시

	int count = get_node_count(tmp);

	printf("전체 노드의 개수는: %d\n", count);

}