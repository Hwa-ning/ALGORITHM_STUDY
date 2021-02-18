#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

pair<int, int> arr[200000];
priority_queue<int>pq;

int main()
{
	int N;
	int cup = 0;

	cin >> N;
	for (int i = 0; i < N; i++) 
		cin >> arr[i].first >> arr[i].second;
	// first  :  deadline  / second  :  cup

	sort(arr, arr + N);
	
	int j = N - 1;

	for (int i = N - 1; i >= 0; i--) {
		for (; j >= 0 && arr[j].first == i; j--)
			pq.push(arr[j].second);

		if (!pq.empty()) {
			cup += pq.top();
			pq.pop();
		}
	}
	cout << cup << endl;

	return 0;
}