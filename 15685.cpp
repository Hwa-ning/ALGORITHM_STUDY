#include <iostream>
#include <vector>

using namespace std;

int res = 0;
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,-1,0,1 };

bool map[101][101];

int main()
{
	int N;
	cin >> N;

	int x, y, d, g;
	for (int i = 0; i < N; i++){
		cin >> x >> y >> d >> g;
		vector<int>D;
		D.push_back(d);

		for (int j = 0; j < g; j++) {
			int D_size = D.size();
			for (int k = D_size - 1; k >= 0; k--)
				D.push_back((D[k] + 1) % 4);
		}
		map[x][y] = true;

		for (int j = 0; j < D.size(); j++){
			x += dx[D[j]];
			y += dy[D[j]];

			if (x < 0 || x >= 101 || y < 0 || y >= 101)
				continue;

			map[x][y] = true;
		}
	}
	for (int i = 0; i <= 100; i++)
		for (int j = 0; j <= 100; j++)
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1])
				res++;

	cout << res << endl;

	return 0;
}