#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student {
	int id;
	char *names;
	int score;
}student;

typedef struct ListNode {
	student data;
	struct ListNode *link;
}ListNode;


void insert_node(ListNode **head, ListNode *pre, ListNode *new_node);	//노드 삽입
ListNode *create_node(student data, ListNode *link);	//노드 생성
void display(ListNode *head);	// 연결리스트 출력
void  qsort(ListNode *head, ListNode *tail);	// 연결리스트 퀵정렬
ListNode * partition(ListNode *head, ListNode *tail);

ListNode *tail=NULL;

int main() {
	FILE *fp;
	char buffer[30];
	ListNode *head = NULL;
	student temp;
	int size = 0; // 이름 길이
	int cnt = 0; // 학생 수

	fp = fopen("data.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%d %s %d", &temp.id, buffer, &temp.score);
		size = strlen(buffer);
		temp.names = (char*)malloc(sizeof(char)*(size + 1));
		strcpy(temp.names, buffer);
		insert_node(&head, NULL, create_node(temp, NULL));
		cnt++;
	}


	display(head);
	//for(int i=0;i<3;i++)
	//qsort(head, tail,i);

	qsort(head, tail);
	display(head);

	fclose(fp);

}
void insert_node(ListNode **head, ListNode *pre, ListNode *new_node) {

	// 첫 노드 삽입
	if (*head == NULL) {
		*head = new_node;
		pre = *head;
		tail = *head;
	}
	
	else
	{
		ListNode *temp;
		temp = *head;
		while (temp->link != NULL) {
			temp = temp->link;
		}
		temp->link = new_node;
		tail = new_node;

	}

}

ListNode *create_node(student data, ListNode *link) {
	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
	temp->data = data;
	temp->link = NULL;

	return temp;
}

void display(ListNode *head)
{
	ListNode* p = head;
	int i = 0;
	while (p != NULL)
	{
		printf("%d번: %3d %3s %3d \n",++i, p->data.id, p->data.names, p->data.score);
		p = p->link;
	}

	printf("\n");
}

void swap(ListNode *head, ListNode *value) {
	student tmp;

	// 노드 위치 바꾸기
	tmp = head->data;
	head->data = value->data;
	value->data = tmp;

	head = head->link;
}

// 분할
ListNode * partition(ListNode *head, ListNode *tail) {	// 처음, 끝
		
	ListNode *pivot = head;
	ListNode *value = head;
	student tmp;

	while (value != NULL && value != tail) {
		if (value->data.id<tail->data.id) {
			pivot = head;

			tmp = head->data;
			head->data = value->data;
			value->data = tmp;
			//swap(head, value);
			head = head->link;
		}
		// 다음 노드 방문
		value = value->link;
	}

	//맨 뒤 노드를 현재 노드로 바꾸기
	tmp = head->data;
	head->data = tail->data;
	tail->data = tmp;
	return pivot;
	
}

void qsort(ListNode * head, ListNode *tail) {

	if (head == tail)
		return;

	
	ListNode *pivot = partition(head, tail);

	if (pivot != NULL && pivot->link != NULL) {
		qsort(pivot->link, tail);
	}
	if (pivot != NULL && head != pivot)
		qsort(head, pivot);
}