#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

int N, M;
int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,-1,-1,-1,0,1,1,1 };
int map[100][100];
int remove_cloud[100][100];

vector<pair<int, int> >cloud;
vector<pair<int, int> >command;

void MoveCloud(int dir, int move) {
	for (int i = 0; i < cloud.size(); i++) {
		int x = cloud[i].first;
		int y = cloud[i].second;

		for (int j = 0; j < move; j++) {
			x += dx[dir];
			y += dy[dir];
			if (x == -1)
				x = N - 1;
			else if (x == N)
				x = 0;

			if (y == -1)
				y = N - 1;
			else if (y == N)
				y = 0;
		}
		cloud[i].first = x;
		cloud[i].second = y;
	}
}
void RemoveCloud() {
	memset(remove_cloud, false, sizeof(remove_cloud));
	for (int i = 0; i < cloud.size(); i++) {
		int x = cloud[i].first;
		int y = cloud[i].second;
		map[y][x]++;
		remove_cloud[y][x] = true;
	}
}
void WaterCopy() {
	for (int i = 0; i < cloud.size(); i++) {
		int x = cloud[i].first;
		int y = cloud[i].second;

		for (int j = 0; j < 4; j++) {
			int next_x = x + dx[2 * j + 1];
			int next_y = y + dy[2 * j + 1];

			if (0 > next_x || 0 > next_y || next_x >= N || next_y >= N || map[next_y][next_x] == 0)
				continue;
			map[y][x]++;
		}
	}
	cloud.clear();
}
void MakeCloud() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (map[i][j] >= 2 && !remove_cloud[i][j]) {
				cloud.push_back({ j,i });
				map[i][j] -= 2;
			}
}
void Solve() {
	for (int step = 0; step < M; step++) {
		MoveCloud(command[step].first, command[step].second);
		RemoveCloud();
		WaterCopy();
		MakeCloud();
	}
}
int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	int dir, move;
	for (int i = 0; i < M; i++) {
		cin >> dir >> move;
		command.push_back({ dir - 1,move });
	}
	cloud.push_back({ 0,N - 1 });
	cloud.push_back({ 0,N - 2 });
	cloud.push_back({ 1,N - 1 });
	cloud.push_back({ 1,N - 2 });
	Solve();
	int res = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			res += map[i][j];
	cout << res << endl;
}