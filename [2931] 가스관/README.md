# 2931. 가스관

## 작성자 : Hwa-ning

## [문제 링크](https://www.acmicpc.net/problem/2931)

<br/>

### <풀이>

DFS를 활용한 구현 문제, 알맞은 파이프를 출력하는 FindPipe()에서 시간을 많이 잡아먹었다.
<br/>

1. FindStart() DFS 순회를 시작할 좌표 찾기
처음 입력을 받을때 M, Z의 좌표를 기억해두고 M 또는 Z에서 상하좌우를 확인하여 .이 아닌 파이프가 있다면 그 점에서 시작하고 상하좌우 어느 방향으로 시작하는지 nowDir에 저장해둔다.

2. DFS(int x, int y) DFS 시작
DFS를 할때 중요한 것은 그 전의 좌표에서 현재의 좌표로 어떤 방향으로 이동했는지를 알아야한다. nowDir에 맞는 방향으로 이동하도록 하자. 1,2,3,4 중 하나라면 방향이 변화되므로 방향을 바꿔주고 DFS를 실행한다. '.'이 나온다면 그 점이 해킹되어 사라진 파이프이므로 DFS를 종료한다.

3. FindPipe() 알맞은 파이프 찾기
앞서 2.DFS에서 나온 사라진 파이프의 좌표를 활용하여 사라진 파이프의 상하좌우를 확인한다.
상하좌우를 확인하여 알맞은 파이프를 찾자.

(!주의 : 방향에 맞게 사라진 파이프의 좌표에서 연결할 수 있는 파이프의 종료인지 확인해야 한다.)
![image](https://user-images.githubusercontent.com/69469529/123144787-08ef9000-d497-11eb-890f-5211f1f724d6.png)</br>
위 그림에서 상(-),우(블록'1')방향 파이프의 경우는 ?와는 연결될 수 없는 파이프로 파이프의 종류에 영향을 주지 않는 반면, 하(블록'3'),좌(-)방향 파이프의 경우는 영향을 준다. 따라서 알맞은 파이프는 블록'4'가 된다.

*** M->Z로 진행하는 경우만 있다고 생각했는데 Z->M으로 진행해야하는 경우가 있음

### <코드>

```C++
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
```
