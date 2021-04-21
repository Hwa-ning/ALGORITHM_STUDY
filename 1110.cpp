#include <iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;
	int now = N;
	int res = 0;
	while (1) {
		res += 1;
		int ten = now / 10;
		int one = now % 10;
		now = one * 10 + (ten + one) % 10;
		if (now == N)
			break;
	}
	cout << res << endl;
}