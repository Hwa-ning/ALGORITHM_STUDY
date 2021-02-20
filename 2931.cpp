#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int w, h;
char map[25][25];
bool visited[25][25];
pair<int, int>M;
pair<int, int>ans;
void dfs(int x, int y)
{
	switch(map[y][x]) {
	case '.':
		ans = { x,y };
		return;
	case '1':
		visited[]
		dfs();
		dfs();
	case '2':
	case '3':
	case '4':
	case '|':
	case '+':
	case '-':
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
}