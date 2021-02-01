#include <iostream>

using namespace std;

int N;
int res = 0;
int map[16][16];

void dfs(int y, int x, int pre_state)
{
	if (y == N - 1 && x == N - 1)
	{
		res++;
		return;
	}
	switch (pre_state) {
	case 0: // 가로
		if (x + 1 < N && map[y][x + 1] == 0)
			dfs(y, x + 1, 0); // 가로
		if (y + 1 < N && x + 1 < N && map[y][x + 1] == 0 && map[y + 1][x] == 0 && map[y + 1][x + 1] == 0)
			dfs(y + 1, x + 1, 2); // 대각선
		break;
	case 1: // 세로
		if (y + 1 < N && map[y + 1][x] == 0)
			dfs(y + 1, x, 1); // 세로
		if (y + 1 < N && x + 1 < N && map[y][x + 1] == 0 && map[y + 1][x] == 0 && map[y + 1][x + 1] == 0)
			dfs(y + 1, x + 1, 2); // 대각선
		break;
	case 2: // 대각선
		if (x + 1 < N && map[y][x + 1] == 0)
			dfs(y, x + 1, 0); // 가로
		if (y + 1 < N && map[y + 1][x] == 0)
			dfs(y + 1, x, 1); //세로
		if (y + 1 < N && x + 1 < N && map[y][x + 1] == 0 && map[y + 1][x] == 0 && map[y + 1][x + 1] == 0)
			dfs(y + 1, x + 1, 2); // 대각선
		break;
	}
}
int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	dfs(0, 1, 0);
	cout << res << endl;
	return 0;
}