#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#define MAX 1000

using namespace std;

int w, h;
int move_x[4] = { 0,1,0,-1 };
int move_y[4] = { 1,0,-1,0 };

char map[MAX][MAX];
bool visited[MAX][MAX];
queue<pair<int, int> >q;
queue<pair<int, int> >f;

int bfs()
{
	int time = 0;
	while (!q.empty()) {
		int f_size = f.size();
		for (int ff = 0; ff < f_size; ff++) {
			int x = f.front().first;
			int y = f.front().second;
			f.pop();

			for (int i = 0; i < 4; i++) {
				int next_x = x + move_x[i];
				int next_y = y + move_y[i];
				
				if (0 <= next_x && next_x < w && 0 <= next_y && next_y < h && map[next_y][next_x] == '.'){
					map[next_y][next_x] = '*';
					f.push({ next_x,next_y });
				}
			}
		}

		int q_size = q.size();
		for (int qq = 0; qq < q_size; qq++) {
			int x = q.front().first;
			int y = q.front().second;
			q.pop();

			if (x == 0 || y == 0 || x == w-1 || y == h-1 )
				return time + 1;

			for (int i = 0; i < 4; i++) {
				int next_x = x + move_x[i];
				int next_y = y + move_y[i];

				if (0 <= next_x && next_x < w && 0 <= next_y && next_y < h && map[next_y][next_x] == '.' && !visited[next_y][next_x])
				{
					visited[next_y][next_x] = true;
					q.push({ next_x,next_y });
				}
			}
		}
		time++;
	}
	return -1;
}
int main()
{
	int test_case;
	cin >> test_case;
	for (int t = 0; t < test_case; t++) {
		memset(visited, false, sizeof(visited));
		cin >> w >> h;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				cin >> map[i][j];
				if (map[i][j] == '*')
					f.push({ j,i });
				if (map[i][j] == '@') {
					q.push({ j,i });
					map[i][j] = '.';
					visited[i][j] = true;
				}
			}
		int res = bfs();
		if (res == -1)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << res << endl;
		while (!q.empty())
			q.pop();
		while (!f.empty())
			f.pop();
	}
}