#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int w, h;
int res = 0;
int map[500][500];
bool visited[500][500];
queue<pair<int, int > >q;
int main()
{
	memset(map, 0, sizeof(map));
	cin >> h >> w;
	int input;
	for (int i = 0; i < w; i++) {
		cin >> input;
		for (int j = 0; j < input; j++) 
			map[j][i] = 1;
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map[i][j] == 1 && !visited[i][j]) {
				int now_j = j - 1;
				int temp = 0;
				while (now_j >= 0) {
					if (map[i][now_j] == 1 || visited[i][now_j])
						break;
					temp++;
					visited[i][now_j] = true;
					now_j--;
				}
				if (now_j != -1)
					res += temp;

				now_j = j + 1;
				temp = 0;
				while (now_j < w) {
					if (map[i][now_j] == 1 || visited[i][now_j])
						break;
					temp++;
					visited[i][now_j] = true;
					now_j++;
				}
				if (now_j != w)
					res += temp;
			}
		}
	}
	cout << res << endl;
}