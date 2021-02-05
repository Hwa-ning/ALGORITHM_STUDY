#include <iostream>
#include <queue>
#include <cstring>

#define MAX 300

using namespace std;

int w, h;
int move_x[4] = { 0,1,0,-1 };
int move_y[4] = { 1,0,-1,0 };
int map[MAX][MAX];
bool visited[MAX][MAX];
int copy_map[MAX][MAX];

queue<pair<int, int> > q;
queue<pair<int, int> > temp_q;

void bfs(int x, int y)
{
	temp_q.push({ x,y });
	while (!temp_q.empty())
	{
		int x = temp_q.front().first;
		int y = temp_q.front().second;
		temp_q.pop();

		for (int i = 0; i < 4; i++) {
			int next_x = x + move_x[i];
			int next_y = y + move_y[i];
			if (0 <= next_x && next_x < w && 0 <= next_y && next_y < h && map[next_y][next_x] > 0 && !visited[next_y][next_x])
			{
				visited[next_y][next_x] = true;
				temp_q.push({ next_x, next_y });
			}
		}
	}
}
int solve()
{
	int year = 0;
	while (true)
	{
		memset(visited, false, sizeof(visited));
		int count = 0;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				if (map[i][j] > 0 && !visited[i][j])
				{
					count++;
					visited[i][j] = true;
					bfs(j, i);
				}
			}
		if (count >= 2)
			return year;
		if (count == 0)
			return 0;

		int q_size = q.size();
		for (int qq = 0; qq < q_size; qq++) {
			int x = q.front().first;
			int y = q.front().second;
			q.pop();

			int ice = map[y][x];
			for (int i = 0; i < 4; i++) {
				int next_x = x + move_x[i];
				int next_y = y + move_y[i];
				if (0 <= next_x && next_x < w && 0 <= next_y && next_y < h && map[next_y][next_x] == 0)
					ice--;
			}
			if (ice > 0) {
				copy_map[y][x] = ice;
				q.push({ x,y });
			}
			else
				copy_map[y][x] = 0;
		}
		year++;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				map[i][j] = copy_map[i][j];
	}
}
int main()
{
	cin >> h >> w;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			cin >> map[i][j];
			if (map[i][j] > 0)
				q.push({ j,i });
		}
	cout << solve() << endl;
}