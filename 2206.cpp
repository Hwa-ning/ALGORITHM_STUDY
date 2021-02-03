#include <iostream>
#include <queue>
#define MAX 1000

using namespace std;
/*
2020.10.02 틀림

벽을 부수고 최단으로 가더라도 끝까지 가려면 벽을 부숴야하는경우를 생각해야함
반례
7 4
0000
1110
0000
0111
0000
0011
0010
*/
struct loc
{
	int y;
	int x;
	int time;
	bool wallBreak; // true면 아직 벽을 부술수 있음.
	loc(int iy, int ix, int it, bool is)
	{
		y = iy; x = ix; time = it; wallBreak = is;
	}
};
queue<loc>q;
int move_x[4] = { 0,0,-1,1 };
int move_y[4] = { 1,-1,0,0 };
int N, M;
char map[MAX][MAX];
bool visited[MAX][MAX][2];
void input()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		string temp;
		cin >> temp;
		for (int j = 0; j < M; j++)
			map[i][j] = temp[j];
	}
}
int bfs()
{
	loc start(0, 0, 1, true);
	visited[0][0][1] = true;
	q.push(start);
	while (!q.empty())
	{
		int now_y = q.front().y;
		int now_x = q.front().x;
		int now_time = q.front().time;
		bool canB = q.front().wallBreak;
		q.pop();
		if (now_x == M - 1 && now_y == N - 1)
			return now_time;
		for (int i = 0; i < 4; i++)
		{
			int temp_y = now_y + move_y[i];
			int temp_x = now_x + move_x[i];
			int count = (canB == true ? 1 : 0);
			if (0 <= temp_y && temp_y < N && 0 <= temp_x && temp_x < M)
			{
				if (map[temp_y][temp_x] == '0' && !visited[temp_y][temp_x][count])
				{
					visited[temp_y][temp_x][count] = true;
					q.push(loc(temp_y, temp_x, now_time + 1, canB));
				}
				if (map[temp_y][temp_x] == '1' && canB)
				{
					visited[temp_y][temp_x][count] = true;
					q.push(loc(temp_y, temp_x, now_time + 1, false));
				}
			}
		}
	}
	return -1;
}
int main()
{
	input();
	cout << bfs() << endl;
	return 0;
}