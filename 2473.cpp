#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

long long liquid[100001];

int res[3] = { 0,0,0 };
int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> liquid[i];

	sort(liquid, liquid + N);

	long long temp = 3100000000;
	for(int left=0;left<N;left++){
		int mid = left + 1;
		int right = N - 1;
		while (mid < right) {
			long long sum = liquid[left] + liquid[mid] + liquid[right];
			if (abs(sum) < temp) {
				temp = abs(sum);
				res[0] = liquid[left];
				res[1] = liquid[mid];
				res[2] = liquid[right];
			}
			if (sum < 0)
				mid++;
			else
				right--;
		}
	}
	cout << res[0] << " " << res[1] << " " << res[2] << endl;

	return 0;
}