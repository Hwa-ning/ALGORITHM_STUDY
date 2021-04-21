#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <set>

#define MAX 1000

using namespace std;

int w, h;
int map[MAX][MAX];
int ans[MAX][MAX];
int group[MAX][MAX];
bool visited[MAX][MAX];

vector<int>areaSize;

int d_x[4] = { 0,1,0,-1 };
int d_y[4] = { 1,0,-1,0 };
int groupNum = 0;

void bfs(int x, int y) {
	queue<pair<int, int> > q;
	visited[y][x] = true;
	group[y][x] = groupNum;
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

			visited[ny][nx] = true;
			group[ny][nx] = groupNum;
			q.push({ nx,ny });
			now++;
		}
	}
	areaSize.push_back(now);
	groupNum++;
}
void solve()
{
	memset(visited, false, sizeof(visited));
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) 
			if (map[i][j] == 0 && !visited[i][j]) 
				bfs(j, i);
			
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			if (map[i][j] == 1) {
				ans[i][j] = 1;
				set<int>s;
				for (int k = 0; k < 4; k++) {
					int nx = j + d_x[k];
					int ny = i + d_y[k];

					if (map[ny][nx] || 0 > nx || nx >= w || 0 > ny || ny >= h)
						continue;

					if (s.find(group[ny][nx]) == s.end()) {
						s.insert(group[ny][nx]);
						ans[i][j] += areaSize[group[ny][nx]];
					}
				}
				ans[i][j] = ans[i][j]%10;
			}
			else
				ans[i][j] = 0;
		}
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