#include <iostream>
#include <vector>

using namespace std;

// �ִ���ġ ���� ���̺� �Լ�
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
		while (j > 0 && parent[i] != pattern[j]) {	// ��ġ���� ������,
			j = table[ j - 1];	// table[j-1]�� ���� �ε����� �ϴ� �� ���� ����-���� ���̰� ��ġ�ϴ� ��.
										// j 
		}
		if (parent[i] == pattern[j]){	
			if (j == patternSize - 1) {	// ��� ���ڿ��� ��ġ�ϴ� ���
				printf("%d ��°���� ã�Ҵ�.\n", i - patternSize + 2);
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