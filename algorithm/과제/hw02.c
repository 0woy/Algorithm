#define _CRT_SECURE_NO_WARNINGS //scanf_s 오류 발생하지 않도록 설정

// 필요한 헤더파일 추가
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
	struct ListNode *link;	//노드들을 연결하는 link
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
	ListNode *head = NULL; // 연결리스트의 시작 노드(head)
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

	// 파일에서 읽어온 상태 출력
	display(head,-1);
	
	// i값을 key로 넘겨 정렬 상태를 바꿈
	for (int i = 0; i < 3; i++) {
		
		qsort(head, tail, i);
		display(head,i);
	}
	
	free(head);	//동적메모리 할당 해제
	fclose(fp);

}


void insert_node(ListNode **head, ListNode *pre, ListNode *new_node) {

	// 연결 리스트에 처음으로 노드가 삽입될 때
	if (*head == NULL) {
		*head = new_node;	
		pre = *head;
		tail = *head;
	}
	
	// 이미 연결리스트에 노드가 있을 때
	else
	{
		ListNode *temp;	 // head의 값을 임시로 저장하는 temp
		temp = *head;
		while (temp->link != NULL) {
			temp = temp->link; //비어있는 노드(NULL)를 찾아감(맨 마지막 노드)
		}

		// 비어있는 노드에 새로운 노드 삽입
		temp->link = new_node;

		// 맨 마지막 노드 = 추가된 노드
		tail = new_node;

	}

}

// 입력 받은 정보를 토대로 노드 생성 함수
ListNode *create_node(student data, ListNode *link) {

	//매개변수로 student data를 받아서 temp 노드에 저장후 temp 반환.
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

// 퀵정렬을 위한 분할 함수(매개변수: 연결리스트 시작과 끝, 정렬 방식)
ListNode * partition(ListNode *head, ListNode *tail, int key) {	
		
	ListNode *pivot = head;
	ListNode *value = head;	
	student tmp;	//swap을 위한 임시 저장 변수

	// 이름순 정렬
	if (key == 1) {
		while (value != NULL && value != tail) {
			if (strcmp(value->data.names, tail->data.names)==-1) {
				pivot = head;

				tmp = head->data;
				head->data = value->data;
				value->data = tmp;
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
			// 학번 순서대로 정렬
			if (key == 0) {
				if (value->data.id < tail->data.id) {
					pivot = head;

					tmp = head->data;
					head->data = value->data;
					value->data = tmp;
					head = head->link;
				}
			}
			// 성적 순서대로 정렬
			if (key == 2) {

				// value의 성적이 맨 뒤에있는 노드의 성적보다 높다면
				if (value->data.score > tail->data.score) {
					pivot = head;

					// pivot과 value의 위치를 바꿔준다.
					tmp = head->data;
					head->data = value->data;
					value->data = tmp;
					head = head->link;
				}
			}
			// value의 성적이 tail의 성적보다 낮다면 다음 노드 방문
			value = value->link;
		}

		//맨 뒤 노드를 현재 노드로 바꾸기
		tmp = head->data;
		head->data = tail->data;
		tail->data = tmp;
		return pivot;
}
	

// 퀵정렬 함수
void qsort(ListNode * head, ListNode *tail, int key) {

	// 처음과 끝이 같다면 정렬하지 않고 return;
	if (head == tail)
		return;

	//분할 함수를 호출하여 pivot 초기화
	ListNode *pivot = partition(head, tail,key);

	// pivot이 비어있지 않고, pivot 다음 노드도 비어있지 않다면
	if (pivot != NULL && pivot->link != NULL) {
		qsort(pivot->link, tail,key);
	}

	// pivot이 비어있지 않고, head 가 pivot이 아니라면
	if (pivot != NULL && head != pivot)
		qsort(head, pivot,key);
}
