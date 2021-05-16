#include <iostream>

using namespace std;

struct planet {
	int x;
	int y; // 여기주석담
	int r;
};
int main()
{
	int test_case;
	int p;
	int px, py, pr;
	cin >> test_case;
	pair<int, int>start;
	pair<int, int>finish;
	for (int t = 0; t < test_case; t++){
		cin >> start.first >> start.second;
		cin >> finish.first >> finish.second;
		cin >> p;
		int count = 0;
		for (int i = 0; i < p; i++) {
			cin >> px >> py >> pr;
			int d1 = (px - start.first) * (px - start.first) + (py - start.second) * (py - start.second);
			int d2 = (px - finish.first) * (px - finish.first) + (py - finish.second) * (py - finish.second);
			bool dd1, dd2;
			if (d1 > pr * pr)
				dd1 = false;
			else
				dd1 = true;

			if (d2 > pr * pr)
				dd2 = false;
			else
				dd2 = true;

			if (dd2 != dd1)
				count++;
		}
		cout << count << endl;
	}
}