#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int w, h;
char map[25][25];
bool visited[25][25];
pair<int, int>M;
pair<int, int>ans;
char res;
int dx[4] = { 0,1,0,-1 }; //  0  1  2  3
int dy[4] = { 1,0,-1,0 }; // ÇÏ ¿ì »ó ÁÂ

// 210220 Åä ÆÀ¹ö

void dfs(int x, int y)
{
	switch(map[y][x]) {
	case '.':
		ans = { x,y };
		return;
	case '1':
		if (!visited[y + 1][x]) {
			visited[y + 1][x] = true;
			dfs(x, y + 1);
		}
		if (!visited[y][x + 1]) {
			visited[y][x + 1] = true;
			dfs(x + 1, y);
		}
		break;
	case '2':
		if (!visited[y - 1][x]) {
			visited[y - 1][x] = true;
			dfs(x, y - 1);
		}
		if (!visited[y][x + 1]) {
			visited[y][x + 1] = true;
			dfs(x + 1, y);
		}
		break;
	case '3':
		if (!visited[y - 1][x]) {
			visited[y - 1][x] = true;
			dfs(x, y - 1);
		}
		if (!visited[y][x - 1]) {
			visited[y][x - 1] = true;
			dfs(x - 1, y);
		}
		break;
	case '4':
		if (!visited[y + 1][x]) {
			visited[y + 1][x] = true;
			dfs(x, y + 1);
		}
		if (!visited[y][x - 1]) {
			visited[y][x - 1] = true;
			dfs(x - 1, y);
		}
		break;
	case '|':
		if (!visited[y - 1][x]) {
			visited[y - 1][x] = true;
			dfs(x, y - 1);
		}
		if (!visited[y+1][x]) {
			visited[y+1][x] = true;
			dfs(x, y + 1);
		}
		break;
	case '+':
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			
			if (visited[ny][nx])
				continue;
			
			visited[ny][nx] = true;
			dfs(nx, ny);
		}
		break;
	case '-':
		if (!visited[y][x+1]) {
			visited[y][x+1] = true;
			dfs(x + 1, y);
		}
		if (!visited[y][x-1]) {
			visited[y][x-1] = true;
			dfs(x - 1, y);
		}
	}
}
int main()
{
	string input;
	cin >> h >> w;
	for (int i = 0; i < h; i++) {
		cin >> input;
		for (int j = 0; j < w; j++) {
			map[i][j] = input.at(j);
			if (map[i][j] == 'M')
				M = { j,i };
		}
	}
	visited[M.second][M.first] = true;
	dfs(M.first, M.second);
	cout << ans.first << ans.second << res << endl;
}