/*
이름: 박윤아
학번: 20204624

프로그램 설명: 큐를 이용한 레벨 순회

*/

#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

#define MAX_QUEUE_SIZE 100
typedef TreeNode *element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;


void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		printf("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType *q)
{
	if (is_empty(q))
		printf("큐가 비었습니다.\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(TreeNode *root);

int main() {

	TreeNode *n1, *n2, *n3, *n4, *n5, *n6;
	n1 = (TreeNode*)malloc(sizeof(TreeNode));
	n2 = (TreeNode*)malloc(sizeof(TreeNode));
	n3 = (TreeNode*)malloc(sizeof(TreeNode));
	n4 = (TreeNode*)malloc(sizeof(TreeNode));
	n5 = (TreeNode*)malloc(sizeof(TreeNode));
	n6 = (TreeNode*)malloc(sizeof(TreeNode));

	n6->data = 15;
	n6->left = n2;
	n6->right = n5;
	n2->data = 4;
	n5->data = 20;
	n5->left = n3;
	n5->right = n4;
	n2->left = n1;
	n2->right = NULL;
	n1->data = 1;
	n3->data = 16;
	n4->data = 25;
	n1->left = n1->right = n3->left = n3->right = n4->left = n4->right = NULL;


	TreeNode *tmp = n6;
	printf("레벨순회\n");
	level_order(tmp);

	free(n1);
	free(n2);
	free(n3);
	free(n4);
	free(n5);
	free(n6);

	return 0;
}

//?占쎈꺼?占쏀?
void level_order(TreeNode *root) {
	QueueType q;
	TreeNode *tmp;
	init_queue(&q);
	enqueue(&q, root);
	while(!is_empty(&q)) {
		
		tmp = dequeue(&q);
		printf("[%d] ", tmp->data);
		if(tmp->left)
			enqueue(&q, tmp->left);
		if(tmp->right)
			enqueue(&q, tmp->right);
	}
}
