#include <stdio.h>

// 퀵 소트 - 중간값 퀵소트
// 배열의 가운데 요소를 피벗으로 삼아서 퀵소트를 진행.

/*
	필요한 함수
	1. swap
	2. quicksort
	3. partition
*/

void printArray(int* p, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", p[i]);
	}
	printf("\n");
}

void swap(int* arr, int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

int partition(int* arr, int s, int e) {
	// 배열의 중간값을 잡는다.
	int mid = arr[(s+e)/2];
	// s 포인터와 e 포인터가 만나거나 지나칠때까지 s++ e--를 한다.
	// arr[s] > mid 이면 stop
	// arr[e] < mid 이면 stop
	// swap( arr[s] arr[e] );
	while (s <= e) {
		while (arr[s] < mid) {
			s++;
		}
		while (arr[e] > mid) {
			e--;
		}
		if (s <= e) {
			swap(arr, s, e);
			//s++;
			e--;
		}

	}
	//
	return s;

}


void quicksort(int* arr, int s, int e) {
	if (s >= e) {
		return;
	}
	

	int pivot = partition(arr, s, e);
	printArray(arr, 10);
	printf("p = %d\n", pivot);
	// 재귀호출
	if (s < pivot - 1 ) {
		quicksort(arr, s, pivot -1 );
	}
	if (pivot + 1 < e) {
		quicksort(arr, pivot + 1, e);
	}
	
}



void main() {
	//int arr[10] = { 3,9,4,7,5,0,1,6,8,2 };
	//int arr[10] = { 3,9,4,11,5,0,10,6,8,2 };
	int arr[10] = { 3,9,4,1,5,0,1,6,8,2 };
	int size = sizeof(arr) / sizeof(int);
	printArray(arr, size);

	quicksort(arr, 0, 9);
	printf("=====\n");
	printArray(arr, size);

	// 개선할 점 : 중복 값이 들어오면 작동을 안 함.
	// 3 9 3 1 5 0 1 6 8 2  ->  0 1 1 2 3 3 5 6 8 9
	// 3 9 4 1 5 0 1 6 8 2  ->  0 2 1 1 3 4 5 6 8 9
	// { 3,9,4,11,5,0,10,6,8,2 } -> 0 2 3 4 5 11 6 10 8 9
	// s++ 를 주석처리 하니까 정상 작동한다. -> why?
	//

}