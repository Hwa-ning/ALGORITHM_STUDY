#include <iostream>
#include <cstring>
#include <queue>
#define MAX 100

using namespace std;

int w, h;
int tt;
int cheese = 0;
int map[MAX + 2][MAX + 2];
int move_x[4] = { 0,1,0,-1 };
int move_y[4] = { 1,0,-1,0 };
bool visited[MAX + 2][MAX + 2];

void bfs() {
	int t = 0;
	while (true)
	{
		int count = 0;
		for (int i = 1; i <= h; i++)
			for (int j = 1; j <= w; j++)
				if (map[i][j] == 1)
					count++;

		if (count == 0) {
			tt = t;
			return;
		}
		cheese = count;
		memset(visited, false, sizeof(visited));
		cheese = count;
		queue<pair<int, int> >q;
		q.push({ 0,0 });
		visited[0][0] = true;
		while (!q.empty()) {
			int x = q.front().first;
			int y = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++) {
				int nx = x + move_x[i];
				int ny = y + move_y[i];

				if (0 > nx || nx >= w + 1 || 0 > ny || ny >= h + 1 || visited[ny][nx] || map[ny][nx]==1)
					continue;

				visited[ny][nx] = true;
				q.push({ nx,ny });
			}
		}
		for (int i = 1; i <= h; i++)
			for (int j = 1; j <= w; j++)
				if (map[i][j]==1)
					for (int k = 0; k < 4; k++) {
						int nx = j + move_x[k];
						int ny = i + move_y[k];

						if (0 > nx || nx > w + 1 || 0 > ny || ny > h + 1)
							continue;

						if (visited[ny][nx]) {
							map[i][j] = 0;
							continue;
						}
					}
		t++;
	}
}
int main()
{
	cin >> h >> w;
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++)
			cin >> map[i][j];

	bfs();
	cout << tt << endl;
	cout << cheese << endl;
}