#include <iostream>
#include <algorithm>

using namespace std;

int DP[1000000];

void makeOne(int idx) {
	if (idx % 3 == 0) {
		if (idx % 2 == 0)
			DP[idx] = min({ DP[idx / 3], DP[idx / 2], DP[idx - 1] }) + 1;
		else
			DP[idx] = min(DP[idx / 3],DP[idx - 1]) + 1 ;
	}
	else if (idx % 2 == 0)
		DP[idx] = min(DP[idx / 2], DP[idx - 1]) + 1;
	else
		DP[idx] = DP[idx - 1] + 1;
}
int main()
{
	int N;
	cin >> N;

	DP[1] = 0;
	DP[2] = 1;
	DP[3] = 1;

	for (int i = 4; i <= N; i++)
		makeOne(i);

	cout << DP[N] << endl;
}