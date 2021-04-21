#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

long long liquid[100001];

int res[2] = { 0,0 };
int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> liquid[i];

	sort(liquid, liquid + N);

	int left = 0;
	int right = N - 1;
	long long temp = 2100000000;
	while (left < right) {
		long long sum = liquid[left] + liquid[right];
		if (abs(sum) < temp ) {
			temp = abs(sum);
			res[0] = left;
			res[1] = right;
		}
		if (sum > 0)
			right--;
		else
			left++;
	}
	cout << liquid[res[0]] << " " << liquid[res[1]] << endl;

	return 0;
}