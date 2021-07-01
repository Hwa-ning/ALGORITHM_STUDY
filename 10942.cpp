#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
int s[2001];
bool DP[2001][2001];

void Cal_DP() {
	for (int i = 1; i <= N; i++)
		DP[i][i] = true;

	for (int i = 1; i + 1 <= N; i++)
		if(s[i] == s[i + 1])
			DP[i][i + 1] = true;

	for (int i = 2; i < N; i++)
		for (int j = 1; j + i <= N; j++)
			if (s[j] == s[j + i] && DP[j + 1][j + i - 1])
				DP[j][j + i] = true;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int M, S, E;

	cin >> N;
	for (int i = 1; i <= N; i++) 
		cin >> s[i];
	
	memset(DP, false, sizeof(DP));
	Cal_DP();
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> S >> E;
		cout << DP[S][E] << "\n";
	}
}