#include <iostream>
#include <vector>

using namespace std;

// 최대일치 길이 테이블 함수
vector<int> makeTable(string pattern) {
	int patternSize = pattern.size();
	vector<int> table(patternSize, 0);
	int j = 0;
	for (int i = 1; i < patternSize; i++) {
		while (j > 0 && pattern[i] != pattern[j]) {
			j = table[j - 1];
		}
		if (pattern[i] == pattern[j]) {
			table[i] = ++j;
		}
	}
	return table;
}

void KMP(string parent, string pattern) {

	vector<int> table = makeTable(pattern);
	int parentSize = parent.size();
	int patternSize = pattern.size();
	int j = 0;
	for (int i = 0; i < parentSize; i++) {
		while (j > 0 && parent[i] != pattern[j]) {	// 일치하지 않을때,
			j = table[ j - 1];	// table[j-1]의 값을 인덱스로 하는 곳 까지 접두-접미 길이가 일치하는 곳.
										// j 
		}
		if (parent[i] == pattern[j]){	
			if (j == patternSize - 1) {	// 모든 문자열이 일치하는 경우
				printf("%d 번째에서 찾았다.\n", i - patternSize + 2);
				j = table[j]; // jump
			}
			else {
				j++;
			}
		}
	}


}



int main(void) {
	string parent = "abaabcabc";
	string pattern = "abc";

	KMP(parent, pattern);
	return 0;


}