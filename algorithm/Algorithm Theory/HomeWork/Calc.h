#include<stdio.h>

//Define int as element
typedef int element;

// Define TreeNode 
typedef struct TreeNode {
	element data;
	struct TreeNode * left, *right;
}TreeNode;

TreeNode* create_node(element key);		// Dynamic memory allocation
int count_nodes(TreeNode* root);		// Counting Nodes in Tree
int count_leaf_nodes(TreeNode* root);	// Count Leaf Nodes in Tree
int get_height(TreeNode *root);			// Get Tree's Height