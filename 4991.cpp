#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

#define MAX 25

using namespace std;

vector<pair<int, int> > v;

int w, h;
int move_x[4] = { 0,1,0,-1 };
int move_y[4] = { 1,0,-1,0 };

int dist[11][11];
char map[MAX][MAX];
bool visited[MAX][MAX];
bool cleaned[15];

bool cant = false;
int res;
int dirty;

int bfs(int start, int finish);

void solve(int now_count, int now_node, int now_dist)
{
	if (now_count == dirty-1) {
		res = min(res, now_dist);
		return;
	}

	for (int i = 1; i < dirty; i++)
	{
		if (!cleaned[i]) {
			cleaned[i] = true;
			if (dist[now_node][i] == -1) {
				cant = true;
				return;
			}
			solve(now_count + 1, i, now_dist + dist[now_node][i]);
			cleaned[i] = false;
		}
	}
}
void cal_dist()
{
	memset(dist, 0, sizeof(dist));
	memset(cleaned, false, sizeof(cleaned));
	for (int i = 0; i < dirty; i++) 
		for (int j = i + 1; j < dirty; j++)
		{
			dist[i][j] = bfs(i, j);
			dist[j][i] = dist[i][j];
		}
	for (int i = 1; i < dirty; i++)
	{
		cleaned[i] = true;
		solve(1, i, dist[0][i]);
		cleaned[i] = false;
	}
}
int bfs(int start, int finish)
{
	queue<pair< pair<int, int>, int > >q;
	memset(visited, false, sizeof(visited));
	visited[v[start].second][v[start].first] = true;
	int f_x = v[finish].first;
	int f_y = v[finish].second;

	q.push({ {v[start].first, v[start].second}, 0 });

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int c = q.front().second;
		q.pop();
		
		if (y == f_y && x == f_x) 
			return c;

		for (int i = 0; i < 4; i++){
			int nx = x + move_x[i];
			int ny = y + move_y[i];
			
			if (0 > ny || ny >= h || 0 > nx || nx >= w || visited[ny][nx] || map[ny][nx] == 'x')
				continue;

			visited[ny][nx] = true;
			q.push({ {nx,ny}, c + 1 });
		}
	}
	return -1;
}
int main()
{
	string input;
	while (true) {
		dirty = 1;
		res = 987654321;
		cant = false;
		cin >> w >> h;
		if (w == 0 && h == 0)
			return 0;
		v.clear();
		v.push_back({ 0,0 });
		for (int i = 0; i < h; i++) {
			cin >> input;
			for (int j = 0; j < w; j++) {
				map[i][j] = input[j];
				if (map[i][j] == 'o') {
					v[0].first = j;
					v[0].second = i;
					map[i][j] = '*';
				}
				else if (map[i][j] == '*') {
					v.push_back({ j,i });
					dirty++;
				}
			}
		}
		cal_dist();
		if (cant)
			cout << -1 << endl;
		else
			cout << res << endl;
	}
	return 0;
}