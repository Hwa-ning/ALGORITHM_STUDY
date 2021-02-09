#include <iostream>
#include <queue>
#include <cstring>

#define MAX 1000

using namespace std;

int w, h;
int map[MAX][MAX];
int ans[MAX][MAX];
bool visited[MAX][MAX];
int d_x[4] = { 0,1,0,-1 };
int d_y[4] = { 1,0,-1,0 };

int bfs(int x, int y) {
	queue<pair<int, int> > q;
	for (int i = 0; i < h; i++)
		memset(visited[i], false, sizeof(visited[i]));
	visited[y][x] = true;
	q.push({ x,y });
	int now = 1;
	while (!q.empty()) {
		int x_ = q.front().first;
		int y_ = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x_ + d_x[i];
			int ny = y_ + d_y[i];

			if (0 > nx || nx >= w || 0 > ny || ny >= h || map[ny][nx] == 1 || visited[ny][nx])
				continue;

			if (ans[ny][nx]) {
				now += ans[ny][nx];
				continue;
			}
			else {
				visited[ny][nx] = true;
				q.push({ nx,ny });
				now++;
			}
		}
	}
	return now;
}
void solve()
{
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) 
			if (map[i][j] == 1)
				ans[i][j] = (bfs(j, i)%10);
			else
				ans[i][j] = 0;
}
int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	string input;

	cin >> h >> w;
	for (int i = 0; i < h; i++) {
		cin >> input;
		for (int j = 0; j < w; j++)
			map[i][j] = input[j] - '0';
	}
	solve();
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << ans[i][j];
		}
		cout << "\n";
	}
	return 0;
}