#include <iostream>

using namespace std;

int main()
{
	int coin[10];
	int N, K;
	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> coin[i];
	int idx = N - 1;
	int money = 0;

	int count = 0;
	while (true) {
		if (K - coin[idx] < 0) {
			idx--;
			continue;
		}
		else {
			K -= coin[idx];
			count++;
			if (K == 0)
				break;
		}
	}
	cout << count << endl;
}