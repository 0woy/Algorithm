/* ----------------------------------------------
제작일 : 2022.09.27 ~ 2022.10.02

학번: 20204624
이름: 박윤아

프로그램 설명:
1. 순환 과 반복을 이용하여 이진 탐색 트리 구현
2. 데이터를 순회/삽입시 시간 비교
3. 트리의 전체 노드 수 구하기
4. 트리의 높이 구하기
5. 트리의 단말노드 개수 구하기
---------------------------------------------------*/

// Error C4996 Prevention
#define _CRT_SECURE_NO_WARNINGS	

//Add required header file
#include<stdlib.h>	
#include<string.h>
#include<time.h>

// Header to reduce code duplication(count node, leaf, height etc)
#include "Calc.h" 

//Declare Function Prototypes
TreeNode* insert_recur(TreeNode ** root, element key);
void inorder_recur(TreeNode * root);

int main() {

	//Declare varialbes
	FILE *fp;			//FILE variable
	element temp;		// element variable
	TreeNode * root = NULL;	// Initialize root node of binary tree to NULL

	fp = fopen("HW02_data.txt", "r");	//Open FILE

	//If file doesn't open 
	if (!fp) {
		printf("CAN NOT OPEN FILE");
		return;	//Exit the Program
	}

	// Declare colck_t variables for Calculating running time
	clock_t start_i, end_i, start_t, end_t;	//i: insert time, t:Traversal time 

	start_i = clock();	//Start Time (INSERT)

	while (!feof(fp))	// Run until end of file
	{
		fscanf(fp, "%d", &temp);		// Read data and save it in temp 
		root =insert_recur(root, temp);	//Insert the read data into the tree
	}
	 end_i = clock(); //End Time(INSERT)

	 printf("Inorder Traversal\n");

	start_t = clock();		//Start Time(TRAVERSAL)
	inorder_recur(root);	//Inorder_Traversal using recursion
	end_t = clock();		//End Time(TRAVERSAL)

	printf("\nCount nodes : %d\n", count_nodes(root));
	printf("Count Leaf Nodes : %d\n", count_leaf_nodes(root));
	printf("Get Tree's Height : %d\n", get_height(root));
	
	printf("Time spent Inserting: %lf\n", (double)(end_i - start_i) / CLOCKS_PER_SEC);
	printf("Time spent Traversal: %lf\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

	free(root);	//Dynamic Allocation Memory Release
	fclose(fp);	// Close the FILE

	return 0;	
}


// Insert node using Recursive
TreeNode* insert_recur(TreeNode * root, element key) {
	TreeNode * tmp = root;

	// if tmp is NULL,
	if (tmp == NULL) {
		return create_node(key); //return new node
	}
	
	
	if (key< tmp->data ) //if new data is smaller than current node,
		tmp->left = insert_recur(tmp->left, key);	// Move to the left and Recall this func

	else if (key > tmp->data) //if new node is bigger than current node,
		tmp->right =insert_recur(tmp->right, key);	//Move to the right and Recall this func

	//If Duplicate value aleady exists
	else {
		printf("Duplicate value already exists.\n");
		return;	//Exit insert_recur func
	}

	return tmp;	// Return BinaryTree that inserted new node
}

// Inorder Traversal using Recursive
void inorder_recur(TreeNode *root) {
	TreeNode * tmp = root;	// Declare tmp that points root

	//if tmp is not NULL
	if (tmp != NULL) {
		inorder_recur(tmp->left);		//Recall this func with left child as a parameter
		printf("[%d] ", tmp->data);		//print data
		inorder_recur(tmp->right);		//Recall this func with right child as a parameter
	}
}

