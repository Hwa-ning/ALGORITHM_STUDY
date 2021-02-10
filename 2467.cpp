#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

vector<int>v;
int N;
int main()
{
	cin >> N;
	int temp;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		v.push_back(temp);
	}
	int left, right;
	int res = 2100000000;
	int left_idx = 0;
	int right_idx = N - 1;

	while (left_idx < right_idx) {
		int tempL = v[left_idx];
		int tempR = v[right_idx];

		if (res > abs(v[left_idx] + v[right_idx])) {
			res = abs(v[left_idx] + v[right_idx]);
			left = v[left_idx];
			right = v[right_idx];
		}
		if (tempL + tempR > 0)
			right_idx--;
		else
			left_idx++;
	}
	cout << left << " "<< right << endl;
}