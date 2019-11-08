#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG_TEST_CASE 1	// 2: 2000�� �����Է����� �׽�Ʈ	1: ���� �׽�Ʈ���̽� �Է�


void printAll();
bool check();

bool DPsolution(int n, int t, int w[]) {
	// n/2 ���� W�� t�� ���� �� �ֳ�?
	// w[]
	t = t + 1;

	int** table = (int**)malloc(sizeof(int*) * n);	// n ��
	for (int i = 0; i < n; i++) {
		table[i] = (int*)malloc(sizeof(int) * t);	// t ��
	}

	// basecase
	for (int i = 0; i < n; i++) {
		table[i][0] = true;
	}
	for (int j = 0; j < t; j++) {
		if (w[0] == j) {
			table[0][j] = true;
		}
		else {
			table[0][j] = false;
		}
	}
	table[0][0] = true;

	// DP ���̺� ����
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < t; j++) {
			if (j < w[i]) { // �� �� �����ؿ���
				table[i][j] = table[i - 1][j];
			}
			else if (j == w[i]) {	// true�� ���.
				table[i][j] = true;
			}
			else {
				if (table[i - 1][j] == true) { // ������ t�̸� �Ʒ��൵ t
					table[i][j] = true;
				}
				else { // ������ f�� ���࿡�� w[i] ��ŭ ������ ��Ҹ� �����´�.
					table[i][j] = table[i - 1][j - w[i]];
				}
			}
		}
	}

	// Ȯ�ο� ���
	//printAll(table, n, t);

	// �����ؼ� N/2������ ? T : F
	int count = 0;
	int B[500];


	if (table[n-1][t-1] == false) {
		return false;		// targetNumber�� �� ����Ƿ� Fail
	}

	if (table[n - 1][t - 1] == true) {
		// ��������
		for (int i = n - 1; i >= 0; i--) {
			// count üũ :: count�� N/2 ������ N/2+1 �� �����ϴ� ��� true�� ��ȯ�ϰ� �Լ��� �����Ѵ�.
			//				  :: �� ��츦 �������� �� �ϸ� false�� ��ȯ�Ѵ�.
			//printf("count is %d\n", count);
			if (check(n, count, B)) {
				return true;
			}

			for (int j = t - 1; j > 0; j--) {
				//printf("(%d, %d) ", i,j);
				 if (i == 0 && table[i][w[i]] == true) { //
					 B[count] = w[i]; //
					 count++; //
					 //printf("count is %d\n", count);
					break;
				}

				if (table[i][j] == true && table[i - 1][j] == false) {
					//printf("i = %d j = %d ", i,j);
					B[count] = w[i];
					count++;
					//printf("c= %d\n", count);
					//printf("\nB[%d] = %d in ", count - 1, w[i]);
					break;
				}
				else if(table[i][j] == false) {
					
				} else {
					 break;
				}
			}
		}

		if (check(n, count, B)) {
			return true;
		}


		return false;
	}

	return false;

}

int total = 0;
// true ���� üũ �Լ�
bool check(int n, int count, int B[]) {
	//int total = 0;
	if (n % 2 == 0 && count == n / 2) { // n/2
		printf("\nsol is : ");
		for (int i = 0; i < count; i++) {
			printf("%d, ", B[i]);
			total += B[i];
		}
		printf("\n");
		printf("Sum is %d\n", total);
		return true;
	}
	else if (n % 2 != 0 && count == n / 2 + 1) {
		printf("\nsol is : ");
		for (int i = 0; i < count; i++) {
			printf("%d, ", B[i]);
			total += B[i];
		}
		printf("\n");
		printf("Sum is %d\n", total);
		return true;
	}
	total = 0;
	return false;
}


void printAll(int** table, int n, int t) {
	// n�� t�� ��� ��� �Լ�
	printf("   ");
	for (int i = 0; i < t; i++) {
		printf("%d  ", i);
	}
	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("%d  ", i);
		for (int j = 0; j < t; j++) {
			printf("%d  ", table[i][j]);
		}
		printf("\n");
	}
}

