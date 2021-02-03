#include <iostream>
#include <algorithm>

using namespace std;

int arr[300];
int DP[300];

int main()
{
	int N;
	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> arr[i];

	DP[0] = arr[0];
	DP[1] = max(arr[0] + arr[1], arr[1]);
	DP[2] = max(arr[0] + arr[2], arr[1] + arr[2]);

	for (int i = 3; i < N; i++)
		DP[i] = max((DP[i - 2] + arr[i]), DP[i - 3] + arr[i - 1] + arr[i]);

	cout << DP[N - 1] << endl;
}