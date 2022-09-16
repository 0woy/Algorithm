#define _CRT_SECURE_NO_WARNINGS //scanf_s ���� �߻����� �ʵ��� ����

// �ʿ��� ������� �߰�
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// �л��� ������ ������ student ����ü
typedef struct student {
	int id;
	char *names;
	int score;
}student;


// �л����� ������ ���Ḯ��Ʈ�� �����ϱ����� LisNode ����ü
typedef struct ListNode {
	student data;
	struct ListNode *link;	//������ �����ϴ� link
}ListNode;


void insert_node(ListNode **head, ListNode *pre, ListNode *new_node);	//��� ����
ListNode *create_node(student data, ListNode *link);	//��� ����
void display(ListNode *head);	// ���Ḯ��Ʈ ���
void  qsort(ListNode *head, ListNode *tail);	// ���Ḯ��Ʈ ������
ListNode * partition(ListNode *head, ListNode *tail);	// �����Ľ� ���Ǵ� ���� �Լ�

ListNode *tail=NULL;

int main() {
	FILE *fp;
	char buffer[30];	// �̸��� �ӽ÷� �޾Ƶ� ����
	ListNode *head = NULL; // ���Ḯ��Ʈ�� ���� ���(head)
	student temp;	// ������ data�� �ӽ� �����ϴ� ����ü

	int size = 0; // �����Ҵ��� ���� �̸� ����
	int cnt = 0; // �л� ��

	fp = fopen("data.txt", "r");

	// ������ NULL�̶�� �޼��� ��� �� ����
	if (fp == NULL) {
		printf("������ ���� �� �����ϴ�.");
		exit(1);
	}


	while (!feof(fp)) {
		//���Ͽ��� �̸��� ������ �л� ������ �� �� �� �о�� temp�� ����
		fscanf(fp, "%d %s %d", &temp.id, buffer, &temp.score);	
		size = strlen(buffer);	

		// size�� �̿��� temp.names�� �޸𸮸� �����Ҵ�.
		temp.names = (char*)malloc(sizeof(char)*(size + 1));
		strcpy(temp.names, buffer);

		//���Ḯ��Ʈ�� tmp �߰�
		insert_node(&head, NULL, create_node(temp, NULL));
		//cnt++;
	}

	// ���Ͽ��� �о�� ���� ���
	display(head,-1);
	
	// i���� key�� �Ѱ� ���� ���¸� �ٲ�
	for (int i = 0; i < 3; i++) {
		
		qsort(head, tail, i);
		display(head,i);
	}
	
	free(head);	//�����޸� �Ҵ� ����
	fclose(fp);

}


void insert_node(ListNode **head, ListNode *pre, ListNode *new_node) {

	// ���� ����Ʈ�� ó������ ��尡 ���Ե� ��
	if (*head == NULL) {
		*head = new_node;	
		pre = *head;
		tail = *head;
	}
	
	// �̹� ���Ḯ��Ʈ�� ��尡 ���� ��
	else
	{
		ListNode *temp;	 // head�� ���� �ӽ÷� �����ϴ� temp
		temp = *head;
		while (temp->link != NULL) {
			temp = temp->link; //����ִ� ���(NULL)�� ã�ư�(�� ������ ���)
		}

		// ����ִ� ��忡 ���ο� ��� ����
		temp->link = new_node;

		// �� ������ ��� = �߰��� ���
		tail = new_node;

	}

}

// �Է� ���� ������ ���� ��� ���� �Լ�
ListNode *create_node(student data, ListNode *link) {

	//�Ű������� student data�� �޾Ƽ� temp ��忡 ������ temp ��ȯ.
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
		printf("�ѤѤ� ���� ���� �ѤѤ�\n");
		break;
	case 0:
		printf("�ѤѤ��й� ������ ���� �ѤѤ�\n");
		break;
	case 1:
		printf("�ѤѤ��̸� ������ ���ĤѤѤ�\n");
		break;
	case 2:
		printf("�ѤѤ����� ������ ���ĤѤѤ�\n");
		break;
	default:
		break;
	}
	while (p != NULL)
	{
		printf("%d��: %3d %3s %3d \n",++i, p->data.id, p->data.names, p->data.score);
		p = p->link;
	}

	printf("\n");
}

// �������� ���� ���� �Լ�(�Ű�����: ���Ḯ��Ʈ ���۰� ��, ���� ���)
ListNode * partition(ListNode *head, ListNode *tail, int key) {	
		
	ListNode *pivot = head;
	ListNode *value = head;	
	student tmp;	//swap�� ���� �ӽ� ���� ����

	// �̸��� ����
	if (key == 1) {
		while (value != NULL && value != tail) {
			if (strcmp(value->data.names, tail->data.names)==-1) {
				pivot = head;

				tmp = head->data;
				head->data = value->data;
				value->data = tmp;
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

		while (value != NULL && value != tail) {
			// �й� ������� ����
			if (key == 0) {
				if (value->data.id < tail->data.id) {
					pivot = head;

					tmp = head->data;
					head->data = value->data;
					value->data = tmp;
					head = head->link;
				}
			}
			// ���� ������� ����
			if (key == 2) {

				// value�� ������ �� �ڿ��ִ� ����� �������� ���ٸ�
				if (value->data.score > tail->data.score) {
					pivot = head;

					// pivot�� value�� ��ġ�� �ٲ��ش�.
					tmp = head->data;
					head->data = value->data;
					value->data = tmp;
					head = head->link;
				}
			}
			// value�� ������ tail�� �������� ���ٸ� ���� ��� �湮
			value = value->link;
		}

		//�� �� ��带 ���� ���� �ٲٱ�
		tmp = head->data;
		head->data = tail->data;
		tail->data = tmp;
		return pivot;
}
	

// ������ �Լ�
void qsort(ListNode * head, ListNode *tail, int key) {

	// ó���� ���� ���ٸ� �������� �ʰ� return;
	if (head == tail)
		return;

	//���� �Լ��� ȣ���Ͽ� pivot �ʱ�ȭ
	ListNode *pivot = partition(head, tail,key);

	// pivot�� ������� �ʰ�, pivot ���� ��嵵 ������� �ʴٸ�
	if (pivot != NULL && pivot->link != NULL) {
		qsort(pivot->link, tail,key);
	}

	// pivot�� ������� �ʰ�, head �� pivot�� �ƴ϶��
	if (pivot != NULL && head != pivot)
		qsort(head, pivot,key);
}