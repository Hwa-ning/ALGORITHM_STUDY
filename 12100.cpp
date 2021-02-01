#include <iostream>
#include <queue>
#include <algorithm>

#define MAX 20

using namespace std;

int N;
int res = 0;
int map[MAX][MAX];
void move(int count)
{
	if (count == 5) {
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < N; j++)
				res = max(res, map[i][j]);
		return;
	}
	queue<int> q;
	int temp_map[MAX][MAX];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			temp_map[i][j] = map[i][j];

	for (int dir = 0; dir < 4; dir++)
	{
		switch (dir){
		case 0: // UP
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (map[i][j])
						q.push(map[i][j]);
					map[i][j] = 0;
				}
				int idx = 0;
				while (!q.empty()) {
					int temp = q.front();
					q.pop();
					if (map[i][idx] == 0)
						map[i][idx] = temp;
					else if (map[i][idx] == temp) {
						map[i][idx] = temp * 2;
						idx++;
					}
					else {
						idx++;
						map[i][idx] = temp;
					}
				}
			}
			break;
		case 1: // LEFT
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (map[j][i])
						q.push(map[j][i]);
					map[j][i] = 0;
				}
				int idx = 0;
				while (!q.empty()) {
					int temp = q.front();
					q.pop();
					if (map[idx][i] == 0)
						map[idx][i] = temp;
					else if (map[idx][i] == temp) {
						map[idx][i] = temp * 2;
						idx++;
					}
					else {
						idx++;
						map[idx][i] = temp;
					}
				}
			}
			break;
		case 2: // DOWN
			for (int i = 0; i < N; i++) {
				for (int j = N - 1; j >= 0; j--) {
					if (map[i][j])
						q.push(map[i][j]);
					map[i][j] = 0;
				}
				int idx = N - 1;
				while (!q.empty()) {
					int temp = q.front();
					q.pop();
					if (map[i][idx] == 0)
						map[i][idx] = temp;
					else if (map[i][idx] == temp) {
						map[i][idx] = temp * 2;
						idx--;
					}
					else {
						idx--;
						map[i][idx] = temp;
					}
				}
			}
			break;
		case 3: // RIGHT
			for (int i = 0; i < N; i++) {
				for (int j = N - 1; j >= 0; j--) {
					if (map[j][i])
						q.push(map[j][i]);
					map[j][i] = 0;
				}
				int idx = N - 1;
				while (!q.empty()) {
					int temp = q.front();
					q.pop();
					if (map[idx][i] == 0)
						map[idx][i] = temp;
					else if (map[idx][i] == temp) {
						map[idx][i] = temp * 2;
						idx--;
					}
					else {
						idx--;
						map[idx][i] = temp;
					}
				}
			}
			break;
		}
		move(count + 1);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				map[i][j] = temp_map[i][j];
	}
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[j][i];
	
	move(0);
	cout << res << endl;
}