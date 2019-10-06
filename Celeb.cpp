#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int select(int **a, int first, int last) {
	if (a[first][last] == 1) { // ���� �ڸ� �˰������Ƿ�, �ڰ� ���� �ĺ�
		return last;
	}
	else { // ���� �ڸ� �𸣸� ���� ���� �ĺ�
		return first;
	}
}


int find_celebrity(int **a, int first, int last) {
	int left_candidate, right_candidate, middle;
	if (last - first == 1) {
		return (select(a, first, last));
	}
	if (last - first == 0) {
		return last; // �񱳴���� ���� ��� ������
	}

	middle = (first + last) / 2;
	left_candidate = find_celebrity(a, first, middle); // ���� �κп��� ã�Ƴ�����
	right_candidate = find_celebrity(a, middle + 1, last); // ������ �κп��� ã�Ƴ�����

	return (select(a, left_candidate, right_candidate)); // �� ���� �ĺ��� �����غ���
}


int main() {

	int arraySize;
	printf("Input Number of People : ");
	scanf("%d", &arraySize);
	int first = 0, last = arraySize - 1;	// �߰��� �κ�
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
				arr[i][j] = 0;   // �ڱ� �ڽ�
				continue;
			}
			arr[i][j] = rand() % 2;
		}
	}
	for (int i = 0; i < arraySize; i++)
	{
		printf("%d���� : ", i);
		for (int j = 0; j < arraySize; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	int celeb = find_celebrity(arr, first, last); // possible celeb
	printf("���� ���ɼ��� �ִ� ��� : %d\n", celeb);

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