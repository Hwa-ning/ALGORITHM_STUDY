#include <iostream>
#include <algorithm>
#define MAX 987654321

using namespace std;

int N;
int arr[1001][3];
int DP[1001][3];
int res = MAX;
// 1번, 2번, N번
// N번은 N-1번 1번
// i번은 i-1, i+1

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> arr[i][0] >> arr[i][1] >> arr[i][2];

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++)
			if (i == k)
				DP[1][k] = arr[1][k];
			else
				DP[1][k] = MAX;

		for (int k = 2; k <= N; k++) {
			DP[k][0] = arr[k][0] + min(DP[k - 1][1], DP[k - 1][2]);
			DP[k][1] = arr[k][1] + min(DP[k - 1][0], DP[k - 1][2]);
			DP[k][2] = arr[k][2] + min(DP[k - 1][0], DP[k - 1][1]);
		}

		for (int k = 0; k < 3; k++)
			if (i != k)
				res = min(res, DP[N][k]);
	}
	cout << res << endl;
}