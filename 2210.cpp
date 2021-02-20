#include <iostream>
#include <algorithm>

using namespace std;

int res = 0;
int map[5][5];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
bool visited[1000000];
void move(int x, int y, int now, int count) {
	if (count == 6) {
		if (!visited[now]) {
			visited[now] = true;
			res++;
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5)
			continue;

		int next = now * 10;
		next += map[ny][nx];
		move(nx, ny, next, count + 1);
	}
}
int main()
{
	for (int i = 0; i < 5; i++) // h
		for (int j = 0; j < 5; j++) // w
			cin >> map[i][j];

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			move(j, i, map[i][j], 1);
	
	cout << res << endl;
	return 0;
}