#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

int calc_dir(TreeNode *root) {
	
	// 트리가 비어있으면 종료
	if (root == NULL)
		return 0;

	int left_size = calc_dir(root->left);
	int right_size = calc_dir(root->right);
	return (root->data + left_size + right_size);

}


int main() {

//		  n1
//	n2			n3
//		    n4		n5



	TreeNode n4 = { 500,NULL,NULL };
	TreeNode n5 = { 200,NULL,NULL };
	TreeNode n3 = { 100,&n4,&n5};
	TreeNode n2 = { 50,NULL,NULL };
	TreeNode n1 = { 0,&n2,&n3};

	TreeNode *tmp = &n1;
	int total = calc_dir(tmp);
	printf("디렉토리의 크기 = %d\n", total);

}
