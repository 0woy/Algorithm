#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

int *sorted;// 추가 공간이 필요

//매개 변수로 받아온 배열 내부의 데이터 출력 함수
void print(int arr[], int left, int right) {
	printf("[");
	for (int i = left; i < right; i++) { //시작 인덱스 ~ 끝 인덱스까지 
		printf("%d > ", arr[i]);	//데이터 출력
	}
	printf("]\n");
}

void merge(int list[], int left, int mid, int right);
void merge_sort(int list[], int left, int right);

int main() {

	FILE *fp; //데이터 파일을 읽어오기 위한 파일 포인터 선언

	fp = fopen("Quick_data.txt", "r");

	int tmp;	//데이터를 임시로 저장하는 변수
	int count = 0; //데이터의 개수
	int *data; //데이터를 저장할 배열

	if (!fp) { //파일을 읽어오는데 실패한 경우
		printf("CAN NOT OPEN FILE"); //에러메세지 출력
		return 0; //return
	}

	while (!feof(fp)) {			//파일의 끝까지
		fscanf(fp, "%d", &tmp); //데이터를 읽고
		count++;				//데이터 개수 세기
	}

	data = (int*)malloc(sizeof(int)*count); //데이터 개수만큼 동적할당
	sorted = (int*)malloc(sizeof(int)*count);
	rewind(fp); // 파일을 다시 처음부터 읽기 위해 rewind

	int i = 0; // data 배열의 인덱스
	while (!feof(fp)) {
		fscanf(fp, "%d", &data[i++]); //파일을 한 줄씩 읽으면서 배열에 저장
	}

	printf("이름: 박윤아\n학번: 20204624\n제출일: 2022.11.26.\n\n");

	printf("정렬 전\n");
	print(data, 0, count);  //정렬 전 데이터 출력

	merge_sort(data, 0, count - 1); // 퀵정렬 실행

	printf("정렬 후\n");
	print(data, 0, count); //정렬 후 데이터 출력


	free(data); // 동적 할당 해제
	free(sorted);
	fclose(fp); // 파일 닫기

	return 0;
}


/* i는 정렬된 왼쪽 리스트에 대한 인덱스
		j는 정렬된 오른쪽 리스트에 대한 인덱스
		k는 정렬될 리스트에 대한 인덱스 */
void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left;  j = mid + 1;  k = left;
	printf("left: %d, mid: %d, right: %d\n", list[left], list[mid],list[right]);

	/* 분할 정렬된 list의 합병 */
	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i > mid)	/* 남아 있는 레코드의 일괄 복사 */
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else	/* 남아 있는 레코드의 일괄 복사 */
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	/* 배열 sorted[]의 리스트를 배열 list[]로 재복사 */
	for (l = left; l <= right; l++)
		list[l] = sorted[l];

//	print(list, left, right+1);
	
}


void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2;     /* 리스트의 균등 분할 */
		merge_sort(list, left, mid);    /* 부분 리스트 정렬 */
		merge_sort(list, mid + 1, right); /* 부분 리스트 정렬 */
		merge(list, left, mid, right);    /* 합병 */
	//	print(list, left, right);
	}
}