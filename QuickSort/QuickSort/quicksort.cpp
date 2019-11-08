#include <stdio.h>

// �� ��Ʈ - �߰��� ����Ʈ
// �迭�� ��� ��Ҹ� �ǹ����� ��Ƽ� ����Ʈ�� ����.

/*
	�ʿ��� �Լ�
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
	// �迭�� �߰����� ��´�.
	int mid = arr[(s+e)/2];
	// s �����Ϳ� e �����Ͱ� �����ų� ����ĥ������ s++ e--�� �Ѵ�.
	// arr[s] > mid �̸� stop
	// arr[e] < mid �̸� stop
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
	// ���ȣ��
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

	// ������ �� : �ߺ� ���� ������ �۵��� �� ��.
	// 3 9 3 1 5 0 1 6 8 2  ->  0 1 1 2 3 3 5 6 8 9
	// 3 9 4 1 5 0 1 6 8 2  ->  0 2 1 1 3 4 5 6 8 9
	// { 3,9,4,11,5,0,10,6,8,2 } -> 0 2 3 4 5 11 6 10 8 9
	// s++ �� �ּ�ó�� �ϴϱ� ���� �۵��Ѵ�. -> why?
	//

}