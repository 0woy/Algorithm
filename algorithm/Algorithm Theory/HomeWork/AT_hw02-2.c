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

// Define STACK size
#define SIZE 40000

// init stack info
int top = -1;	// current index
TreeNode* stack[SIZE];


//Declare Function Prototypes
void insert_repeat(TreeNode** root, element key);
void Iterative_inorder(TreeNode * root);


int main() {

	//Declare variables
	FILE *fp;			// FILE value;
	element temp;		// element value 
	TreeNode * root = NULL;	// Initialize root node of binary tree as NULL

	fp = fopen("HW02_data.txt", "r");	//Open FILE

	if (!fp) {		//If file doesn't open 
		printf("CAN NOT OPEN FILE");
		return;		//Exit the Program
	}

	// Declare colck_t variables for Calculating running time
	clock_t start_i, end_i, start_t, end_t;		//i: insert time, t:Traversal time 

	start_i = clock();	//Start Time (INSERT)
	
	//Run until end of file
	while (!feof(fp))	
	{
		fscanf(fp, "%d", &temp);	// Read data and save it in temp 
		insert_repeat(&root, temp);	//Insert the read data into the tree
	}
	end_i = clock();	//End Time(INSERT)



	printf("Inorder Traversal\n");
	start_t = clock();			//Start Time(TRAVERSAL)
	Iterative_inorder(root);	//Inorder Traversal using iterations
	end_t = clock();			//End Time(TRAVERSAL)

	printf("\nCount nodes : %d\n", count_nodes(root));
	printf("Count Leaf Nodes : %d\n", count_leaf_nodes(root));
	printf("Get Tree's Height : %d\n", get_height(root));

	printf("Time spent Inserting: %lf\n", (double)(end_i - start_i) / CLOCKS_PER_SEC);
	printf("Time spent Traversal: %lf\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

	free(root);	//Release Dynamic Allocation Memory 
	fclose(fp); // Close the file

	return 0;
}

// Insert node using Iterations
void insert_repeat(TreeNode** root, element key) {

	TreeNode* p = NULL;		//init Parents node to NULL
	TreeNode* tmp = *root;	//tmp that points root(tmp will be current node)

	// Repeat until tmp is NULL
	while (tmp != NULL) {
		p = tmp;	// save tmp to p (To point to the parents)

		if (key < tmp->data)	//if key is smaller than current data,
			tmp = tmp->left;	//Move to the left child

		else if (key > tmp->data)	//if key is bigger than current data,
			tmp = tmp->right;		//Move to the right child

		//If Duplicate value aleady exists,
		else {
			printf("Duplicate value already exists.\n");
			return;	//Exit insert_repeat func
		}
	}

	
	TreeNode *n = create_node(key); //Create a new node 

	if (p != NULL) { // if parents node exists,
		if (key < p->data)	// if key is smaller than parents
			p->left = n;	// allocate new node to parents's left child

		else	// if key is bigger than parents
			p->right = n;	//Allocate new node to parent's right child
	}

	// if parents node does not exist,
	else
		*root = n; //allocate new node to root
	
}

// Push Node to stack
void push(TreeNode* n) {
	if (top < SIZE - 1)		//if stack is not full
		stack[++(top)] = n;	// index +=1 and push node to stack
}

//Pull node from stack
TreeNode* pop() {
	TreeNode *tmp = NULL; //Declare tmp to contain node

	if (top >= 0) //if stack is not empty
		tmp = stack[top--];	//allocate the current node in stack to tmp

	return tmp;	// return tmp
}

// Inorder Traversal using iterations
void Iterative_inorder(TreeNode * root) {

	top = -1;	// init stack's index
	TreeNode* tmp = root;	// Declare tmp that points root

	while (1) {		//Infinite roop

		while (tmp !=NULL)	//Repeat until tmp is NULL
		{
			push(tmp);	// push node into stack
			tmp = tmp->left;	//Move to the left child
		}
		
		tmp = pop();	//pull out the top data in stack and allocate it to tmp

		if (tmp == NULL)	// if returned node is NULL
			break;	//Exit roop
		
		else {	//if returned node is not NULL,
			printf("[%d] ", tmp->data);	//Print data
			tmp = tmp->right;	//Move to the right child
		}
	}
}