#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<long long, char> >arr;
bool first[10];
bool use[10];
int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < 10; i++)
		arr.push_back({ 0,'A' + i, });
	
	string input;

	for (int i = 0; i < N; i++) {
		cin >> input;
		first[input[0] - 'A'] = true;
		long long mulValue = 1;
		for (int j = input.size() - 1; j >= 0; j--) {
			use[input[j] - 'A'] = true;
			arr[input[j] - 'A'].first += mulValue;
			mulValue *= 10;
		}
	}

	int count_char = 0;
	for (int i = 0; i < 10; i++)
		if (use[i]) 
			count_char++;

	long long res = 0;
	if (count_char != 10) {
		sort(arr.begin(), arr.end());
		reverse(arr.begin(), arr.end());
		for (long long i = 0; i < count_char; i++)
			res += arr[i].first * (9 - i);
	}
	else {
		sort(arr.begin(), arr.end());
		
		int idx = 1;
		vector<pair<long long, char> >temp(10);
		for (int i = 0; i < 10; i++) {
			if (first[arr[i].second - 'A']) {
				temp[idx++] = arr[i];
			}
			else {
				temp[0] = arr[i];
				break;
			}
		}
		for (int i = idx; i < 10; i++)
			temp[i] = arr[i];

		for (long long i = 9; i >= 0; i--)
			res += temp[i].first * i;
	}
	cout << res << endl;
}