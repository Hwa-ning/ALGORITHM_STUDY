#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int N, M;

int res = 987654321;
int blank = 0;

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int map[50][50];
bool visited[50][50];
vector<bool>choose_virus;
vector<pair<int, int> >v;
queue<pair<int, int> >q;

void bfs()
{
	if (blank == 0) {
		res = 0;
		return;
	}

	while (!q.empty())
		q.pop();

	memset(visited, false, sizeof(visited));

	int temp_map[50][50];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			temp_map[i][j] = map[i][j];

	for (int i = 0; i < v.size(); i++)
		if (choose_virus[i]) {
			q.push({ v[i].first,v[i].second });
			visited[v[i].second][v[i].first] = true;
		}

	int sec = 1;
	int temp_blank = 0;

	while (!q.empty()) {
		int q_size = q.size();
		for (int i = 0; i < q_size; i++) {
			int x = q.front().first;
			int y = q.front().second;
			q.pop();

			if(temp_blank == blank) {
				res = min(res, sec);
				return;
			}

			for (int j = 0; j < 4; j++) {
				int nx = x + dx[j];
				int ny = y + dy[j];

				if (nx < 0 || nx >= N || ny < 0 || ny >= N || visited[ny][nx] || map[ny][nx] == 1)
					continue;

				if(map[ny][nx]==0)
					temp_blank++;

				visited[ny][nx] = true;
				q.push({ nx,ny });
			}
		}
		if (temp_blank == blank) {
			res = min(res, sec);
			return;
		}
		sec++;
		if (sec == res)
			return;
	}
}

void choose(int idx, int vir)
{
	if (vir == M) {
		bfs();
		return;
	}

	for (int i = idx; i < v.size(); i++)
		if (!choose_virus[i]) {
			choose_virus[i] = true;
			choose(i+1,vir + 1);
			choose_virus[i] = false;
		}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0)
				blank++;
			else if (map[i][j] == 2) {
				choose_virus.push_back({ false });
				v.push_back({ j,i });
			}
		}

	choose(0,0);
	if (res == 987654321)
		cout << -1 << "\n";
	else
		cout << res << "\n";
}