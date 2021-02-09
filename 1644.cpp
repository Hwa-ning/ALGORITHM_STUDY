#include <iostream>
#include <vector>
#include <cstring>
#define MAX 4000001

using namespace std;

vector<int>v;
int input;
int res = 0;
bool prime[MAX];
bool visited[300000];

void prime_num()
{
	if (input <= 1)
		return;

	memset(prime, false, sizeof(prime));
	prime[0] = true;
	prime[1] = true;

	for (int i = 2; i <= input; i++) {
		if (!prime[i]) {
			for (int j = i*2; j <= input; j+=i)
				prime[j] = true;
		}
	}
	for (int i = 2; i <= input; i++)
		if (!prime[i])
			v.push_back(i);
}
void solve(int now_count, int now_idx)
{
	if (now_count == input) {
		res++;
		return;
	}
	if (now_count > input || now_idx >= v.size())
		return;

	solve(now_count + v[now_idx], now_idx + 1);
}
int main()
{
	cin >> input;
	prime_num();
	for (int i = 0; i < v.size(); i++) 
		solve(0, i);
	cout << res << endl;
}