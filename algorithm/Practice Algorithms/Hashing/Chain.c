/*
프로그램 설명: 해싱을 이용하여 데이터 삽입/탐색/삭제 하기

작성일: 2022.12.02.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define KEY_SIZE 10
#define TABLE_SIZE 13

typedef struct {
	char key[KEY_SIZE];
}element;

struct list {
	element item;
	struct list *link;
};

struct list* hash_table[TABLE_SIZE];

void init_table(element ht[]) {

	for (int i = 0; i < TABLE_SIZE; i++)
		ht[i].key[0] = NULL;
}

// *char -> int
int transform(char *key) {

	int number = 0;
	while (*key)
		number = number + *key++;

	return number;
}

//제산 함수를 사용한 해시 함수
int hash_function(char *key) {

	return transform(key) % TABLE_SIZE;
}

#define empty(item) (strlen(item.key) ==0)
#define equal(item1, item2) (!strcmp(item1.key, item2.key))

//체인법을 이용해 해시테이블에 키 삽입
// 테이블이 가득 찬 경우 종료
void hash_chain_add(element item, struct list* ht[]) {

	int hash_value = hash_function(item.key);
	struct list* ptr;
	struct list* node_before = NULL, *node = ht[hash_value];
	
	for (; node; node_before = node, node = node->link) {
		if (node->item.key == item.key) {
			fprintf(stderr, "탐색키 중복\n");
			return;
		}
	}

	ptr = (struct list*)malloc(sizeof(struct list));
	ptr->item = item;
	ptr->link = NULL;

	if (node_before)
		node_before->link = ptr;
	else
		ht[hash_value] = ptr;
	printf("인덱스 %d번에 저장됨\n", hash_value);
}

// 체인법을 이용해 테이블에 저장된 키 탐색
void hash_chain_search(element item, struct list * ht[]) {
	struct list *node;

	int hash_value = hash_function(item.key);
	for (node = ht[hash_value]; node; node = node->link) {
		if (strcmp(node->item.key, item.key) ==0) {
			fprintf(stderr, "탐색 %s 성공\n", item.key);
			return;
		}
	}
	printf("키를 찾지 못함\n");
}
void hash_chain_print(struct list *ht[])
{
	struct list *node;
	int i;
	printf("\n===============================\n");
	for (i = 0; i < TABLE_SIZE; i++) {
		printf("[%d]->", i);
		for (node = ht[i]; node; node = node->link) {
			printf("%s->", node->item.key);
		}
		printf("\n");
	}
	printf("===============================\n");
}

int main() {

	element e;
	char cmd[100];
	char name[100];

	init_table(hash_table);

	while (1)
	{
		printf("input: i,s,q >>");
		scanf("%s", cmd);

		if (strcmp(cmd, "i") == 0) {
			printf("animal name?");
			scanf("%s", name);
			strcpy(e.key, name);
			hash_chain_add(e, hash_table);
		}
		else if (strcmp(cmd, "s") == 0) {
			printf("animal name?");
			scanf("%s", name);
			strcpy(e.key, name);
			hash_chain_search(e, hash_table);
		}
		else if (strcmp(cmd, "q") == 0)
			break;
	}

	hash_chain_print(hash_table);

	return 0;
}