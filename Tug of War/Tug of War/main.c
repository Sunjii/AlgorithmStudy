#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG_TEST_CASE 1	// 2: 2000명 랜덤입력으로 테스트	1: 직접 테스트케이스 입력


void printAll();
bool check();

int total = 0;

bool DPsolution(int n, int t, int w[]) {
	// n/2 명의 W로 t를 만들 수 있나?
	///t = t + 1;


	int** table = (int**)malloc(sizeof(int*) * n);	// 0 ~ n-1 행
	for (int i = 0; i < n; i++) {
		table[i] = (int*)malloc(sizeof(int) * t);	// 0 ~ t-1 열
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
		
		//table[0][j] = false;
	}
	table[0][0] = true;


	// DP 테이블 생성
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < t; j++) {
			if (j < w[i]) { // 윗 행 복사해오기
				table[i][j] = table[i - 1][j];
			}
			else if (j == w[i]) {	// true인 경우.
				table[i][j] = true;
			}
			else {
				if (table[i - 1][j] == true) { // 윗행이 t이면 아래행도 t
					table[i][j] = true;
				}
				else { // 윗행이 f면 윗행에서 w[i] 만큼 왼쪽의 요소를 가져온다.
					table[i][j] = table[i - 1][j - w[i]];
				}
			}
		}
	}


	// 확인용 출력
	//printAll(table, n, t);


	// 추적해서 N/2명인지 ? T : F
	int count = 0;
	int B[2000];


	if (table[n-1][t-1] == false) {
		return false;		// targetNumber를 못 만드므로 Fail
	}

	int start = t - 1;
	total = 0;

	// DP 추적 시작.
	// n/2 개로 targetNumber를 만들 수 있는지 확인.
	printf("\n%d을 %d개로 만들 수 있는지 확인합니다.\n", t, n/2);
	for (int i = n - 1; i > 0; i--) {
		/*
		if (count == n/2) {
			printf("solset is : ");
			for (int i = 0; i < count; i++) {
				printf("%d, ", B[i]);
				total += B[i];
			}
			return true;
		}
		*/
		
		

		for (int j = start; j >= 0; j--) {
			if (table[i][j] == true) {
				if (table[i - 1][j] == false) {
					// 이 경우 t는  i에서 온것.
					B[count] = w[i]; // i
					count++;
					start = start - w[i]; // i
					// i의 요소를 해집합에 추가하고, 한줄 위 & w[i] 만큼 왼쪽으로 진행.
					break;
				} else {
					// 이 경우 t는 일단 위쪽 어디선가 온 것.
					// 한줄 위로 간다.
					break;
				}
			} else {	// table[i][j] == false인 경우는 볼게 없음.

			}

		}

	}


	printf("count is %d\n", count);
	if (count == n / 2) {
		printf("solset is : ");
		for (int i = 0; i < count; i++) {
			printf("%d, ", B[i]);
			total += B[i];
		}

		for (int i = 0; i < n; i++) {
			free(table[i]);
		}
		free(table);

		return true;
	}
	else {
		for (int i = 0; i < n; i++) {
			free(table[i]);
		}
		free(table);
		return false;
	}

	printf("\n\nNONONONNO");
	return -1;








	///////
	if (table[n - 1][t - 1] == true) {
		// 추적시작
		printf("\n%d에서 Tracing Start...\n", t);
		for (int i = n - 1; i >= 0; i--) {
			// count 체크 :: count가 N/2 내지는 N/2+1 을 만족하는 경우 true를 반환하고 함수를 종료한다.
			//				  :: 위 경우를 만족하지 못 하면 false를 반환한다.
			//printf("count is %d\n", count);
			if (check(n, count, B)) {
				return true;
			}

			/// 숫자가 중복되면 버그가 발생하는듯? ----> 추적 부분 다시 확인..
			for (int j = start; j > 0; j--) {	// for j=t-1 to j>0 j--;
				// start 에서 시작하도록								
				//printf("(%d, %d) ", i,j);
				
				 if (i == 0 && table[i][w[i]] == true) { //
					 B[count] = w[i]; //
					 count++; //
					break;
				}
				

				// i == 0 인 경우.
				///if (i == 0) {
				///	B[count] = 0;
				///	count++;
				///	break;
				///}

				if (table[i][j] == true && table[i - 1][j] == false) {
					//printf("i = %d j = %d ", i,j);
					B[count] = w[i];
					count++;
					//printf("c= %d\n", count);
					//printf("\nB[%d] = %d in ", count - 1, w[i]);
					start = start - w[i]; // +1?
					//printf(" %d열 ", start);
					break;
				}
				else if(table[i][j] == false) {
					//start--;
				} else if(table[i][j] == true && table[i-1][j] == true){
					
					break;
				}
			}
		}


		if (check(n, count, B)) {
			return true;
		}
		else {
			return false;
		}


		return false;
	}
	//////



	
	return false;



}


