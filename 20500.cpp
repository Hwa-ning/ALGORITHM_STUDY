#include <iostream>
#define MOD 1000000007

using namespace std;

int DP[1516][3];

int main()
{
	int N;
	cin >> N;

	DP[1][0] = 0;
	DP[2][0] = 1;
	DP[2][1] = 1;
	DP[2][2] = 0;

	for (int i = 3; i <= N; i++){
		DP[i][0] = (DP[i - 1][1] + DP[i - 1][2]) % MOD;
		DP[i][1] = (DP[i - 1][0] + DP[i - 1][2]) % MOD;
		DP[i][2] = (DP[i - 1][0] + DP[i - 1][1]) % MOD;
	}
	cout << DP[N][0] << endl;

	return 0;
}