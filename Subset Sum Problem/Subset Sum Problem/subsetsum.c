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
			if (j < A[i]) {	// �� ���� ��Ҹ� ����
				table[i][j] = table[i - 1][j];
			}
			else if (j == A[i]) {	// ������ True�� ���
				table[i][j] = 1;
			}
			else {	// �������� �� ��� �񱳸� �ؾ��Ѵ�.
				if (table[i - 1][j] == 1) {	// ������ T �̸� �Ʒ��൵ T
					table[i][j] = 1;
				}
				else {	// �� ���� F��, �� �࿡�� -A[i] ��ŭ �� ���� ��Ҹ� �����´�.
					table[i][j] = table[i - 1][j - A[i]];
				}
			}
		}
	}

	// ��¿�
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 12; j++) {
			printf("%d ", table[i][j]);
		}
		printf("\n");
	}

	if (table[4][11] == 1) {
		printf("����\n");
	}
	else {
		printf("�Ұ���\n");
	}


	for (int i = 4; i >= 0; i--) {
		for (int j = 11; j >= 0; j--) {
			if (table[i - 1][j] == 1) {	// �� ���� T �̸� �� ���� ��Ҹ� ������ ���̴�.
				B[count] = A[i - 1];
				count++;
				j = j - A[i];	// ���� �����
				i--;	// ���� �� �� �ø���.
				break;
			}
			else {
			}
		}
	}

	printf("������ : ");
	for (int i = 0; i < count; i++) {
		printf("%d ", B[i]);
	}



}
