#include <iostream>
#include <queue>
#include <set>
#include <string>

using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int solve(string init)
{
	queue<pair<string,int> >q;
	set<string>visited;

	q.push({ init, 0 });
	visited.insert(init);
	
	while (!q.empty()) {
		string now = q.front().first;
		int cnt = q.front().second;
		q.pop();

		if (now == "123456780")
			return cnt;

		int idx = now.find('0');
		int x = idx / 3;
		int y = idx % 3;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 > nx || 0 > ny || nx >= 3 || ny >= 3)
				continue;

			string next = now;
			swap(next[idx], next[nx * 3 + ny]);
			if (visited.find(next) == visited.end()) {
				visited.insert(next);
				q.push({ next, cnt + 1 });
			}
		}
	}
	return -1;
}
int main()
{
	string init;
	char s;
	for (int i = 0; i < 9; i++){
		cin >> s;
		init += s;
	}
	cout << solve(init) << endl;

	return 0;
}