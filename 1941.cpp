#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int> >v;
string student[5];
bool* selected;
int res = 0;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
void IsConnect(string s[])
{
	bool visited[5][5];
	memset(visited, false, sizeof(visited));
	int qx, qy;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (s[i][j] == 'S')
			{
				qy = i;
				qx = j;
				break;
			}
	int cnt = 1;
	queue<pair<int, int> >q;
	q.push({ qx,qy });
	visited[qy][qx] = true;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (0 > nx || nx >= 5 || 0 > ny || ny >= 5 || visited[ny][nx] || s[ny][nx] == 'Y')
				continue;

			visited[ny][nx] = true;
			q.push({ nx,ny });
			cnt++;
		}
	}
	if (cnt == 7)
		res++;
}
void Solve(int y, int x, int cnt, string s[])
{
	if (cnt == 7)
		IsConnect(s);
	else if (cnt > 7)
		return;

	for (int i = y; i < 5; i++) {
		for (int j = (i == y ? x : 0); j < 5; j++) {
			if (s[i][j] == 'Y' && student[i][j] == 'Y') {
				s[i][j] = 'S';
				Solve(i, j, cnt+1, s);
				s[i][j] = 'Y';
			}
		}
	}
}
void PickSom(int idx, int select)
{
	if (select >= 4) {
		string temp[5];
		for (int i = 0; i < 5; i++)
			temp[i] = "YYYYY";

		int cnt = 0;
		for (int i = 0; i < v.size(); i++) {
			if (selected[i]) {
				int x = v[i].first;
				int y = v[i].second;
				temp[y][x] = 'S';
				cnt++;
			}
		}
		Solve(0, 0, cnt, temp);
	}
	for (int i = idx; i < v.size(); i++){
		if (!selected[i]) {
			selected[i] = true; 
			PickSom(i + 1, select + 1);
			selected[i] = false;
		}
	}
}
int main()
{
	for (int i = 0; i < 5; i++) {
		cin >> student[i];
		for (int j = 0; j < 5; j++)
			if (student[i][j] == 'S')
				v.push_back({j,i});
	}
	selected = new bool[v.size()];
	for (int i = 0; i < v.size(); i++) {
		selected[i] = false;
	}
	PickSom(0,0);
	cout << res << endl;
}