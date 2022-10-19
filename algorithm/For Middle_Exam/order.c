/*
�й�: 20204624
�̸�: ������

���α׷� ����:
��ȯ�� �̿��� ����, ����, ���� ��ȸ
������ �̿��� ����, ����, ���� ��ȸ
ť�� �̿��� ���� ��ȸ
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

	printf("��ȯ�� �̿��� ��ȸ\n\n���� ��ȸ\n");
	recur_preorder(&n6);
	printf("\n������ȸ\n");
	recur_inorder(&n6);
	printf("\n������ȸ\n");
	recur_postorder(&n6);
	printf("\n\n�ݺ��� �̿��� ��ȸ\n\n������ȸ\n");
	inorder_iterator(&n6);
	printf("\n������ȸ\n");
	preorder_iterator(&n6);
	printf("\n������ȸ\n");
	postorder_iterator(&n6);

}

//���� ��ȸ
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

//�ݺ��� �̿��� ��ȸ
//���� ��ȸ
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

//���� ��ȸ
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

//���� ��ȸ
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


//��ȯ�� �̿��� ��ȸ
//���� ��ȸ
void recur_preorder(TreeNode* root) {
	TreeNode* tmp = root;
	if (tmp) {
		printf("%d -> ", tmp->data);
		recur_preorder(tmp->left);
		recur_preorder(tmp->right);
	}
	
}

//���� ��ȸ
void recur_inorder(TreeNode* root) {
	TreeNode* tmp = root;
	if (tmp) {
		recur_inorder(tmp->left);
		printf("%d -> ", tmp->data);
		recur_inorder(tmp->right);
	}
}

//���� ��ȸ
void recur_postorder(TreeNode* root) {
	TreeNode* tmp = root;
	if (tmp) {
		recur_postorder(tmp->left);
		recur_postorder(tmp->right);
		printf("%d -> ", tmp->data);
	}
}