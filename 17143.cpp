#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int h, w, N;

int res = 0;
int king = 0;
int dx[4] = { 0,0,1,-1 };
int dy[4] = { -1,1,0,0 };
struct shark {
	int x;
	int y;
	int speed;
	int dir;
	int size;
	shark(int x, int y, int a, int b, int c) {
		this->x = x;
		this->y = y;
		this->speed = a;
		this->dir = b;
		this->size = c;
	}
};
bool compare(shark s1, shark s2) {
	return s1.size > s2.size;
}
vector<shark> tmp[100][100];
vector<shark> map[100][100];
void shark_move()
{
	for (int i = 0; i < h; i++) 
		for (int j = 0; j < w; j++)
			if (map[i][j].size() != 0)
			{
				shark temp = map[i][j][0];
				for (int j = 0; j < temp.speed; j++) {
					if ((temp.dir == 0 && temp.y == 0) || (temp.dir == 1 && temp.y == h - 1) || (temp.dir == 2 && temp.x == w - 1) || (temp.dir == 3 && temp.x == 0)) {
						switch (temp.dir) {
						case 0:
						case 2:
							temp.dir++;
							break;
						case 1:
						case 3:
							temp.dir--;
							break;
						}
						temp.x += dx[temp.dir];
						temp.y += dy[temp.dir];
					}
				}
				map[i][j].clear();
				tmp[temp.y][temp.x].push_back(temp);
			}

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			if (tmp[i][j].size() == 0)
				continue;
			else {
				sort(tmp[i][j].begin(), tmp[i][j].end(), compare);
				shark temp = tmp[i][j][0];
				tmp[i][j].clear();
				map[i][j].push_back(temp);
			}
		}
}
void catch_shark()
{
	for (int i = 0; i < h; i++)
		if (map[i][king].size()==1)
		{
			res += map[i][king][0].size;
			map[i][king].clear();
			return;
		}
}
int main()
{
	cin >> h >> w >> N;
	for (int i = 0; i < N; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		if (d <= 2) // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			s %= 2 * h - 2;
		else        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			s %= 2 * w - 2;

		map[r - 1][c - 1].push_back(shark(c - 1, r - 1, s, d - 1, z));
	}
	if (N == 0) {
		cout << 0 << endl;
		return 0;
	}
	while (king < w) {
		catch_shark();
		shark_move();
		king++;
	}
	cout << res << endl;
}