/*
학번: 20204624
이름: 박윤아

프로그램 설명:
순환을 이용한 전위, 중위, 후위 순회
스택을 이용한 전위, 중위, 후위 순회
큐를 이용한 레벨 순회
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
	bool check;
}TreeNode;

#define SIZE 10
int tos = -1;
TreeNode* stack[SIZE];

typedef struct {
	TreeNode* data[SIZE];
	int front, rear;
}QueueType;

void init(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->rear == q->front);
}

int is_full(QueueType *q) {
	return((q->rear + 1) % SIZE == q->front);
}

void enqueue(QueueType* q, TreeNode* n) {
	if (is_full(q)) {
		fprintf(stderr, "The Queue is Full");
		return;
	}
	q->rear = (q->rear + 1) % SIZE;
	q->data[q->rear] = n;
}

TreeNode* dequeue(QueueType* q) {
	if (is_empty(q)) {
		fprintf(stderr, "The Queue is Empty");
		return;
	}
	q->front = (q->front + 1) % SIZE;
	return q->data[q->front];
}

void push(TreeNode* n) {
	if (tos >= SIZE) {
		fprintf(stderr,"Error: stack is full");
		return;
	}
	else 
		stack[++tos] = n;	
}

TreeNode* pop() {
	if (tos < 0) return NULL;
	else {
		return stack[tos--];
	}
}


void recur_preorder(TreeNode* root);
void recur_inorder(TreeNode* root);
void recur_postorder(TreeNode* root);
void inorder_iterator(TreeNode* root);
void preorder_iterator(TreeNode* root);
void postorder_iterator(TreeNode* root);

int main() {
/*			  15
		4			20
	1			16		25
*/

	TreeNode n1 = { 1,NULL,NULL };
	TreeNode n2 = { 4,&n1,NULL };
	TreeNode n3 = { 16,NULL,NULL };
	TreeNode n4 = { 25,NULL,NULL };
	TreeNode n5 = { 20,&n3,&n4 };
	TreeNode n6 = { 15,&n2,&n5 };

	printf("순환을 이용한 순회\n\n전위 순회\n");
	recur_preorder(&n6);
	printf("\n중위순회\n");
	recur_inorder(&n6);
	printf("\n후위순회\n");
	recur_postorder(&n6);
	printf("\n\n반복을 이용한 순회\n\n중위순회\n");
	inorder_iterator(&n6);
	printf("\n전위순회\n");
	preorder_iterator(&n6);
	printf("\n후위순회\n");
	postorder_iterator(&n6);

}

//레벨 순회
void level_order(TreeNode* root) {
	QueueType q;
	TreeNode* tmp = root;
	
	init(&q);
	if (!tmp) return;

	enqueue(&q, tmp);
	while (!is_empty(&q)) {
		tmp = dequeue(&q);
		printf("[%d] -> ", tmp->data);
		if (tmp->left) enqueue(&q, tmp->left);
		if (tmp->right) enqueue(&q, tmp->right);
			
	}

}

//반복을 이용한 순회
//전위 순회
void preorder_iterator(TreeNode* root) {
	TreeNode* tmp = root;
	tos = -1;

	while (1) {
		while (tmp) {
			printf("[%d] -> ", tmp->data);
			if (tmp->right)
				push(tmp);
			tmp = tmp->left;
		}
		tmp = pop();
		if (!tmp) break;
		tmp = tmp->right;
	}
}

//중위 순회
void inorder_iterator(TreeNode* root) {
	TreeNode* tmp = root;
	tos = -1;

	while (1) {
		while (tmp!=NULL) {
			push(tmp);
			tmp = tmp->left;
		}
		tmp = pop();
		if (!tmp) return;
		printf("[%d] -> ", tmp->data);
		tmp = tmp->right;
	}
}

//후위 순회
void postorder_iterator(TreeNode* root) {
	TreeNode* tmp = root;
	tos = -1;

	while (1) {
		while (tmp != NULL&&!tmp->check) {
			push(tmp);
			tmp = tmp->left;
		}
		tmp = pop();
		if (!tmp) return;
		if (tmp->right) {
			if (tmp->right->check) {
				printf("[%d] ->", tmp->data);
				tmp->check = true;
			}
			else {
				push(tmp);
				tmp = tmp->right;
			}
		}
		else {
			printf("[%d] -> ", tmp->data);
			tmp->check = true;
		}

	}
}


//순환을 이용한 순회
//전위 순회
void recur_preorder(TreeNode* root) {
	TreeNode* tmp = root;
	if (tmp) {
		printf("%d -> ", tmp->data);
		recur_preorder(tmp->left);
		recur_preorder(tmp->right);
	}
	
}

//중위 순회
void recur_inorder(TreeNode* root) {
	TreeNode* tmp = root;
	if (tmp) {
		recur_inorder(tmp->left);
		printf("%d -> ", tmp->data);
		recur_inorder(tmp->right);
	}
}

//후위 순회
void recur_postorder(TreeNode* root) {
	TreeNode* tmp = root;
	if (tmp) {
		recur_postorder(tmp->left);
		recur_postorder(tmp->right);
		printf("%d -> ", tmp->data);
	}
}