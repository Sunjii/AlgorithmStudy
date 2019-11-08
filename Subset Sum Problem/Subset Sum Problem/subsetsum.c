#include <stdio.h>


void main() {
	int A[5] = { 2, 3, 7, 8, 10 };	// Set
	int B[5] = { 0 };	// Solution Set
	int count = 0;	
	int target = 11;	// Target number

	int table[5][12];
	for (int i = 0; i < 5; i++) {
		table[i][0] = 0; // false
	}

	// base case
	for (int j = 0; j < 11 + 1; j++) {
		if (A[0] == j) {
			table[0][j] = 1;	// T
		}
		else {
			table[0][j] = 0;	// F
		}
	}

	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 11 + 1; j++) {
			if (j < A[i]) {	// 윗 행의 요소를 복사
				table[i][j] = table[i - 1][j];
			}
			else if (j == A[i]) {	// 무조건 True인 경우
				table[i][j] = 1;
			}
			else {	// 이제부터 윗 행과 비교를 해야한다.
				if (table[i - 1][j] == 1) {	// 윗행이 T 이면 아래행도 T
					table[i][j] = 1;
				}
				else {	// 윗 행이 F면, 윗 행에서 -A[i] 만큼 뺀 열의 요소를 가져온다.
					table[i][j] = table[i - 1][j - A[i]];
				}
			}
		}
	}

	// 출력용
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 12; j++) {
			printf("%d ", table[i][j]);
		}
		printf("\n");
	}

	if (table[4][11] == 1) {
		printf("가능\n");
	}
	else {
		printf("불가능\n");
	}


	for (int i = 4; i >= 0; i--) {
		for (int j = 11; j >= 0; j--) {
			if (table[i - 1][j] == 1) {	// 윗 행이 T 이면 윗 행의 요소를 가져온 것이다.
				B[count] = A[i - 1];
				count++;
				j = j - A[i];	// 열을 땅기고
				i--;	// 행은 한 줄 올린다.
				break;
			}
			else {
			}
		}
	}

	printf("해집합 : ");
	for (int i = 0; i < count; i++) {
		printf("%d ", B[i]);
	}



}
