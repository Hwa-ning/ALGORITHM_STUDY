#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#define MAX 987654321

using namespace std;

bool visit[5][5][5];
char input[5][5][5];
char maze[5][5][5];
int dx[6] = { 0,0,0,0,1,-1 };
int dy[6] = { 0,0,1,-1,0,0 };
int dz[6] = { 1,-1,0,0,0,0 };
int order[5] = { 0,1,2,3,4 };
int rot[5];
int res = MAX;

int BFS()
{
	if (maze[0][0][0] == '0' || maze[4][4][4] == '0')
		return MAX;
	queue<pair<pair<int, int>, pair<int, int> > > q;
	memset(visit, false, sizeof(visit));
	q.push({ {0, 0}, {0, 0} });
	visit[0][0][0] = true;
	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int z = q.front().second.first;
		int cnt = q.front().second.second;
		q.pop();

		if (x == 4 && y == 4 && z == 4)
			return cnt;

		for (int i = 0; i < 6; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			int nz = z + dz[i];

			if (0 > nx || 0 > ny || 0 > nz || nx >= 5 || ny >= 5 || nz >= 5 || maze[nx][ny][nz] == '0' || visit[nx][ny][nz])
				continue;

			q.push({ {nx, ny}, {nz, cnt + 1} });
			visit[nx][ny][nz] = true;
		}
	}
	return MAX;
}
void RotateMaze(int nth, int rotateCnt) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			switch (rotateCnt) {
			case 0:
				maze[order[nth]][i][j] = input[nth][i][j];
				break;
			case 1:
				maze[order[nth]][i][j] = input[nth][4 - j][i];
				break;
			case 2:
				maze[order[nth]][i][j] = input[nth][4 - i][4 - j];
				break;
			case 3:
				maze[order[nth]][i][j] = input[nth][j][4 - i];
				break;
			}
}
void SetRotate(int select)
{
	if (select == 5) {
		for (int i = 0; i < 5; i++)
			RotateMaze(i, rot[i]);
		res = min(res, BFS());
		return;
	}
	for (int i = 0; i < 4; i++) {
		rot[select] = i;
		SetRotate(select + 1);
	}
}
int main()
{
	for (int s = 0; s < 5; s++)			
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++) 
				cin >> input[s][i][j];
			
	do {
		SetRotate(0);
	} while (next_permutation(order, order + 5));

	if (res != MAX)
		cout << res << endl;
	else
		cout << -1 << endl;
}