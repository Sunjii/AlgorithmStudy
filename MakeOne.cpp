#include <stdio.h>

int min(int a, int b) {
	if (a > b) {
		return b;
	}
	else {
		return a;
	}
}

int count[10000000]; // 연산횟수를 기록하는 배열

int main() {

	int input;	// 연산 횟수를 구할 입력값.
	scanf_s("%d", &input);

	/*
		count[1] = 0
		count[2] = 1; // 2를 1로 만드는 연산횟수
		count[3] = 1; // 3을 1로 만드는 연산횟수

		count[4] = 2; // 4->2->1 (2번) // 나누기 연산후, count[2]의 결과를 재활용
		count[5] = 3; // 5->4-> .. (3번) // 빼기연산 후, count[4]의 결과를 재활용
		count[6] = 2; // 6->3	or		6->2 (2) // 나누기연산 후, count[3]의 결과를 재활용
		count[7] = 3; // 7->6-> ... (3) // 빼기연산 후, count[6]의 결과를 재활용
		count[8] = 3; // 8->4->... (3) // 나누기연산 후, count[4]의 결과를 재활용
		.....
		count[n] = ?;
		우선 1을 빼는 계산을 해서 count[n]에 저장한다.
		나눠진다면 나눈 숫자, (n/2 or n/3)의 연산횟수를 재활용한다.
		둘중 최소값을 count[n]에 다시 저장한다.
	*/

	// bottom-up 방식.
	// 각 숫자마다 가장 적은 입력 횟수를 배열에 기록해나간다.
	count[1] = 0;

	for (int i = 2; i <= input; i++) { // 2부터 배열을 채워나간다
		count[i] = count[i - 1] + 1;	// 먼저 빼기연산을 한 결과를 기록.
		// 2나 3으로 나누어 떨어지면 기록, 비교(둘중 최소값)한다.
		if (i % 3 == 0) {
			count[i] = min(count[i], count[i / 3] + 1);
		}
		else if (i % 2 == 0) {
			count[i] = min(count[i], count[i / 2] + 1);
		}
	}



	printf("입력한 숫자 : %d\n연산 횟수 : %d\n", input, count[input]);

	return 0;
}
