#include <iostream>

using namespace std;

int w, h, sX[2], sY[2];
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,-1,1};
int nowX, nowY, nowDir;
char map[26][26];
void FindStart() {
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < 4; i++) {
			int startX = sX[j] + dx[i];
			int startY = sY[j] + dy[i];

			if (startX < 0 || startX >= w || startY < 0 || startY >= h)
				continue;

			if (map[startY][startX] != '.') {
				nowX = startX;
				nowY = startY;
				nowDir = i;
				return;
			}
		}
}
void DFS(int x, int y) {
	switch (map[y][x]) {
	case '.':
		nowX = x;
		nowY = y;
		return;
	case '|':
		if (nowDir == 2)
			DFS(x, y - 1);
		else
			DFS(x, y + 1);
		break;
	case '-':
		if (nowDir == 0)
			DFS(x + 1, y);
		else
			DFS(x - 1, y);
		break;
	case '+':
		if (nowDir == 2)
			DFS(x, y - 1);
		else if (nowDir == 3)
			DFS(x, y + 1);
		else if (nowDir == 0)
			DFS(x + 1, y);
		else
			DFS(x - 1, y);
		break;
	case '1':
		if (nowDir == 2) {
			nowDir = 0;
			DFS(x + 1, y);
		}
		else {
			nowDir = 3;
			DFS(x, y + 1);
		}
		break;
	case '2':
		if (nowDir == 3) {
			nowDir = 0;
			DFS(x + 1, y);
		}
		else {
			nowDir = 2;
			DFS(x, y - 1);
		}
		break;
	case '3':
		if (nowDir == 0) {
			nowDir = 2;
			DFS(x, y - 1);
		}
		else {
			nowDir = 1;
			DFS(x - 1, y);
		}
		break;
	case '4':
		if (nowDir == 0) {
			nowDir = 3;
			DFS(x, y + 1);
		}
		else {
			nowDir = 1;
			DFS(x - 1, y);
		}
		break;
	}
}
void FindPipe() {
	bool dir[4] = { false,false,false,false };
	for (int i = 0; i < 4; i++) {
		int nX = nowX + dx[i];
		int nY = nowY + dy[i];

		if (nX < 0 || nX >= w || nY < 0 || nY >= h)
			continue;

		if (map[nY][nX] != '.') {
			switch (i) {
			case 0: if (map[nY][nX] == '-' || map[nY][nX] == '+' || map[nY][nX] == '3' || map[nY][nX] == '4') dir[i] = true; break;
			case 1: if (map[nY][nX] == '-' || map[nY][nX] == '+' || map[nY][nX] == '1' || map[nY][nX] == '2') dir[i] = true; break;
			case 2: if (map[nY][nX] == '|' || map[nY][nX] == '+' || map[nY][nX] == '1' || map[nY][nX] == '4') dir[i] = true; break;
			case 3: if (map[nY][nX] == '|' || map[nY][nX] == '+' || map[nY][nX] == '2' || map[nY][nX] == '3') dir[i] = true; break;
			}
		}
	}
	cout << nowY + 1 << " " << nowX + 1 << " ";
	if (dir[0] && dir[1] && dir[2] && dir[3]) cout << "+";
	else if (dir[0] && dir[1]) cout << "-";
	else if (dir[2] && dir[3]) cout << "|";
	else if (dir[0] && dir[3]) cout << "1";
	else if (dir[0] && dir[2]) cout << "2";
	else if (dir[1] && dir[2]) cout << "3";
	else if (dir[1] && dir[3]) cout << "4";
}
int main()
{
	cin >> h >> w;
	int idx = 0;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'M' || map[i][j] == 'Z') {
				sX[idx] = j;
				sY[idx++] = i;
			}
		}
	FindStart();
	DFS(nowX, nowY);
	FindPipe();
	return 0;
}