#include <iostream>
#include <queue>

#define MAX 1000
using namespace std;

int w, h;
int move_x[8] = { -1,0,1,-1,1,-1,0,1 };
int move_y[8] = { -1,-1,-1,0,0,1,1,1 };
int map[MAX][MAX];
queue<pair<int, int> >q;
int bfs()
{
	int res = 0;
	while (true) {
		int q_size = q.size();
		for (int s = 0; s < q_size; s++) {
			int x = q.front().first;
			int y = q.front().second;
			q.pop();
			for (int i = 0; i < 8; i++) {
				int n_x = x + move_x[i];
				int n_y = y + move_y[i];
				if (0 > n_x || n_x >= w || 0 > n_y || n_y >= h ||map[n_y][n_x]==0)
					continue;
				map[n_y][n_x]--;
				if (map[n_y][n_x] == 0)
					q.push({ n_x,n_y });
			}
		}
		if (q.empty())
			return res;
		res++;
	}
}
int main()
{
	cin >> h >> w;
	char input;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			cin >> input;
			if (input == '.') {
				map[i][j] = 0;
				q.push({ j,i });
			}
			else
				map[i][j] = (input - '0');
		}
	cout << bfs() << endl;
	return 0;
}