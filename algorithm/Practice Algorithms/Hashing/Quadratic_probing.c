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

element hash_table[TABLE_SIZE];

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

//선형 조삽버을 이용하여 테이블에 키 삽입,
// 테이블이 가득 찬 경우 종료
void hash_qp_add(element item, element ht[])
{
	int i, hash_value, inc = 0;
	hash_value = i = hash_function(item.key);
	//printf("hash_address=%d\n", i);
	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "탐색키가 중복되었습니다\n");
			exit(1);
		}
		i = (hash_value + inc * inc) % TABLE_SIZE;
		inc = inc + 1;
		if (i == hash_value) {
			fprintf(stderr, "테이블이 가득찼습니다\n");
			exit(1);
		}
	}
	ht[i] = item;
	printf("인덱스 %d번에 저장됨\n", i);
}

// 선형조사법을 이용해 테이블에 저장된 키 탐색
void hash_lp_search(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			printf("탐색 %s 위치  = %d\n", item.key, i);
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {
			printf("찾는 값이 테이블에 없음");
			return;
		}
	}
	printf("찾는 값이 테이블에 없음\n");
}
void hash_lp_print(element ht[]) {

	printf("\n==================================\n");
	for (int i = 0; i < TABLE_SIZE; i++)
		printf("[%d]	%s\n", i, ht[i].key);
	printf("\n==================================\n");
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
			hash_qp_add(e, hash_table);
		}
		else if (strcmp(cmd, "s") == 0) {
			printf("animal name?");
			scanf("%s", name);
			strcpy(e.key, name);
			hash_lp_search(e, hash_table);
		}
		else if (strcmp(cmd, "q") == 0)
			break;
	}

	hash_lp_print(hash_table);

	return 0;
}