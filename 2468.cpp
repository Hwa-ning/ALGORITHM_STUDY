#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#define MAX 100
using namespace std;


int N;
int res = 1;
int map[MAX][MAX];
bool water[MAX][MAX];
bool visited[MAX][MAX];
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
void bfs()
{
	int now_height = 1;
	while (now_height <= 100) {
		memset(water, false, sizeof(water));
		memset(visited, false, sizeof(visited));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (map[i][j] <= now_height)
					water[i][j] = true;

		int count = 0;
		queue<pair<int, int> >q;

		for (int i = 0; i < N; i++) // h
			for (int j = 0; j < N; j++) // w
				if (!water[i][j] && !visited[i][j]) {
					count++;
					visited[i][j] = true;
					q.push({ j,i });
					while (!q.empty()) {
						int x = q.front().first;
						int y = q.front().second;
						q.pop();
						for (int k = 0; k < 4; k++) {
							int nx = x + dx[k];
							int ny = y + dy[k];
							if (nx < 0 || nx >= N || ny < 0 || ny >= N || visited[ny][nx] || water[ny][nx])
								continue;

							visited[ny][nx] = true;
							q.push({ nx,ny });
						}
					}
				}
		res = max(res, count);
		now_height++;
	}
}
int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	bfs();
	cout << res << endl;
}