#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct fireBall {
	int mass, speed, dir;
	fireBall(int m, int s, int d) :mass(m), speed(s), dir(d) {}
};

int N, M, K;
int dx[8] = { 0,1,1,1,0,-1,-1,-1 };
int dy[8] = { -1,-1,0,1,1,1,0,-1 };
vector<fireBall>map[50][50];

void Move()
{
	vector<fireBall>temp[50][50];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < map[i][j].size(); k++) {
				int mass = map[i][j][k].mass;
				int speed = map[i][j][k].speed;
				int dir = map[i][j][k].dir;
				int nx = ((i + speed * dy[dir]) % N + N) % N;
				int ny = ((j + speed * dx[dir]) % N + N) % N;

				temp[nx][ny].push_back(fireBall(mass, speed, dir));
			}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			map[i][j] = temp[i][j];
}
void Divide()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (map[i][j].size() >= 2) {
				bool same = true;
				int prime = map[i][j][0].dir % 2;
				int sum_mass = map[i][j][0].mass;
				int sum_speed = map[i][j][0].speed;
				int count = map[i][j].size();
				for (int k = 1; k < map[i][j].size(); k++) {
					if (same)
						if (prime != map[i][j][k].dir % 2)
							same = false;

					sum_mass += map[i][j][k].mass;
					sum_speed += map[i][j][k].speed;
				}
				map[i][j].clear();
				if (sum_mass < 5) {
					continue;
				}
				for (int l = ((same) ? 0 : 1); l < 8; l += 2)
					map[i][j].push_back(fireBall(sum_mass / 5, sum_speed / count, l));
			}
}
int main()
{
	cin >> N >> M >> K;
	int x, y, m, s, d;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> m >> s >> d;
		map[x - 1][y - 1].push_back(fireBall(m, s, d));
	}
	for (int i = 0; i < K; i++) {
		Move();
		Divide();
	}
	int res = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < map[i][j].size(); k++)
				res += map[i][j][k].mass;
	cout << res << endl;
}