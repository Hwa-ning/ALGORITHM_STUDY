#include <iostream>
#include <queue>
#include <cstring>

int N, customer, M, now_customer = 0;
int tx, ty;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int map[20][20];
bool visited[20][20];
struct taxi {
	int sx;
	int sy;
	int fx;
	int fy;
	bool finish;
};

taxi t[400];
using namespace std;

int bfs(int destx,int desty) {
	queue<pair<pair<int, int>, int > >q;
	memset(visited, false, sizeof(visited));
	visited[ty][tx] = true;
	q.push({ { tx,ty },0 });

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int now = q.front().second;
		q.pop();
	
		if (destx == x && desty == y) 
			return now;

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (0 > nx || nx >= N || 0 > ny || ny >= N || visited[ny][nx] || map[ny][nx] == 1)
				continue;

			visited[ny][nx] = true;
			q.push({ {nx,ny},now + 1 });
		}
	}
	return -1;
}
int solve() {
	while (true) {
		if (customer == now_customer)
			return M;

		int now_min = 987654321;
		int dest = 0;
		for (int i = 0; i < customer; i++) {
			if (t[i].finish)
				continue;

			int dist = bfs(t[i].sx, t[i].sy);
			if (dist == -1)
				return -1;

			if (now_min > dist) {
				dest = i;
				now_min = dist;
				continue;
			}
			if (now_min == dist) {
				if (t[i].sx == t[dest].sx) {
					if (t[i].sy < t[dest].sy)
						dest = i;
				}
				else {
					if (t[i].sx < t[dest].sx)
						dest = i;
				}
			}
		}

		if (M < now_min)
			return -1;

		M -= now_min;

		tx = t[dest].sx;
		ty = t[dest].sy;

		int res = bfs(t[dest].fx, t[dest].fy);

		if (M < res)
			return -1;

		M += res;

		t[dest].finish = true;

		tx = t[dest].fx;
		ty = t[dest].fy;

		now_customer++;
	}
}
int main()
{
	cin >> N >> customer >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[j][i];

	cin >> tx >> ty;
	tx--;
	ty--;

	for (int i = 0; i < customer; i++) {
		cin >> t[i].sx >> t[i].sy >> t[i].fx >> t[i].fy;
		t[i].sx--;
		t[i].sy--;
		t[i].fx--;
		t[i].fy--;
		t[i].finish = false;
	}
	cout << solve() << endl;
}