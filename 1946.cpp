#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int> > v;

int main()
{
	int test_case;
	cin >> test_case;
	int N;
	for (int t = 0; t < test_case; t++) {
		cin >> N;
		v.resize(N);
		for (int i = 0; i < N; i++) 
			cin >> v[i].first >> v[i].second;

		sort(v.begin(), v.end());
		
		int min = 987654321;
		int res = 0;
		for (int i = 0; i < N; i++) {
			if (min > v[i].second) {
				min = v[i].second;
				res++;
			}
		}
		cout << res << endl;
	}
}