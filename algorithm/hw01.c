#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
typedef struct {
	int id;
	char *name;
	int kor, eng, math,tot;
	double avg;
	
}student;


typedef struct ListNode{
	student data;
	struct ListNode * link;
}ListNode;

void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}


void insert_node(ListNode **phead, ListNode *pre, ListNode *new_node) {


	ListNode *temp;
	// 첫 노드 삽입
	if (*phead == NULL) {
		*phead = new_node; 
		pre = *phead;
	}
	else 
	{
		temp = *phead;
		while (temp->link != NULL) {
			temp = temp->link;
		}
		temp->link = new_node;

	}

}

void display(ListNode *head)
{
	ListNode* p = head;
	printf("┌━━━━━━━━━┬━━━━━━━┬━━━━━━┬━━━━━━┬━━━━━━┬━━━━━━┬━━━━━━━━┐\n");
	printf("│ 학    번│ 이 름 │ 수학 │ 영어 │ 국어 │ 총점 │ 평  균 │\n");
	printf("├━━━━━━━━━┼━━━━━━━┼━━━━━━┼━━━━━━┼━━━━━━┼━━━━━━┼━━━━━━━━┤\n");
	while (p != NULL)
	{
		printf(" %d │ %s %5d %5d %7d %6d %8.2f\n", p->data.id, p->data.name, p->data.math, p->data.eng, p->data.kor, p->data.tot, p->data.avg);
		p = p->link;
	}
	printf("└━━━━━━━━━┴━━━━━━━┴━━━━━━┴━━━━━━┴━━━━━━┴━━━━━━┴━━━━━━━━┘\n\n");
	printf("\n");
}


ListNode *create_node(student data, ListNode *link) {
	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
	temp->data = data;
	temp->link = link;

	return temp;
}


int main() {

	SetConsoleOutputCP(65001);
	 
	FILE *fp;
	
	ListNode *list1=NULL;
	student temp;
	char buffer[30];
	int cnt = 0;	// 학생 수
	int size = 0;	// 이름 크기

	fp = fopen("data2.txt", "r");
	if (fp == NULL)
	{
		printf("파일을 여는데 실패했습니다.");
		exit(1);
	}

	while (!feof(fp)) {
		fscanf(fp,"%d %s %d %d %d", &temp.id, buffer, &temp.kor, &temp.eng, &temp.math);
		size = strlen(buffer);
		temp.name = (char*)malloc(sizeof(char)*(size + 1));
		strcpy(temp.name, buffer);
		temp.tot = temp.math + temp.kor + temp.eng;
		temp.avg = temp.tot / 3.0;
		insert_node(&list1, NULL, create_node(temp, NULL));
	}
	display(list1);

}
