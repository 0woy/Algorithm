/*
충돌을 해결하는 방법: 개방주소법, 체이닝
개방주소법의 종류: 선형조사법, 이차조사법, 이중해싱법, 임의조사법 등

- 선형조사법: 충돌이 ht[k]에서 발생했다면, ht[k+1]이 비어있는지 살펴봄

프로그램설명: 선형조사법 프로그램 작성
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define KEY_SIZE 10		// Max length of search KEY
#define TABLE_SIZE 13	// The size of hash table = prime number

//These two functions depend on the type of data stored
#define empty(item) (strlen(item.key)==0) //Check if the current bucket is empty
#define equel(item1, item2) (!strcmp(item1.key, item2.key))	 //Check that two items are the same


typedef struct {
	char key[KEY_SIZE];
	//add another fields

}element;

element hash_table[TABLE_SIZE]; //hash table

// init ht : Make the buckets NULL
void init_table(element ht[]) {

	for (int i = 0; i < TABLE_SIZE; i++) {
		ht[i].key[0] = NULL;  //In this Program, keys are string. if key's first char is NULL, bucket is empty  
	}
}

// Transform key to number 
int str_to_int(char *key) {
	int number = 0;

	while (*key) 
		number = 31 * number + *key++;
	
	return number;
}

//Hashing func using division Func
int hash_func(char *key) {

	// transform keys to numbers, divide by TABLE_SIZE and return the rest
	return str_to_int(key) % TABLE_SIZE;
}

//

