#include <iostream>
#include <algorithm>

using namespace std;

int N;
int building[50];
int res[50];
int result = 0;
void CheckBuilding(int idx)
{
	int count = 0;
	for (int left = idx - 1; left > 0; --left) {
		double a = (double)(building[left] - building[idx]) / (double)(left - idx);
		double b = (double)(building[idx]) - (a * (double)idx);
		int temp_left = idx - 1;
		for(; temp_left > left; --temp_left) {
			if (a * temp_left + b <= building[temp_left])
				break;
		}
		if (temp_left == left)
			count++;
	}

	for (int right = idx + 1; right <= N; right++) {
		double a = (double)(building[right] - building[idx]) / (double)(right - idx);
		double b = (double)(building[idx]) - (a * (double)idx);
		int temp_right = idx+1;
		for (;temp_right < right; ++temp_right) {
			if (a * temp_right + b <= building[temp_right])
				break;
		}
		if (temp_right == right)
			count++;
	}
	result = max(result, count);
}
int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++) 
		cin >> building[i];

	for (int i = 1; i <= N; i++)
		CheckBuilding(i);

	cout << result << endl;
}