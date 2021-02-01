// 210129 
#include <iostream>
#include <queue>
#define MAX 50

using namespace std;

int w, h;

int move_x[4] = { 1,0,-1,0 };
int move_y[4] = { 0,1,0,-1 };
char map[MAX][MAX];
bool visited[MAX][MAX];
bool waterd[MAX][MAX];
queue<pair<int, int> >water;
queue<pair<int, int> >cute;
int bfs(int now_level)
{
	int cute_size = cute.size();
	for (int c = 0; c < cute_size; c++) {
		int x = cute.front().first;
		int y = cute.front().second;
		cute.pop();

		if (map[y][x] == '*')
			continue;

		if (map[y][x] == 'D')
			return now_level;

		for (int i = 0; i < 4; i++) {
			int next_x = x + move_x[i];
			int next_y = y + move_y[i];

			if (0 > next_y || next_y >= h || 0 > next_x || next_x >= w || visited[next_y][next_x])
				continue;

			if (map[next_y][next_x] == '.' || map[next_y][next_x] == 'D') {
				cute.push({ next_x,next_y });
				visited[next_y][next_x] = true;
			}
		}
	}

	int water_size = water.size();
	for (int wa = 0; wa < water_size; wa++) {
		int x = water.front().first;
		int y = water.front().second;
		water.pop();

		for (int i = 0; i < 4; i++) {
			int next_x = x + move_x[i];
			int next_y = y + move_y[i];
			
			if (0 > next_y || next_y >= h || 0 > next_x || next_x >= w || waterd[next_y][next_x])
				continue;

			if (map[next_y][next_x] == '.') {
				map[next_y][next_x] = '*';
				waterd[next_y][next_x] = true;
				water.push({ next_x,next_y });
			}
		}
	}
	if (cute.empty())
		return -1;
	else
		return bfs(now_level + 1);
}
int main()
{
	cin >> h >> w;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'S') {
				cute.push({ j,i });
				visited[i][j] = true;
				map[i][j] = '.';
			}
			else if (map[i][j] == '*') {
				waterd[i][j] = true;
				water.push({ j,i });
			}
		}
	}
	int res = bfs(0);
	if (res == -1)
		cout << "KAKTUS" << endl;
	else
		cout << res << endl;
}