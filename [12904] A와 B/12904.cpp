#include <iostream>
#include <algorithm>

using namespace std;

string origin, dest;
int solve(string str) {
	if (str.length() == origin.length()) {
		if (str.compare(origin) == 0)
			return 1;
		else
			return 0;
	}
	int nowLength = str.length();
	string temp = str.substr(0, nowLength - 1);
	if (str[nowLength - 1] == 'A')
		solve(temp);
	else {
		reverse(temp.begin(), temp.end());
		solve(temp);
	}
}
int main()
{
	cin >> origin >> dest;
	cout << solve(dest) << endl;
}