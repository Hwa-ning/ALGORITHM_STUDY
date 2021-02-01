#include <iostream>
#include <algorithm>
#include <queue>

#define MAX 50

using namespace std;

int w,h;
char map[MAX][MAX];
int DP[MAX][MAX];
int move_x[4] = { 0,0,-1,1 };
int move_y[4] = { 1,-1,0,0 };
bool visited[MAX][MAX];
void input()
{
	cin >> h >> w;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			cin >> map[i][j];
			DP[i][j] = -1;
		}
}
int dfs(int y, int x)
{
	if (DP[y][x] == -1)
	{
		DP[y][x] = 0;

		visited[y][x] = true;
		for (int i = 0; i < 4; i++)
		{
			char tmp = map[y][x];
			if (tmp == 'H')
				break;

			int now = (tmp - '0');
			int next_y = y + now * move_y[i];
			int next_x = x + now * move_x[i];
			 
			if (next_y < 0 || h <= next_y || next_x < 0 || w <= next_x || map[next_y][next_x] == 'H') // map 범위 초과
				continue;

			DP[y][x] = max(DP[y][x], dfs(next_y, next_x)+1); // 현재칸과 ny,nx 지점을 비교
		}
		visited[y][x] = false;
	}
	else
	{
		if (visited[y][x]) {
			cout << -1 << endl;
			exit(0);
		}
	}
	return DP[y][x];
}
int main()
{
	input();
	int res = dfs(0, 0) + 1;
	cout << res << endl;
	return 0;
}