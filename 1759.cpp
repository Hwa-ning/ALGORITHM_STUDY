#include <iostream>
#include <algorithm>

using namespace std;

int L, C;
char s[15];
bool visited[15];

void dfs(int now , int pre_idx)
{
	if (now == L) {
		int consonant = 0; // 자음
		int collection = 0; // 모음
		for (int j = 0; j < 15; j++)
			if (visited[j]) {
				switch (s[j]) {
				case 'a':
				case 'e':
				case 'i':
				case 'o':
				case 'u':
					collection++;
					break;
				default:
					consonant++;
					break;
				}
			}
		if (collection >= 1 && consonant >= 2) {
			for (int i = 0; i < C; i++)
				if (visited[i])
					cout << s[i];
			cout << endl;
		}
		return;
	}

	for(int i=pre_idx;i<C;i++)
		if (!visited[i]) {
			visited[i] = true;
			dfs(now + 1, i);
			visited[i] = false;
		}
}
int main()
{
	cin >> L >> C;
	for (int i = 0; i < C; i++)
		cin >> s[i];

	sort(s, s + C);
	dfs(0,0);
}