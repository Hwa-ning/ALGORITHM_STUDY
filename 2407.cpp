#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string DP[101][101];

string addBigInteger(string s1, string s2) {
	string result;
	int sum = 0;
	while (!s1.empty() || !s2.empty() || sum) {
		if (!s1.empty()) {
			sum += s1.back() - '0';
			s1.pop_back();
		}
		if (!s2.empty()) {
			sum += s2.back() - '0';
			s2.pop_back();
		}
		result.push_back( (sum % 10) + '0');
		sum /= 10;
	}
	reverse(result.begin(), result.end());
	return result;
}
string combination(int N, int M)
{
	if (N == M || M == 0)
		return "1";

	string &result = DP[N][M];
	if (result != "")
		return result;

	result = addBigInteger(combination(N - 1, M - 1), combination(N - 1, M));
	return result;
}
int main()
{
	int N, M;
	cin >> N >> M;

	cout << combination(N,M) << endl;
}