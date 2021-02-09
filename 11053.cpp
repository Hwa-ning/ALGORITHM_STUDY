#include <iostream>
#define MAX 1000
using namespace std;

int arr[MAX + 1];
int DP[MAX + 1];

int arr_length;
int res = 0;

int main()
{
	cin >> arr_length;

	for (int i = 1; i <= arr_length; i++)
		cin >> arr[i];

	for (int i = 1; i <= arr_length; i++) {
		int min = 0;
		for (int j = 0; j < i; j++) {
			if (arr[i] > arr[j]) {
				if (DP[j] > min)
					min = DP[j];
			}
		}
		DP[i] = min + 1;
		if (DP[i] > res)
			res = DP[i];
	}

	cout << res << endl;
	return 0;
}