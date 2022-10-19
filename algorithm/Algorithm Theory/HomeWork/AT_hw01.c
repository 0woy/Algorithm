/*
학번: 20204624
이름: 0woy

문제: 파일에서 데이터를 읽어온 후 학번, 이름, 총점 순으로 퀵 정렬을 이용해 데이터 정렬하기.
*/


#define _CRT_SECURE_NO_WARNINGS 

// 필요한 헤더 파일 추가
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

typedef struct student {
	int id;
	char *names;
	int score;
}student;

typedef struct ListNode {
	student data;
	struct ListNode *link;	
}ListNode;


void insert_node(ListNode **head, ListNode *pre, ListNode *new_node);	
ListNode *create_node(student data, ListNode *link);	
void display(ListNode *head);	
void  qsort(ListNode *head, ListNode *tail);	
ListNode * partition(ListNode *head, ListNode *tail);

ListNode *tail=NULL;

int main() {

	FILE *fp;
	char buffer[30];	
	ListNode *head = NULL; 
	student temp;	

	int size = 0; 
	int cnt = 0; 

	fp = fopen("HW01_data.txt", "r");

	if (fp == NULL) {
		printf("CAN NOT OPEN FILE");
		exit(1);
	}


	while (!feof(fp)) {
		fscanf(fp, "%d %s %d", &temp.id, buffer, &temp.score);	
		size = strlen(buffer);	

		temp.names = (char*)malloc(sizeof(char)*(size + 1));
		strcpy(temp.names, buffer);

		insert_node(&head, NULL, create_node(temp, NULL));
		//cnt++;
	}

	display(head,-1);
	
	for (int i = 0; i < 3; i++) {
		
		qsort(head, tail, i);
		display(head,i);
	}
	
	free(head);	
	fclose(fp);

}


void insert_node(ListNode **head, ListNode *pre, ListNode *new_node) {

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

void display(ListNode *head, int key)
{
	ListNode* p = head;
	int i = 0;
	switch (key)
	{
	case -1:
		printf("데이터 파일\n");
		break;
	case 0:
		printf("\n학번으로 정렬\n");
		break;
	case 1:
		printf("\n이름으로 정렬\n");
		break;
	case 2:
		printf("\n총점으로 정렬\n");
		break;
	default:
		break;
	}
	while (p != NULL)
	{
		printf("%d번 %3d %3s %3d \n",++i, p->data.id, p->data.names, p->data.score);
		p = p->link;
	}

	printf("\n");
}

ListNode * partition(ListNode *head, ListNode *tail, int key) {	
		
	ListNode *pivot = head;
	ListNode *value = head;	
	student tmp;	

	if (key == 1) {
		while (value != NULL && value != tail) {
			if (strcmp(value->data.names, tail->data.names)==-1) {
				pivot = head;

				tmp = head->data;
				head->data = value->data;
				value->data = tmp;
				head = head->link;
			}
			value = value->link;
		}

		tmp = head->data;
		head->data = tail->data;
		tail->data = tmp;
		return pivot;
	}

		while (value != NULL && value != tail) {
			if (key == 0) {
				if (value->data.id < tail->data.id) {
					pivot = head;

					tmp = head->data;
					head->data = value->data;
					value->data = tmp;
					head = head->link;
				}
			}

			if (key == 2) {

				if (value->data.score > tail->data.score) {
					pivot = head;

					tmp = head->data;
					head->data = value->data;
					value->data = tmp;
					head = head->link;
				}
			}
			value = value->link;
		}

		tmp = head->data;
		head->data = tail->data;
		tail->data = tmp;
		return pivot;
}
	

void qsort(ListNode * head, ListNode *tail, int key) {

	if (head == tail)
		return;

	ListNode *pivot = partition(head, tail,key);

	if (pivot != NULL && pivot->link != NULL) {
		qsort(pivot->link, tail,key);
	}

	if (pivot != NULL && head != pivot)
		qsort(head, pivot,key);
}
