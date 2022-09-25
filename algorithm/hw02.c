#define _CRT_SECURE_NO_WARNINGS //scanf_s ?�류 발생?��? ?�도�??�정

// ?�요???�더?�일 추�?
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

// ?�생???�보�??�?�한 student 구조�?
typedef struct student {
	int id;
	char *names;
	int score;
}student;


// ?�생?�의 ?�보�??�결리스?�로 ?�?�하기위??LisNode 구조�?
typedef struct ListNode {
	student data;
	struct ListNode *link;	//?�드?�을 ?�결?�는 link
}ListNode;


void insert_node(ListNode **head, ListNode *pre, ListNode *new_node);	//?�드 ?�입
ListNode *create_node(student data, ListNode *link);	//?�드 ?�성
void display(ListNode *head);	// ?�결리스??출력
void  qsort(ListNode *head, ListNode *tail);	// ?�결리스???�정??
ListNode * partition(ListNode *head, ListNode *tail);	// ?�정?�시 ?�용?�는 분할 ?�수

ListNode *tail=NULL;

int main() {

	SetConsoleOutputCP(65001);
	FILE *fp;
	char buffer[30];	// ?�름???�시�?받아??공간
	ListNode *head = NULL; // ?�결리스?�의 ?�작 ?�드(head)
	student temp;	// ?�일??data�??�시 ?�?�하??구조�?

	int size = 0; // ?�적?�당???�한 ?�름 길이
	int cnt = 0; // ?�생 ??

	fp = fopen("data.txt", "r");

	// ?�일??NULL?�라�?메세지 출력 ??종료
	if (fp == NULL) {
		printf("?�일???�을 ???�습?�다.");
		exit(1);
	}


	while (!feof(fp)) {
		//?�일?�서 ?�름???�외???�생 ?�보�???�????�어?� temp???�??
		fscanf(fp, "%d %s %d", &temp.id, buffer, &temp.score);	
		size = strlen(buffer);	

		// size�??�용??temp.names??메모리�? ?�적?�당.
		temp.names = (char*)malloc(sizeof(char)*(size + 1));
		strcpy(temp.names, buffer);

		//?�결리스?�에 tmp 추�?
		insert_node(&head, NULL, create_node(temp, NULL));
		//cnt++;
	}

	// ?�일?�서 ?�어???�태 출력
	display(head,-1);
	
	// i값을 key�??�겨 ?�렬 ?�태�?바꿈
	for (int i = 0; i < 3; i++) {
		
		qsort(head, tail, i);
		display(head,i);
	}
	
	free(head);	//?�적메모�??�당 ?�제
	fclose(fp);

}


void insert_node(ListNode **head, ListNode *pre, ListNode *new_node) {

	// ?�결 리스?�에 처음?�로 ?�드가 ?�입????
	if (*head == NULL) {
		*head = new_node;	
		pre = *head;
		tail = *head;
	}
	
	// ?��? ?�결리스?�에 ?�드가 ?�을 ??
	else
	{
		ListNode *temp;	 // head??값을 ?�시�??�?�하??temp
		temp = *head;
		while (temp->link != NULL) {
			temp = temp->link; //비어?�는 ?�드(NULL)�?찾아�?�?마�?�??�드)
		}

		// 비어?�는 ?�드???�로???�드 ?�입
		temp->link = new_node;

		// �?마�?�??�드 = 추�????�드
		tail = new_node;

	}

}

// ?�력 받�? ?�보�??��?�??�드 ?�성 ?�수
ListNode *create_node(student data, ListNode *link) {

	//매개변?�로 student data�?받아??temp ?�드???�?�후 temp 반환.
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
		printf("?�ㅡ???�일 보기 ?�ㅡ??n");
		break;
	case 0:
		printf("?�ㅡ?�학�??�으�??�렬 ?�ㅡ??n");
		break;
	case 1:
		printf("?�ㅡ?�이�??�으�??�렬?�ㅡ??n");
		break;
	case 2:
		printf("?�ㅡ?�점???�으�??�렬?�ㅡ??n");
		break;
	default:
		break;
	}
	while (p != NULL)
	{
		printf("%d�? %3d %3s %3d \n",++i, p->data.id, p->data.names, p->data.score);
		p = p->link;
	}

	printf("\n");
}

// ?�정?�을 ?�한 분할 ?�수(매개변?? ?�결리스???�작�??? ?�렬 방식)
ListNode * partition(ListNode *head, ListNode *tail, int key) {	
		
	ListNode *pivot = head;
	ListNode *value = head;	
	student tmp;	//swap???�한 ?�시 ?�??변??

	// ?�름???�렬
	if (key == 1) {
		while (value != NULL && value != tail) {
			if (strcmp(value->data.names, tail->data.names)==-1) {
				pivot = head;

				tmp = head->data;
				head->data = value->data;
				value->data = tmp;
				head = head->link;
			}
			// ?�음 ?�드 방문
			value = value->link;
		}

		//�????�드�??�재 ?�드�?바꾸�?
		tmp = head->data;
		head->data = tail->data;
		tail->data = tmp;
		return pivot;
	}

		while (value != NULL && value != tail) {
			// ?�번 ?�서?��??�렬
			if (key == 0) {
				if (value->data.id < tail->data.id) {
					pivot = head;

					tmp = head->data;
					head->data = value->data;
					value->data = tmp;
					head = head->link;
				}
			}
			// ?�적 ?�서?��??�렬
			if (key == 2) {

				// value???�적??�??�에?�는 ?�드???�적보다 ?�다�?
				if (value->data.score > tail->data.score) {
					pivot = head;

					// pivot�?value???�치�?바꿔준??
					tmp = head->data;
					head->data = value->data;
					value->data = tmp;
					head = head->link;
				}
			}
			// value???�적??tail???�적보다 ??���??�음 ?�드 방문
			value = value->link;
		}

		//�????�드�??�재 ?�드�?바꾸�?
		tmp = head->data;
		head->data = tail->data;
		tail->data = tmp;
		return pivot;
}
	

// ?�정???�수
void qsort(ListNode * head, ListNode *tail, int key) {

	// 처음�??�이 같다�??�렬?��? ?�고 return;
	if (head == tail)
		return;

	//분할 ?�수�??�출?�여 pivot 초기??
	ListNode *pivot = partition(head, tail,key);

	// pivot??비어?��? ?�고, pivot ?�음 ?�드??비어?��? ?�다�?
	if (pivot != NULL && pivot->link != NULL) {
		qsort(pivot->link, tail,key);
	}

	// pivot??비어?��? ?�고, head 가 pivot???�니?�면
	if (pivot != NULL && head != pivot)
		qsort(head, pivot,key);
}
