#include<stdio.h>

void main() {

	char str1[9] = "Computer";
	char *str2 = "Computer";

	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);

	str2 = "Science";
	//str1 = "Science" //변경 불가능

	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);

	str1[0] = 'h';
	//str2[0] ='c	// 변경 불가능

	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);


}