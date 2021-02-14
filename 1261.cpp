#include <iostream>
#include <queue>
#include <cstring>
#define MAX 100
using namespace std;

char map[MAX][MAX];
bool visited[MAX][MAX];
int w, h;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

struct spot {
	int x;
	int y;
	int wall;
	spot(int x, int y, int w) {
		this->x = x;
		this->y = y;
		this->wall = w;
	}
};
struct compare {
	bool operator()(spot a, spot b) {
		return a.wall > b.wall;
	}
};

int bfs()
{
	memset(visited, false, sizeof(visited));
	priority_queue<spot,vector<spot>, compare> pq;
	pq.push(spot(0, 0, 0));
	visited[0][0] = true;
	while (!pq.empty()) {
		int x = pq.top().x;
		int y = pq.top().y;
		int wall = pq.top().wall;
		pq.pop();
		
		if (x == w - 1 && y == h - 1)
			return wall;

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx < 0 || nx >= w || ny < 0 || ny >= h || visited[ny][nx])
				continue;

			visited[ny][nx] = true;
			if (map[ny][nx] == '1') 
				pq.push(spot(nx, ny, wall + 1));
			else
				pq.push(spot(nx, ny, wall));
		}
	}
}
int main()
{
	cin >> w >> h;
	string input;
	for (int i = 0; i < h; i++) {
		cin >> input;
		for (int j = 0; j < w; j++)
			map[i][j] = input.at(j);
	}
	cout << bfs() << endl;
}