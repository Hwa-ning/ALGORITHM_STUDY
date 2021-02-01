#include <iostream>
#include <cstring>
#include <queue>
#define MAX 50

using namespace std;

int map[MAX][MAX];
pair<int, int> AirCleaner[2];
int w, h, T;
int move_x[4] = { 0,1,0,-1 };
int move_y[4] = { 1,0,-1,0 };
void input()
{
	int count = 0;
	cin >> h >> w >> T;
	for (int i = 0; i < h; ++i)
		for (int j = 0; j < w; ++j) {
			cin >> map[i][j];
			if (map[i][j] == -1) {
				AirCleaner[count].first = j;
				AirCleaner[count++].second = i;
			}
		}
}
void spread()
{
	int temp[MAX][MAX];
	memset(temp, 0, sizeof(temp));
	for(int now_y=0;now_y<h;++now_y)
		for (int now_x = 0; now_x < w; ++now_x) {
			if (map[now_y][now_x] > 0)
			{
				int dust = map[now_y][now_x];
				queue<pair<int, int>>q;
				for (int i = 0; i < 4; ++i) {
					int next_x = now_x + move_x[i];
					int next_y = now_y + move_y[i];
					if (0 > next_x || next_x >= w || 0 > next_y || next_y >= h || map[next_y][next_x]==-1)
						continue;
					else
						q.push({ next_x,next_y });
				}
				int spread_count = q.size();
				while (!q.empty()) {
					int x = q.front().first;
					int y = q.front().second;
					q.pop();
					temp[y][x] += dust / 5;
				}
				temp[now_y][now_x] += dust -(dust / 5) * spread_count;
			}
		}
	for (int i = 0; i < 2; ++i)
	{
		int x = AirCleaner[i].first;
		int y = AirCleaner[i].second;
		temp[y][x] = -1;
	}
	memcpy(map, temp, sizeof(temp));
}
void airClean()
{
	int start_x = AirCleaner[0].first;
	int start_y = AirCleaner[0].second;
	
	int next = map[start_y][++start_x];
	int temp = 0;
	map[start_y][start_x] = temp;
	start_x++;

	while (start_x != w-1) {
		temp = map[start_y][start_x];
		map[start_y][start_x++] = next;
		next = temp;
	}

	start_x--; start_y--;
	while (start_y != 0) {
		temp = map[start_y][start_x];
		map[start_y--][start_x] = next;
		next = temp;
	}
	
	start_y++; start_x--;
	while (start_x != 0) {
		temp = map[start_y][start_x];
		map[start_y][start_x--] = next;
		next = temp;
	}

	start_x++; start_y++;
	while (start_y != AirCleaner[0].second) {
		temp = map[start_y][start_x];
		map[start_y++][start_x] = next;
		next = temp;
	}

	start_x = AirCleaner[1].first;
	start_y = AirCleaner[1].second;

	next = map[start_y][++start_x];
	temp = 0;
	map[start_y][start_x] = temp;
	start_x++;

	while (start_x != w) {
		temp = map[start_y][start_x];
		map[start_y][start_x++] = next;
		next = temp;
	}

	start_x--; start_y++;
	while (start_y != h) {
		temp = map[start_y][start_x];
		map[start_y++][start_x] = next;
		next = temp;
	}

	start_y--; start_x--;
	while (start_x != -1) {
		temp = map[start_y][start_x];
		map[start_y][start_x--] = next;
		next = temp;
	}

	start_x++; start_y--;
	while (start_y != AirCleaner[1].second) {
		temp = map[start_y][start_x];
		map[start_y--][start_x] = next;
		next = temp;
	}
}
void solve()
{
	for (int i = 0; i < T; ++i) {
		spread();
		airClean();
	}
	int res = 0;
	for (int i = 0; i < h; ++i)
		for (int j = 0; j < w; ++j)
			if (map[i][j] >= 0)
				res += map[i][j];
	cout << res << endl;
}
int main()
{
	input();
	solve();
}