# 20056. 마법사 상어와 파이어볼

## 작성자 : Hwa-ning

## [문제 링크](https://www.acmicpc.net/problem/20056)

<br/>

### <풀이>

삼성 SW 역량 기출 문제, 삼성스러운 구현문제였다. 2차원 배열의 vector\<fireBall>에다 해당 행,열에 위치한 파이어볼을 저장해두는 방식으로 풀이했다. 행,열 값에서 계산에 착오가 있어서 조금 헤매긴 했지만 그렇게 어려운 문제는 아닌 것 같다.

1. Move()<br>
   파이어볼을 이동하는 함수, 2차원 배열 vector에서 파이어볼이 존재하는 칸에서 fireBall이 이동해야하는 위치로 이동시킨 후 저장해둘 2차원 배열 vector\<fireBall> temp에 저장해두고 모든 이동을 끝낸 후, temp의 결과를 map에
   옮겨담는다.(!!!_map에다가 옮겨담게되면 이동한 fireBall을 또 움직일 수 있음_)<br>
   _\*\* int nx = ((i + speed _ dy[dir]) % N + N) % N; << 새로 알게 된 것
2. Divide()<br>
   파이어볼이 2개이상인 칸에서 파이어볼을 나누는 함수, 2차원 배열 vector에서 파이어볼의 정보를 담고 있을 때 총 2가지의 경우가 생긴다.<br>
   (1) 파이어볼이 존재하지 않거나 1개인 경우<br>
   존재하지 않다면 나눌 것이 없음 / 1개인 경우 파이어볼이 나누어지지 않으므로 그 자리에 그대로 위치하면 됨.
   (2) 파이어볼이 2개 이상인 경우<br>
   파이어볼을 문제 조건에 따라 나누어줘야하는데 bool same 변수를 사용하여 짝수 방향으로 나눌지 홀수 방향으로 나눌지 결정했다. 또한, 파이어볼의 질량이 0인 경우 나눠지지 않으므로 해당 칸 파이어볼 질량의 합 sum_mass가 5미만이라면 해당 칸의 파이어볼들을 나누지 않고 해당 칸의 vector를 clear만 하도록 한다.

### <코드>

```C++
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
```
