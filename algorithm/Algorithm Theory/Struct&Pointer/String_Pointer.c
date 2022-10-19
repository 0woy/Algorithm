/*
학번: 20204624
이름: 박윤아

프로그램 설명: 문자열과 포인터 다루기
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main() {

	char str1[9] = "Computer";
	char *str2 = "Computer";

	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);

	str2 = "Science";
	//str1 = "Science" 

	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);

	str1[0] = 'h';
	//str2[0] ='c	

	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);


}
