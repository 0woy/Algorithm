#include "Calc.h"

// Create node 
TreeNode * create_node(element key) {
	
	TreeNode * n = (TreeNode*)malloc(sizeof(TreeNode));	//Dynamic allocation 

	//If memory allocation fails,
	if (n == NULL) {
		printf("Fail to allocate memory");
		return;	
	}

	n->data = key; //allocate key to new node's data 
	n->left = n->right = NULL;	// init new node's left&right as NULL
	return n;	// return new node
}

// Count all nodes in tree
int count_nodes(TreeNode *root) {
	TreeNode * tmp = root; //Declare tmp that points root

	// if tmp is NULL
	if (tmp == NULL)
		return 0;	// return zero

	// Plus 1 and Recall count_node func with left & right child as a parameter
	return 1 + count_nodes(tmp->left) + count_nodes(tmp->right);
}

// Count Leaf nodes in tree
int count_leaf_nodes(TreeNode* root) {

	TreeNode* tmp = root; //Declare tmp that points root
	int count = 0;	//variable to store the number of leaf nodes

	if (tmp != NULL) { //If tmp is not NULL	

		//If current node has any child,
		if (tmp->left != NULL || tmp->right != NULL) {
			//Recall this func with left & right child as a parameter 
			//and allocate returned value to count
			count = count_leaf_nodes(tmp->left) +	
				count_leaf_nodes(tmp->right);
		}

		else	//If current node is leaf node,
			return 1;	// return 1
	}
	return count;	// return number of leaf node 
	
}

// Get tree's height
int get_height(TreeNode* root) {
	
	int height = 0;	//variable to count tree's height

	if (root == NULL)	//if tree is empty
		return 0;	// height is 0

	else {	// tree is not empty

		//Recall this func with current node's left & right child as a parameter
		int left = get_height(root->left); 
		int right = get_height(root->right);
		
		//if (left/right) is bigger than (right/left),
		// allocate (left/right)+1 to height
		height = 1 + ((left > right) ? left : right);
	}

	return height; // return tree's height
}

