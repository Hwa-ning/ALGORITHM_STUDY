#include <iostream>

using namespace std;

int map[100][100];

int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				if (map[i][j] == 1)
					continue;
				if (i == j) {
					continue;
				}
				else if (map[i][k] == 1 && map[k][j] == 1) {
					map[i][j] = 1;
					continue;
				}
			}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << map[i][j] << " ";
		cout << endl;
	}
}