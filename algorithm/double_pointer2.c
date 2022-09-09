#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main() {

	FILE *fp;
	char **names;
	char buffer[100];	//입력을 위한 버퍼, 입력받는 이름의 최대길이는 99 바이트
	int cnt = 0;
	int size = 0;

	fp = fopen("station_data.txt", "r");
	
	// 문자열 개수 세기
	while (!feof(fp)) {
		fscanf(fp, "%s", buffer);
		cnt++;
	}

	names = (char**)malloc(sizeof(char*)*cnt);	
	rewind(fp); //파일의 시작위치로 이동

	for (int i = 0; i < cnt; i++) {
		fscanf(fp, "%s", buffer);
		size = strlen(buffer);
		names[i] = (char*)malloc(sizeof(char)*(size+1)); //마지막: \0
		strcpy(names[i], buffer); // 이름 복사
	}

	for (int i = 0; i < cnt; i++) {
		printf("%s\n", names[i]);
	}

	fclose(fp);

	for (int i = 0; i < cnt; i++) free(names[i]);
	free(names);

	return 0;

}