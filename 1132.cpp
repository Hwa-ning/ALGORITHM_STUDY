#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<long long, char> >arr;
bool first[10];
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
			arr[input[j] - 'A'].first += mulValue;
			mulValue *= 10;
		}
	}
	for (int i = 0; i < 10; i++)
		if (first[i])
			cout << char('A' + i) << "불가능" << endl;
		else
			cout << char('A' + i) << "가능" << endl;
	
	sort(arr.begin(), arr.end());
	reverse(arr.begin(), arr.end());

	for (int i = 0; i < 10; i++)
		cout << arr[i].second << " " << arr[i].first << endl;

	vector<pair<long long, char > >res;
	for (int i = 0; i < 10; i++) {
		if (first[arr[i].second - 'A']) {
			cout << arr[i].second << "맨뒤로" << endl;
			pair<long long, char> temp = arr[i];
			arr.erase(arr.begin() + i);
			arr.push_back(temp);
		}
	}

	for (int i = 0; i < 10; i++)
		cout << arr[i].second << " " << arr[i].first << endl;
	
	long long mulValue = 9;
	long long res = 0;
	for (int i = 0; i < 10; i++,mulValue--) 
		res += arr[i].first * mulValue;
	cout << res << endl;
}