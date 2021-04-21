#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	string N;
	cin >> N;
	int count[9] = { 0 };

	// 9876
	for (int i = 0; i < N.length(); i++) {
		int now = N[i] - '0';
		if (now == 9)
			count[6]++;
		else
			count[now]++;
	}
	cout << count[6] << endl;

	(count[6] /= 2) + 1;
	cout << count[6] << endl;

 	(count[6] % 2 == 0 ) ? count[6] = count[6]/2 : count[6] = count[6]/2 + 1;
	int nowMax = 0;
	for (int i = 0; i < 9; i++)
		nowMax = max(count[i], nowMax);

	cout << nowMax << endl;
}