#include <iostream>
#include <string>
#include <queue>
#define MAX 50

using namespace std;

int w, h;
char map[MAX][MAX];
bool visited[MAX][MAX][MAX][MAX];

int move_x[4] = { 0,1,0,-1 };
int move_y[4] = { -1,0,1,0 };
char move_step[4] = { 'N','E','S','W' }; // 이거 조심하자
struct pack {
	int fX;
	int fY;
	int sX;
	int sY;
	pack(int a, int b, int c, int d) {
		this->fX = a;
		this->fY = b;
		this->sX = c;
		this->sY = d;
	}
};
int p[2][2];

void check(int& fX, int& fY, int& sX, int& sY)
{
	if (fX == -1)
		fX = w - 1;
	else if (fX == w)
		fX = 0;
	
	if (fY == -1)
		fY = h - 1;
	else if (fY == h)
		fY = 0;

	if (sX == -1)
		sX = w - 1;
	else if (sX == w)
		sX = 0;

	if (sY == -1)
		sY = h - 1;
	else if (sY == h)
		sY = 0;
}
void bfs() {
	memset(visited, false, sizeof(visited));
	queue<pair<pack, string> >q;
	string s = "";
	q.push({pack(p[0][0],p[0][1],p[1][0],p[1][1]) , s });
	visited[p[0][0]][p[0][1]][p[1][0]][p[1][1]] = true;
	while (!q.empty()) {
		int now_fX = q.front().first.fX;
		int now_fY = q.front().first.fY;
		int now_sX = q.front().first.sX;
		int now_sY = q.front().first.sY;
		string now_step = q.front().second;
		q.pop();

		if (now_fY == now_sY && now_fX == now_sX) {
			cout << now_step.size() << " " << now_step << endl;
			return;
		}

		for (int i = 0; i < 4; i++) {
			int next_fX = now_fX + move_x[i];
			int next_fY = now_fY + move_y[i];
			int next_sX = now_sX + move_x[i];
			int next_sY = now_sY + move_y[i];
			check(next_fX, next_fY, next_sX, next_sY);
			if (map[next_fY][next_fX] == 'X') { // 벽인 경우 다시 전의 자리로 돌아가자
				next_fX -= move_x[i];
				next_fY -= move_y[i];
			}
			if (map[next_sY][next_sX] == 'X') {
				next_sX -= move_x[i];
				next_sY -= move_y[i];
			}
			check(next_fX, next_fY, next_sX, next_sY); // 맵 끝에서 끝으로 이동하는 경우

			if (map[next_fY][next_fX] == 'G' || map[next_sY][next_sX] == 'G')
				continue;
			if (visited[next_fY][next_fX][next_sY][next_sX])
				continue;

			string next_step = "";
			next_step+=now_step;
			next_step+=move_step[i];
			visited[next_fY][next_fX][next_sY][next_sX] = true;
			q.push({ pack(next_fX,next_fY,next_sX,next_sY), next_step });
		}
	}
	cout << "IMPOSSIBLE" << endl;
}
int main()
{
	int test_case; 
	cin >> test_case;
	for (int t = 0; t < test_case; t++){
		int pp = 0;
		cin >> h >> w;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> map[i][j];
				if (map[i][j] == 'P') {
					map[i][j] = '.';
					p[pp][0] = j;
					p[pp++][1] = i;
				}
			}
		}
		bfs();
	}
	return 0;
}