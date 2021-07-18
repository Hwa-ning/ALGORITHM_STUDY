#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
int map[1001][1001];
int DP[1001][1001];

int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++) // h
		for (int j = 1; j <= M; j++) // w
			cin >> map[i][j];

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			DP[i][j] = max({ DP[i - 1][j],DP[i - 1][j - 1],DP[i][j - 1] }) + map[i][j];
	
	cout << DP[N][M] << endl;
}