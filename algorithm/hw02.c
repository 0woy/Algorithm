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


void insert_node(ListNode **head, ListNode *pre, ListNode *new_node);
ListNode *create_node(student data, ListNode *link);
void display(ListNode *head);



int main() {
	FILE *fp;
	char buffer[30];
	ListNode *head = NULL;
	student temp;
	int size = 0; // 이름 길이

	fp = fopen("data.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%d %s %d", &temp.id, buffer, &temp.score);
		size = strlen(buffer);
		temp.names = (char*)malloc(sizeof(char)*(size + 1));
		strcpy(temp.names, buffer);
		insert_node(&head, NULL, create_node(temp, NULL));
	}

	display(head);
	fclose(fp);

}
void insert_node(ListNode **head, ListNode *pre, ListNode *new_node) {

	// 첫 노드 삽입
	if (*head == NULL) {
		*head = new_node;
		pre = *head;
	}
	
	else
	{
		ListNode *temp;
		temp = *head;
		while (temp->link != NULL) {
			temp = temp->link;
		}
		temp->link = new_node;
	//	pre = temp;
	//	pre->link = new_node;
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
/*	printf("┌━━━━━━━━━━━┬━━━━━━━━━━┬━━━━━━━━━━┬\n");
	printf("│ 학    번  │  이 름   │ 총점     │\n");
	printf("├━━━━━━━━━━━┼━━━━━━━━━━┼━━━━━━━━━━┬\n");
*/
	while (p != NULL)
	{
		printf("%d번: %3d %3s %3d\n",++i, p->data.id, p->data.names, p->data.score);
		p = p->link;
	}
//	printf("└━━━━━━━━━━━┴━━━━━━━━━━━━┴━━━━━━━━━━-┘\n\n");
	printf("\n");
}