// true 조건 체크 함수
bool check(int n, int count, int B[]) {
	total = 0;
	if (n % 2 == 0 && count == n / 2) { // n/2
		printf("\nsol is : ");
		for (int i = 0; i < count; i++) {
			printf("%d, ", B[i]);
			total += B[i];
		}
		printf("\n");
		printf("Sum is %d, Count is %d\n", total, count);
		return true;
	}
	else if (n % 2 != 0 && count == n / 2 + 1) {
		printf("\nsol is : ");
		for (int i = 0; i < count; i++) {
			printf("%d, ", B[i]);
			total += B[i];
		}
		printf("\n");
		printf("Sum is %d, Count is %d\n", total, count);
		return true;
	}
	total = 0;
	return false;
}


void printAll(int** table, int n, int t) {
	// n행 t열 행렬 출력 함수
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

// 오름차순
int compare(const void *a, const void *b){
	int num1 = *(int *)a;    
	int num2 = *(int *)b;   
	if (num1 < num2) return -1;
	if (num1 > num2) return 1; 
	return 0;
}


int main() {

	// 2000 명 체중 랜덤 생성해서 입력
	// 1000 vs 1000

	// set : 1, 2, 3, 4, .... 2000
	// Sub : T , F, T , ...   // T : A팀에 포함, F : A팀에 포함x (B에 포함됨)

	// totalsum == 40 이라면,  20 20 으로 나눠봄
	// 41 이면,  21, 20
	// 21 20 이 안 나오면?  22 19 로 다시 잡고 계산 ...... 반복
	// TRUE 가 나온다면 성공
	// 역추적하여 구성원 구하기 :: 인원수가 절반으로 나눠지지 않은 경우 Fail. 다시 subsum을 설정하여 계산 반복


	/*
	N명이 입력된다. totalSum을 구한다.

	N/2 명으로 totalSum/2 를 만들 수 있는지 본다.
	만들어지는가? 그렇다면 그게 답이다...

	totalSum/2가 안 되는가?
	totalSum/2 -1 은 만들어지는가?
	totalSum/2 -2 는? ... 반복...  	만들어지면 거기서 stop.
	totalSum/2 -k 에서 만들어진다면? -> output : totalSum/2 -k , totalSum - (totalSum/2 -k)
	0이 되어도 안 만들어진다면? -> 결과는 0, totalSum  ex) input : 40,  output : L-40 , R-0

	N/2 명으로 K가 만들어지는지 확인하는 방법은?  :: Subset Sum Problem! 
	*/

	int numberOfMens;	// 사람의 총 수
	int totalSum = 0;	// 모든 사람 몸무게의 총합


	/// TEST CASE를 위한 2000명 랜덤생성. 
#if DEBUG_TEST_CASE >= 2
	srand(time(NULL));

	numberOfMens = 2000;	// 2000명 오류남
	int* W = (int*)malloc(sizeof(int) * numberOfMens);

	printf("Ping");
	int buf = 0;
	for (int i = 0; i < numberOfMens; i++) {
		//scanf_s("%d", &buf);
		buf = (rand() % 100) + 1; // 1 ~ 100 까지 몸무게 랜덤 생성
		W[i] = buf;
		totalSum += buf;
	}
	printf(" Pong ");
#endif


#if DEBUG_TEST_CASE < 2
	printf("입력할 사람의 수 : ");
	scanf_s("%d", &numberOfMens);

	int* W = (int*)malloc(sizeof(int) * numberOfMens);

	int buf = 0;
	printf("\n사람들의 몸무게를 입력하세요 : ");
	for (int i = 0; i < numberOfMens; i++) {
		scanf_s("%d", &buf);
		W[i] = buf;
		totalSum += buf;
	}
#endif
	// W를 오름차순으로 정렬
	qsort(W, numberOfMens, sizeof(int), compare);


	int targetNumber = totalSum / 2;	// Target은 우선 총합의 절반.
	// N/2 명으로 Target을 만들 수 있는지 확인
	// N/2 명으로 Target-1을 만들 수 있는지 확인 .... target 만큼 반복
	
	printf("\nTragetNumber : %d TotalSum : %d\n", targetNumber, totalSum);

	if (numberOfMens == 2) {	// 2명인 경우 DPsolution을 사용할 필요가 없음.
		printf("Leftside : %d, Rightside : %d", W[0], W[1]);
		return;
	}
	else if (numberOfMens == 1) {
		printf("1명 뿐입니다...");
		return;
	}

	// DP를 이용한 Solution 구하기
	for (int i = 0; targetNumber != 0; i++) {
		printf(" %d \n", i);
		if (DPsolution(numberOfMens, targetNumber, W) == true) {	// 찾음!
			printf("\nSTOP\n");
			//printf("Leftside : %d,  Rightside : %d", targetNumber, totalSum - targetNumber);
			printf("Leftside : %d,  Rightside : %d", total, totalSum - total);
			break;
		}
		else {
			// 다음 DPsol 진행
			targetNumber--;
		}
	}


}