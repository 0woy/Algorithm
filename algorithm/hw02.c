#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// 학생의 정보를 저장한 student 구조체
typedef struct student {
	int id;
	char *names;
	int score;
}student;


// 학생들의 정보를 연결리스트로 저장하기위한 LisNode 구조체
typedef struct ListNode {
	student data;
	struct ListNode *link;
}ListNode;


void insert_node(ListNode **head, ListNode *pre, ListNode *new_node);	//노드 삽입
ListNode *create_node(student data, ListNode *link);	//노드 생성
void display(ListNode *head);	// 연결리스트 출력
void  qsort(ListNode *head, ListNode *tail);	// 연결리스트 퀵정렬
ListNode * partition(ListNode *head, ListNode *tail);	// 퀵정렬시 사용되는 분할 함수

ListNode *tail=NULL;

int main() {
	FILE *fp;
	char buffer[30];	// 이름을 임시로 받아둘 공간
	ListNode *head = NULL;
	student temp;	// 파일의 data를 임시 저장하는 구조체

	int size = 0; // 동적할당을 위한 이름 길이
	int cnt = 0; // 학생 수

	fp = fopen("data.txt", "r");

	// 파일이 NULL이라면 메세지 출력 후 종료
	if (fp == NULL) {
		printf("파일을 읽을 수 없습니다.");
		exit(1);
	}


	while (!feof(fp)) {
		//파일에서 이름을 제외한 학생 정보를 한 줄 씩 읽어와 temp에 저장
		fscanf(fp, "%d %s %d", &temp.id, buffer, &temp.score);	
		size = strlen(buffer);	

		// size를 이용해 temp.names의 메모리를 동적할당.
		temp.names = (char*)malloc(sizeof(char)*(size + 1));
		strcpy(temp.names, buffer);

		//연결리스트에 tmp 추가
		insert_node(&head, NULL, create_node(temp, NULL));
		//cnt++;
	}


	display(head,-1);
	
	for (int i = 0; i < 3; i++) {
		
		qsort(head, tail, i);
		display(head,i);
	}
	

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

	//매개변수로 studata를 받아서 temp 노드에 저장후 tmp 반환.
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
		printf("ㅡㅡㅡ 파일 보기 ㅡㅡㅡ\n");
		break;
	case 0:
		printf("ㅡㅡㅡ학번 순으로 정렬 ㅡㅡㅡ\n");
		break;
	case 1:
		printf("ㅡㅡㅡ이름 순으로 정렬ㅡㅡㅡ\n");
		break;
	case 2:
		printf("ㅡㅡㅡ점수 순으로 정렬ㅡㅡㅡ\n");
		break;
	default:
		break;
	}
	while (p != NULL)
	{
		printf("%d번: %3d %3s %3d \n",++i, p->data.id, p->data.names, p->data.score);
		p = p->link;
	}

	printf("\n");
}

// 분할
ListNode * partition(ListNode *head, ListNode *tail, int key) {	// 처음, 끝
		
	ListNode *pivot = head;
	ListNode *value = head;
	student tmp;

	// 이름순 정렬
	if (key == 1) {
		while (value != NULL && value != tail) {
			if (strcmp(value->data.names, tail->data.names)==-1) {
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

	
		while (value != NULL && value != tail) {
			if (key == 0) {
				if (value->data.id < tail->data.id) {
					pivot = head;

					tmp = head->data;
					head->data = value->data;
					value->data = tmp;
					//swap(head, value);
					head = head->link;
				}
			}
			if (key == 2) {
				if (value->data.score > tail->data.score) {
					pivot = head;

					tmp = head->data;
					head->data = value->data;
					value->data = tmp;
					//swap(head, value);
					head = head->link;
				}
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