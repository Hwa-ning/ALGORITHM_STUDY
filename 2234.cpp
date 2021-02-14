#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#define MAX 50

using namespace std;

int w, h;
int ans[3] = { 0,0,0 };
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };
int room[MAX][MAX];
bool map[MAX][MAX][4]; // ¼­ ºÏ µ¿ ³²
bool visited[MAX][MAX];
void solve12()
{
	memset(visited, false, sizeof(visited));
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (!visited[i][j]) {
				ans[0]++;
				visited[i][j] = true;
				room[i][j] = ans[0];
				queue<pair<int, int> >q;
				q.push({ j,i });
				int roomCount = 1;
				while (!q.empty()) {
					int x = q.front().first;
					int y = q.front().second;
					q.pop();
					for (int k = 0; k < 4; k++) {
						int nx = x + dx[k];
						int ny = y + dy[k];
						if (0 > nx || nx >= w || 0 > ny || ny >= h || visited[ny][nx] || map[y][x][k])
							continue;
						visited[ny][nx] = true;
						q.push({ nx, ny });
						room[ny][nx] = ans[0];
						roomCount++;
					}
				}
				ans[1] = max(roomCount, ans[1]);
			}
		}
	}
}
void solve3()
{
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			for (int k = 0; k < 4; k++)
				if (map[i][j][k]) {
					memset(visited, false, sizeof(visited));
					int Nx = j + dx[k];
					int Ny = i + dy[k];
					if (0 > Nx || Nx >= w || 0 > Ny || Ny >= h)
						continue;
					int r1 = room[i][j];
					int r2 = room[Ny][Nx];
					if (r1 == r2)
						continue;
					queue<pair<int, int> >q;
					q.push({ j, i });
					visited[i][j] = true;

					int roomCount = 1;
					while (!q.empty()) {
						int x = q.front().first;
						int y = q.front().second;
						q.pop();

						for (int l = 0; l < 4; l++) {
							int nx = x + dx[l];
							int ny = y + dy[l];

							if (0 > nx || nx >= w || 0 > ny || ny >= h || visited[ny][nx] || room[ny][nx]!=room[y][x])
								continue;

							visited[ny][nx] = true;
							q.push({ nx, ny });
							roomCount++;
						}
					}
					q.push({ Nx, Ny });
					visited[Ny][Nx] = true;
					roomCount++;
					while (!q.empty()) {
						int x = q.front().first;
						int y = q.front().second;
						q.pop();

						for (int l = 0; l < 4; l++) {
							int nx = x + dx[l];
							int ny = y + dy[l];

							if (0 > nx || nx >= w || 0 > ny || ny >= h || visited[ny][nx] || room[ny][nx] != room[y][x])
								continue;

							visited[ny][nx] = true;
							q.push({ nx, ny });
							roomCount++;
						}
					}
					ans[2] = max(ans[2], roomCount);
				}
}
int main()
{
	cin >> w >> h;
	int input;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			cin >> input;
			for (int b = 0; b < 4; b++)
				if (input & (1 << b))
					map[i][j][b] = true;
				else
					map[i][j][b] = false;
		}
	solve12();
	cout << ans[0] << endl;
	cout << ans[1] << endl;
	solve3();
	cout << ans[2] << endl;
}