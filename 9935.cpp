#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

char res[1000001];
int main() {
	string input, bomb;
	cin >> input;
	cin >> bomb;
	int now = 0, i = 0;

	int idx = 0;
	for (int i = 0; i < input.size(); i++) {
		res[idx++] = input[i];

		if (res[idx-1] == bomb[bomb.size() - 1]) {
			if (idx < bomb.size()) // 주의할것
				continue;

			bool isbomb = true;
			for (int j = 0; j < bomb.size(); j++)
				if (res[idx - j - 1] != bomb[bomb.size() - j - 1]) {
					isbomb = false;
					break;
				}
			if (isbomb)
				idx -= bomb.size();
		}
	}
	
	if (idx == 0)
		cout << "FRULA";
	else
		for (int i = 0; i < idx; i++)
			cout << res[i];

	cout << endl;

	return 0;
}