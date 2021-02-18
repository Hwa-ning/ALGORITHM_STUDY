#include <iostream>

using namespace std;

int DP[1001][10];

int main()
{
	int N;
	cin >> N;
	
	for (int i = 0; i < 10; i++)
		DP[0][i] = 0;
	                        
	for (int i = 0; i < 10; i++)
		DP[1][i] = 1;

	for (int i = 0; i < 10; i++)
		DP[2][i] = 10 - i;

	for (int i = 3; i <= N; i++)
		for (int j = 0; j < 10; j++) {
			for (int k = j; k < 10; k++) {
				DP[i][j] += DP[i - 1][k];
			}
			DP[i][j] %= 10007;
		}

	int res = 0;
	for (int i = 0; i < 10; i++)
		res += DP[N][i];
	cout << res % 10007<< endl;
}