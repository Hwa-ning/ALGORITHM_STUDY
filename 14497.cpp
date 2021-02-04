#include <iostream>
#include <cstring>
#include <queue>
#define MAX 300

using namespace std;

queue<pair<int, int> >q;

int h, w;
int j_x, j_y, b_x, b_y;
char map[MAX][MAX];
bool visited[MAX][MAX];
int move_x[4] = { 0,1,0,-1 };
int move_y[4] = { 1,0,-1,0 };
int solve(int level)
{
	for (int i = 0; i < 4; i++)
	{
		int next_x = j_x + move_x[i];
		int next_y = j_y + move_y[i];
		if(0<=next_x && next_x <w && 0 <= next_y && next_y <h )
			q.push({ next_x,next_y });
	}

	memset(visited, false, sizeof(visited));
	visited[j_y][j_x] = true;

	while (!q.empty())
	{
		int now_x = q.front().first;
		int now_y = q.front().second;
		q.pop();

		if (map[now_y][now_x] == '#')
			return level;

		else if (map[now_y][now_x] == '0')
		{
			for (int i = 0; i < 4; i++)
			{
				int next_x = now_x + move_x[i];
				int next_y = now_y + move_y[i];
				if (0 <= next_x && next_x < w && 0 <= next_y && next_y < h)
					if (!visited[next_y][next_x]) {
						visited[next_y][next_x] = true;
						q.push({ next_x,next_y });
					}
			}
		}
		else
			map[now_y][now_x] = '0';
	}
	return solve(level + 1);
}
int main()
{
	cin >> h >> w;
	cin >> j_y >> j_x >> b_y >> b_x;
	j_x--; j_y--;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			cin >> map[i][j];

	cout << solve(1) << endl;
	return 0;
}