// ��������
int compare(const void *a, const void *b){
	int num1 = *(int *)a;    
	int num2 = *(int *)b;   
	if (num1 < num2) return -1;
	if (num1 > num2) return 1;      
	return 0;
}


int main() {

	// 2000 �� ü�� ���� �����ؼ� �Է�
	// 1000 vs 1000

	// set : 1, 2, 3, 4, .... 2000
	// Sub : T , F, T , ...   // T : A���� ����, F : A���� ����x (B�� ���Ե�)

	// totalsum == 40 �̶��,  20 20 ���� ������
	// 41 �̸�,  21, 20
	// 21 20 �� �� ������?  22 19 �� �ٽ� ��� ��� ...... �ݺ�
	// TRUE �� ���´ٸ� ����
	// �������Ͽ� ������ ���ϱ� :: �ο����� �������� �������� ���� ��� Fail. �ٽ� subsum�� �����Ͽ� ��� �ݺ�


	/*
	N���� �Էµȴ�. totalSum�� ���Ѵ�.

	N/2 ������ totalSum/2 �� ���� �� �ִ��� ����.
	��������°�? �׷��ٸ� �װ� ���̴�...

	totalSum/2�� �� �Ǵ°�?
	totalSum/2 -1 �� ��������°�?
	totalSum/2 -2 ��? ... �ݺ�...  	��������� �ű⼭ stop.
	totalSum/2 -k ���� ��������ٸ�? -> output : totalSum/2 -k , totalSum - (totalSum/2 -k)
	0�� �Ǿ �� ��������ٸ�? -> ����� 0, totalSum  ex) input : 40,  output : L-40 , R-0

	N/2 ������ K�� ����������� Ȯ���ϴ� �����?  :: Subset Sum Problem! 
	*/

	int numberOfMens;	// ����� �� ��
	int totalSum = 0;	// ��� ��� �������� ����


	/// TEST CASE�� ���� 2000�� ��������. 
#if DEBUG_TEST_CASE >= 2
	srand(time(NULL));

	numberOfMens = 1000;	// 2000�� ������
	int* W = (int*)malloc(sizeof(int) * numberOfMens);

	int buf = 0;
	for (int i = 0; i < numberOfMens; i++) {
		//scanf_s("%d", &buf);
		buf = (rand() % 100) + 1; // 1 ~ 100 ���� ������ ���� ����
		W[i] = buf;
		totalSum += buf;
	}
#endif


#if DEBUG_TEST_CASE < 2
	printf("�Է��� ����� �� : ");
	scanf_s("%d", &numberOfMens);

	int* W = (int*)malloc(sizeof(int) * numberOfMens);

	int buf = 0;
	printf("\n������� �����Ը� �Է��ϼ��� : ");
	for (int i = 0; i < numberOfMens; i++) {
		scanf_s("%d", &buf);
		W[i] = buf;
		totalSum += buf;
	}
#endif
	// W�� ������������ ����
	qsort(W, numberOfMens, sizeof(int), compare);


	int targetNumber = totalSum / 2;	// Target�� �켱 ������ ����.
	// N/2 ������ Target�� ���� �� �ִ��� Ȯ��
	// N/2 ������ Target-1�� ���� �� �ִ��� Ȯ�� .... target ��ŭ �ݺ�
	
	printf("\nTragetNumber : %d TotalSum : %d\n", targetNumber, totalSum);

	if (numberOfMens == 2) {	// 2���� ��� DPsolution�� ����� �ʿ䰡 ����.
		printf("Leftside : %d, Rightside : %d", W[0], W[1]);
		return;
	}
	else if (numberOfMens == 1) {
		printf("1�� ���Դϴ�...");
		return;
	}

	// DP�� �̿��� Solution ���ϱ�
	for (int i = 0; targetNumber != 0; i++) {
		if (DPsolution(numberOfMens, targetNumber, W) == true) {	// ã��!
			printf("\nSTOP\n");
			//printf("Leftside : %d,  Rightside : %d", targetNumber, totalSum - targetNumber);
			printf("Leftside : %d,  Rightside : %d", total, totalSum - total);
			break;
		}
		else {
			// ���� DPsol ����
			targetNumber--;
		}
	}


}