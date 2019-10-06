#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int select(int **a, int first, int last) {
	if (a[first][last] == 1) { // 앞이 뒤를 알고있으므로, 뒤가 셀럽 후보
		return last;
	}
	else { // 앞이 뒤를 모르면 앞이 셀럽 후보
		return first;
	}
}


int find_celebrity(int **a, int first, int last) {
	int left_candidate, right_candidate, middle;
	if (last - first == 1) {
		return (select(a, first, last));
	}
	if (last - first == 0) {
		return last; // 비교대상이 없는 경우 부전승
	}

	middle = (first + last) / 2;
	left_candidate = find_celebrity(a, first, middle); // 왼쪽 부분에서 찾아나간다
	right_candidate = find_celebrity(a, middle + 1, last); // 오른쪽 부분에서 찾아나간다

	return (select(a, left_candidate, right_candidate)); // 두 최종 후보를 검증해본다
}


int main() {

	int arraySize;
	printf("Input Number of People : ");
	scanf("%d", &arraySize);
	int first = 0, last = arraySize - 1;	// 추가한 부분
	int **arr;
	arr = (int**)malloc(sizeof(int*)*arraySize);
	for (int i = 0; i < arraySize; i++) {
		arr[i] = (int*)malloc(sizeof(int)*arraySize);
	}

	
	srand(time(NULL));
	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize; j++)
		{
			if (i == j)
			{
				arr[i][j] = 0;   // 자기 자신
				continue;
			}
			arr[i][j] = rand() % 2;
		}
	}
	for (int i = 0; i < arraySize; i++)
	{
		printf("%d번쨰 : ", i);
		for (int j = 0; j < arraySize; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	int celeb = find_celebrity(arr, first, last); // possible celeb
	printf("셀럽 가능성이 있는 사람 : %d\n", celeb);

	for (int i = 0; i < arraySize; i++) { // check if everyone knows king and king does not know everyone.
		if (i != celeb) { // if not king himself
			if ((select(arr, celeb, i) != celeb) || (select(arr, i, celeb) != celeb)) {
				// king knows someone, or someone does not know king
				printf("No Celebrity in the list\n");
				return 0;
			}
		}
	}

	printf("Celebirity is %d\n", celeb);
	return 0;

}