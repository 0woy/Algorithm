/*
정렬 프로그램
파일에 학생의 정보가 이름, 학번, 등수 순서로 저장되어 있다.
이를 읽어와 정렬하여 출력.
- 각 정렬은 정해진 양식으로 구현
- 동적 할당을 이용하여 데이터 저장
- 모두 오름차순으로 정렬
- 수행시간을 검사하고 비교

작성일: 2022.11.18.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //이름을 비교할 때

#include<time.h> // 수행시간

typedef struct Student {
	char* name;
	int id;
	int grade;
}element;

void print(element list[], int n);
void selection_sort(element list[], int n);
void insertion_sort(element list[], int n);
void bubble_sort(element list[], int n);


double selection_time, insertion_time, bubble_time;

int main() {

	FILE *fp;		//파일을 읽어오기 위한 파일포인터 선언
	element tmp;	// 데이터를 임시로 저장하는 변수
	element *list;	// 데이터를 저장하는 배열
	char buffer[20]; // 이름 메모리 동적할당을 위한 이름 임시 공간
	int count = 0;	// 레코드 갯수(학생 수)

	fp = fopen("random_data.txt", "r");
	if (!fp) {	//파일을 읽어오는데 실패한 경우
		printf("CAN NOT OPEN FILE");	//에러메세지 출력
		return;	//종료
	}

	while (!feof(fp)){	//파일의 처음부터 끝까지
		fscanf(fp, "%s %d %d", buffer, &tmp.id, &tmp.grade); // 데이터를 읽고
		count++;	//데이터 개수 증가
	}

	list = (element*)malloc(sizeof(element)* count);	//데이터 개수만큼 동적할당
	rewind(fp);	//다시 파일을 처음부터 읽기 위해 rewind

	count = 0; //배열의 인덱스
	while (!feof(fp)) {
		fscanf(fp, "%s %d %d", buffer, &list[count].id, &list[count].grade);	//데이터를 읽어와 저장

		int len = strlen(buffer);		//읽어온 이름의 길이 저장 변수
		list[count].name = (char*)malloc(sizeof(char)*(len+1));	//읽어온 이름의 크기만큼 동적할당
		strcpy(list[count].name, buffer); // 이름을 복사해서 배열에 붙여 넣음

		count++; //인덱스 증가
	}

	printf("이름: 박윤아\n학번: 20204624\n제출일: 2022.11.24.\n\n");

	printf("데이터의 개수: %d\n", count);
//	printf("<정렬전>\n");
	printf("\n");

	printf("<선택 정렬- 등수순>\n");
	selection_sort(list, count);
	printf("수행시간: %lf\n\n", selection_time);

	printf("<삽입 정렬- 학번순>\n");
	insertion_sort(list, count);
	printf("수행시간: %lf\n\n", insertion_time);

	printf("<버블 정렬- 이름순>\n");
	bubble_sort(list, count);
	printf("수행시간: %lf\n\n", bubble_time);

	fclose(fp);
	free(list);

	return 0;
}

// 배열 상태 출력
void print(element list[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%s %d %d\n", list[i].name, list[i].id, list[i].grade);
	}
}

// 선택정렬을 사용한 성적순으로 정렬
void selection_sort(element list[], int n) {

	int min;
	element tmp;
	clock_t start, end; //수행시간을 계산하기 위한 변수
	 
	start = clock(); //시간 측정 시작
	for (int i = 0; i < n - 1; i++) {
		min = i;	//맨처음 인덱스를 min에 저장
		for (int j = i + 1; j < n; j++) {	//i의 앞 요소들은 크기순으로 정렬이 된 상태

			if (list[j].grade < list[min].grade) //만일 min 위치에 있는 성적보다 j위치에 있는 성적이 낮다면
				min = j;	//min에 j저장
		}

		// 가장 크기가 작은 요소를 맨 앞으로 가져옴
		tmp = list[i]; 
		list[i] = list[min];
		list[min] = tmp;
	}
	end = clock(); //시간 측정 종료
	selection_time = (double)(end - start) / CLOCKS_PER_SEC;
}

// 삽입 정렬을 이용한 학번순 정렬
void insertion_sort(element list[], int n) {
	element tmp;
	int j;

	clock_t start, end;

	start = clock();
	for (int i = 1; i < n; i++) {
		tmp = list[i];	// list[i]번째 요소 tmp에 저장

		for (j = i - 1; j >= 0 && list[j].id > tmp.id; j--) //j는 i번째 요소 앞부터, 0까지 만약 j의 학번이 tmp의 학번보다 크다면
			list[j + 1] = list[j];	//j번째 요소를 j+1번째 요소로 넣어 뒤로 밀기

		list[j + 1] = tmp;	//반복문을 빠져나온 후 j+1번째에 tmp 삽입.
	}
	end = clock();
	insertion_time = (double)(end - start) / CLOCKS_PER_SEC;
}

// 이름순
void bubble_sort(element list[], int n) {
	element tmp;
	int j;
	clock_t start, end;
	start = clock();

	for (int i = n-1; i >0 ; i--) { //맨 뒤에서부터 반복
		for (j = 0; j < i; j++) {	
			if (strcmp(list[j].name, list[j + 1].name) > 0) { //j번째의 이름이 j+1번째의 이름보다 사전적으로 뒤에 있다면

				// j와 j+1번째에 있는 data SWAP
				tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
		}
	}
	end = clock();

	bubble_time = (double)(end - start) / CLOCKS_PER_SEC;
}

