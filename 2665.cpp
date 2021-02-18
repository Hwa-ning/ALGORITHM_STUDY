#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

int N;
int map[50][50];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
bool visited[50][50];

priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<> > pq;
int bfs()
{
	pq.push({ 0,{0,0} });
	visited[0][0] = true;
	while (!pq.empty()) {
		int c = pq.top().first;
		int x = pq.top().second.first;
		int y = pq.top().second.second;
		pq.pop();
		if (x == N - 1 && y == N - 1)
			return c;
		for (int i = 0; i < 4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			
			if (nx < 0 || nx >= N || ny < 0 || ny >= N || visited[ny][nx])
				continue;

			if (map[ny][nx] == 1) {
				visited[ny][nx] = true;
				pq.push({ c,{nx,ny} });
			}
			else if (map[ny][nx] == 0) {
				visited[ny][nx] = true;
				pq.push({ c + 1,{nx,ny} });
			}
		}
	}
}
int main()
{
	cin >> N;
	string input;
	for (int i = 0; i < N; i++) {
		cin >> input;
		for (int j = 0; j < N; j++) {
			map[i][j] = input.at(j) - '0';
		}
	}
	cout << bfs() << endl;
}