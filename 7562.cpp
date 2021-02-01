#include <iostream>
#include <cstring>
#include <queue>

int move_x[8] = { 1,2,2,1,-1,-2,-2,-1 };
int move_y[8] = { 2,1,-1,-2,-2,-1,1,2 };

int map_size;
int start_x, start_y, dest_x, dest_y;
bool visited[301][301];

using namespace std;

void solve()
{
	queue<pair<pair<int, int>, int > >q;

	q.push({ { start_x,start_y }, 0 });
	visited[start_x][start_y] = true;

	while (!q.empty()) {
		int now_x = q.front().first.first;
		int now_y = q.front().first.second;
		int now_level = q.front().second;
		q.pop();
		if (now_x == dest_x && now_y == dest_y) {
			cout << now_level << endl;
			break;
		}
		for (int i = 0; i < 8; ++i) {
			int next_x = now_x + move_x[i];
			int next_y = now_y + move_y[i];
			if (0 <= next_x && next_x < map_size && 0 <= next_y && next_y < map_size)
				if (!visited[next_x][next_y]) {
					visited[next_x][next_y] = true;
					q.push({ { next_x, next_y }, now_level + 1 });
				}
		}
	}
}
int main()
{
	int test_case;
	cin >> test_case;
	
	for (int t = 0; t < test_case; ++t) {
		memset(visited, false, sizeof(visited));
		cin >> map_size;
		cin >> start_x >> start_y;
		cin >> dest_x >> dest_y;
		solve();
	}
}