#include <iostream>
#include <queue>
#include <cstring>

#define MAX 102

using namespace std;

int w, h;
char map[MAX][MAX];
bool visited[MAX][MAX];
bool key[26];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
int bfs()
{
	memset(visited, false, sizeof(visited));
	queue<pair<int, int> >q;
	q.push({ 0,0 });
	visited[0][0] = true;
	int res = 0;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		if (map[y][x] == '$') {
			map[y][x] = '.';
			res++;
		}
		else if ('a' <= map[y][x] && map[y][x] <= 'z') {
			if (key[map[y][x] - 'a']) {
				map[y][x] = '.';
				q.push({ x,y });
				continue;
			}
			key[map[y][x] - 'a'] = true;
			for (int i = 1; i <= h; i++)
				for (int j = 1; j <= w; j++)
					if ((map[i][j] == map[y][x] - 32))
						map[i][j] = '.';
					
			while (!q.empty()) 
				q.pop();
			
			map[y][x] = '.';
			memset(visited, false, sizeof(visited));
			visited[y][x] = true;
			q.push({ x, y });
			continue;
		}
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 <= nx && nx <= w + 1 && 0 <= ny && ny <= h + 1 && !visited[ny][nx] && (map[ny][nx] == '.' || 'a' <= map[ny][nx] && map[ny][nx] <= 'z' || map[ny][nx] == '$')) {
				visited[ny][nx] = true;
				q.push({ nx,ny });
			}
		}
	}
	return res;
}
int main()
{
	string input;
	int test_case;
	cin >> test_case;
	for (int t = 0; t < test_case; t++) {
		cin >> h >> w;
		for (int i = 0; i <= w + 1; i++) {
			map[0][i] = '.';
			map[h + 1][i] = '.';
		}
		for (int i = 0; i <= h + 1; i++) {
			map[i][0] = '.';
			map[i][w + 1] = '.';
		}

		for (int i = 1; i <= h; i++) {
			cin >> input;
			for (int j = 0; j < w; j++) 
				map[i][j+1] = input[j];
		}
		memset(key, false, sizeof(key));
		cin >> input;
		if (input != "0") {
			for (int k = 0; k < input.length(); k++) {
				key[input[k] - 'a'] = true;
				for (int i = 1; i <= h; i++)
					for (int j = 1; j <= w; j++)
						if ((map[i][j] == input[k] - 32)) {
							map[i][j] = '.';
						}
			}
		}
		cout << bfs() << endl;
	}
}