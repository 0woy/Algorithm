/*
���α׷� ����: �ؽ��� �̿��Ͽ� ������ ����/Ž��/���� �ϱ�

�ۼ���: 2022.12.02.
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

//���� �Լ��� ����� �ؽ� �Լ�
int hash_function(char *key) {

	return transform(key) % TABLE_SIZE;
}

#define empty(item) (strlen(item.key) ==0)
#define equal(item1, item2) (!strcmp(item1.key, item2.key))

//���� ������� �̿��Ͽ� ���̺� Ű ����,
// ���̺��� ���� �� ��� ����
void hash_qp_add(element item, element ht[])
{
	int i, hash_value, inc = 0;
	hash_value = i = hash_function(item.key);
	//printf("hash_address=%d\n", i);
	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "Ž��Ű�� �ߺ��Ǿ����ϴ�\n");
			exit(1);
		}
		i = (hash_value + inc * inc) % TABLE_SIZE;
		inc = inc + 1;
		if (i == hash_value) {
			fprintf(stderr, "���̺��� ����á���ϴ�\n");
			exit(1);
		}
	}
	ht[i] = item;
	printf("�ε��� %d���� �����\n", i);
}

// ����������� �̿��� ���̺� ����� Ű Ž��
void hash_lp_search(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			printf("Ž�� %s ��ġ  = %d\n", item.key, i);
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {
			printf("ã�� ���� ���̺� ����");
			return;
		}
	}
	printf("ã�� ���� ���̺� ����\n");
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