#include <iostream>
#include <vector>

using namespace std;

vector<int> v_lis;

int main()
{
	int input, N;
	while (cin >> N) {
		int ans = 0;
		v_lis.clear();
		v_lis.push_back(-1);
		for (int i = 0; i < N; i++) {
			cin >> input;
			if (v_lis.back() < input) {
				v_lis.push_back(input);
				++ans;
			}
			else {
				auto it = lower_bound(v_lis.begin(), v_lis.end(), input);
				*it = input;
			}
			for (int i = 0; i < v_lis.size(); i++)
				cout << v_lis[i] << " ";
			cout << endl;
		}

		cout << ans << endl;
	}
	return 0;
}