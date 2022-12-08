#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define STU_CNT 25000
#define FIRST_NAME 41
#define LAST_NAME 71

typedef struct Student {
	char sname[10];
	int grade;
	int id;
}STU;

int main() {
	STU stu[STU_CNT];
	int i, j, t_first, t_last;

	char first[FIRST_NAME] = "���̹��������ѽ��������۰��������Ȳ�ּ�";
	char last[LAST_NAME] = "�ΰ浵��������ưǿ�����ȣ�ּ��������󿹿��켭�ؼ��ִ̾���������������";

	char sname[10] = "", word[3] = "";

	FILE *fp = fopen("random_data.txt", "wt");
	if (fp == NULL) return 1;

	srand(time(NULL));

	for (int i = 0; i < STU_CNT; i++) {

		//char �迭 �ʱ�ȭ
		strcpy(stu[i].sname, "");

		printf("i %d name %s ", i + 1, stu[i].sname);

		//�� 
		t_first = rand() % (FIRST_NAME - 2);
		if ((t_first <= (FIRST_NAME - 3)) && (t_first % 2 == 1)) t_first++;
		strncpy(word, &first[t_first], 2);
		strcat(stu[i].sname, word);
		printf("t_f %d f %s ", t_first, stu[i].sname);
		//printf("%d %c%c", t_first, first[t_first], first[t_first+1]);

		//�̸� 
		for (j = 0; j <= 1; j++) {
			t_last = rand() % (LAST_NAME - 2);
			if ((t_last <= (LAST_NAME - 3)) && (t_last % 2 == 1)) t_last++;
			//strncpy(word, &last[t_last], 2);
			//strcat(stu[i].sname, word);
			strncat(stu[i].sname, &last[t_last], 2);
			//printf("t_l %d %s ", t_last, word);
		}
		printf("%s ", stu[i].sname);

		stu[i].grade = (int)rand() % 25000 +1;	 //����(0~100, �Ǽ�)
		stu[i].id = (int)rand()%20230000;
		fprintf(fp, "%s %d %d\n",  stu[i].sname,  stu[i].id, stu[i].grade);
	}

	fclose(fp);
	return 0;
}