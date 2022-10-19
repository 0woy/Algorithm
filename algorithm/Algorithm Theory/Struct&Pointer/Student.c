/*
학번: 20204624
이름: 박윤아

프로그램 설명: 파일에서 학생 데이터(이름, 나이, 학번, 키)를 읽어와 출력
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
typedef struct student_info
{
	int id;
	char *name;
	int age;
	float height;

}student;

int main() {
	FILE *fp;
	student *std_info, temp;
	char buffer[30]; //학생 이름을 저장할 임시 버퍼
	int cnt = 0;
	int size = 0;

	fp = fopen("student.txt", "r");

	while (!feof(fp))
	{
		fscanf(fp, "%d%s%d%f", &temp.id,buffer,&temp.age,&temp.height);
		cnt++;
	}

	std_info = (student*)malloc(sizeof(student) * cnt);
	rewind(fp);

	for (int i = 0; i < cnt; i++) {
		fscanf(fp, "%d%s%d%f", &std_info[i].id, buffer, &std_info[i].age, &std_info[i].height);
		size = strlen(buffer);
		std_info[i].name = (char*)malloc(sizeof(char)*(size + 1));
		strcpy(std_info[i].name, buffer);
	}
	fclose(fp);

	for (int i = 0; i < cnt; i++) {
		printf("%d %s %d %.1f\n", std_info[i].id, std_info[i].name, std_info[i].age, std_info[i].height);
	}


	for (int i = 0; i < cnt; i++) {
		free(std_info[i].name);
	}
	free(std_info);
}
