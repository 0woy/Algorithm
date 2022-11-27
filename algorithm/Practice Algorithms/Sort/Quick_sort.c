#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

// 함수 원형 선언
void print(int arr[], int left, int right);
void quick_sort(int arr[], int left, int right);
int partition(int arr[], int left, int right);


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
	rewind(fp); // 파일을 다시 처음부터 읽기 위해 rewind

	int i = 0; // data 배열의 인덱스
	while (!feof(fp)) {
		fscanf(fp, "%d", &data[i++]); //파일을 한 줄씩 읽으면서 배열에 저장
	}

	printf("이름: 박윤아\n학번: 20204624\n제출일: 2022.11.26.\n\n");

	printf("정렬 전\n");
	print(data, 0, count);  //정렬 전 데이터 출력

	quick_sort(data, 0, count - 1); // 퀵정렬 실행

	printf("정렬 후\n");
	print(data, 0, count); //정렬 후 데이터 출력


	free(data); // 동적 할당 해제
	fclose(fp); // 파일 닫기

	return 0;
}

//매개 변수로 받아온 배열 내부의 데이터 출력 함수
void print(int arr[], int left, int right) {
	printf("[");
	for (int i = left; i < right; i++) { //시작 인덱스 ~ 끝 인덱스까지 
		printf("%d > ", arr[i]);	//데이터 출력
	}
	printf("]\n");
}


//퀵 정렬
void quick_sort(int arr[], int left, int right) {

	if (left < right) {	//만일 데이터가 2개 이상이라면,
		int	p = partition(arr, left, right);	//partition 함수 호출, p 에 pivot의 인덱스 저장
		quick_sort(arr, left, p- 1);	//pivot 기준 왼쪽 배열 퀵정렬
		quick_sort(arr, p+ 1, right);	//pivot 기준 오른쪽 배열 퀵정렬
	}
}


// 실질적으로 정렬을 하는 함수
int partition(int arr[], int left, int right) {

	int pivot = arr[left]; // 배열의 제일 왼쪽 요소를 pivot으로 지정
	printf("\n-Pivot : %d -\n", pivot);


	int low, high, tmp;
	low = left;			// low에 left 저장
	high = right + 1;	// high에 right+1 저장

	do { // low와 high가 교차할 때까지 반복

		//배열에서 low에 위치한 데이터가 pivot보다 클 때까지 반복
		do {	
			low++; 
		} while (arr[low] < pivot && low <= right);


		//배열에서 high에 위치한 데이터가 pivot보다 작을 때까지 반복
		do {	
			high--;
		} while (arr[high] > pivot && high > left);

		printf("Low: %d High: %d\t", arr[low], arr[high]);
		print(arr, left, right + 1);	// 현재 배열 상태 출력

		//교차하지 않았다면
		if (low < high) { 
			printf("%d와 %d 스왑\n", arr[low], arr[high]);
			SWAP(arr[low], arr[high], tmp);	//low와 high에 위치한 데이터 SWAP
			print(arr, left, right + 1);	// SWAP 후 배열 상태 출력
			printf("\n");
		}
	} while (low < high);

	//low와 high가 교차한 후 
	SWAP(arr[left], arr[high], tmp);  //pivot과 교차된 high에 있는 원소를 교환
	printf("\n");
	return high;	//pivot의 인덱스 반환

}
