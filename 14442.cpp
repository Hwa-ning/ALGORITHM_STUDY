#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#define MAX 1000

using namespace std;

queue<pair < pair<int, int>, pair<int, int> > >q;

int w, h, k;
int map[MAX][MAX];
bool visited[11][MAX][MAX];

int move_x[4] = { 0,1,0,-1 };
int move_y[4] = { 1,0,-1,0 };
int bfs()
{
	memset(visited, false, sizeof(visited));
	visited[0][0][0] = true;
	q.push({ {0,0},{0,1} });
	while (!q.empty()){
		int x = q.front().first.first;
		int y = q.front().first.second;
		int wb = q.front().second.first;
		int now_count = q.front().second.second;
		q.pop();

		if (x == w - 1 && y == h - 1)
			return now_count;

		for (int i = 0; i < 4; i++){
			int nx = x + move_x[i];
			int ny = y + move_y[i];

			if (0 <= nx && nx < w && 0 <= ny && ny < h) {
				if (map[ny][nx] == 1 && wb < k && !visited[wb + 1][ny][nx]) {
					visited[wb + 1][ny][nx] = true;
					q.push({ {nx,ny}, {wb + 1,now_count + 1} });
				}
				if (map[ny][nx] == 0 && !visited[wb][ny][nx]) {
					visited[wb][ny][nx] = true;
					q.push({ {nx,ny}, {wb,now_count + 1} });
				}
			}
		}
	}
	return -1;
}
int main()
{
	cin >> h >> w >> k;
	string input;
	for (int i = 0; i < h; i++) {
		cin >> input;
		for (int j = 0; j < w; j++)
			map[i][j] = input[j] - '0';
	}
	cout << bfs() << endl;
}