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


void insert_node(ListNode **head, ListNode *pre, ListNode *new_node);	//��� ����
ListNode *create_node(student data, ListNode *link);	//��� ����
void display(ListNode *head);	// ���Ḯ��Ʈ ���
void  qsort(ListNode *head, ListNode *tail);	// ���Ḯ��Ʈ ������
ListNode * partition(ListNode *head, ListNode *tail);

ListNode *tail=NULL;

int main() {
	FILE *fp;
	char buffer[30];
	ListNode *head = NULL;
	student temp;
	int size = 0; // �̸� ����
	int cnt = 0; // �л� ��

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

	// ù ��� ����
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
		printf("%d��: %3d %3s %3d \n",++i, p->data.id, p->data.names, p->data.score);
		p = p->link;
	}

	printf("\n");
}

void swap(ListNode *head, ListNode *value) {
	student tmp;

	// ��� ��ġ �ٲٱ�
	tmp = head->data;
	head->data = value->data;
	value->data = tmp;

	head = head->link;
}

// ����
ListNode * partition(ListNode *head, ListNode *tail) {	// ó��, ��
		
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
		// ���� ��� �湮
		value = value->link;
	}

	//�� �� ��带 ���� ���� �ٲٱ�
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