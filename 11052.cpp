#include <iostream>
#include <algorithm>
#define MAX 1000
using namespace std;

int arr[MAX];
int DP[MAX+1];
int main()
{
	int N;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
		DP[i] = arr[i];
	}

	DP[1] = arr[1];
	DP[2] = max(arr[2], DP[1] * 2);
	for (int i = 3; i <= N; i++)
	{
		for (int j = 1; (i-j)>=1; j++) {
			DP[i] = max({ DP[i],(DP[i - j] + DP[j]), arr[i] });
		}
	}
	cout << DP[N] << endl;
}