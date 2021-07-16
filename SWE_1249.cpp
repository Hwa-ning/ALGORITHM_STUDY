#include <iostream>

using namespace std;

int N;
char map[100][100];
int main()
{
	int test_case;

	cin >> N;
	for (int tC = 0; tC < test_case; tC++) {
		string input;
		for (int i = 0; i < N; i++) {
			cin >> input;
			for (int j = 0; j < N; j++) {
				map[i][j] = input[j];
			}
		}
		solve();
		answer[N - 1][N - 1];
	}
	
}