#include <iostream>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;

int from, to;
bool isprime[10000];
bool visited[10000];

queue<pair<int, int> > q;

void set_prime()
{
	memset(isprime, true, sizeof(isprime));

	isprime[0] = false;
	isprime[1] = false;

	for (int i = 2; i < 10000; i++) {
		if (isprime[i]) {
			for (int j = i + i; j < 10000; j += i)
				isprime[j] = false;
		}
	}
}
int combine_num(int a, int b, int c, int d) {
	return 1000 * a + 100 * b + 10 * c + d;
}
int bfs()
{
	while (!q.empty())
		q.pop();

	memset(visited, false, sizeof(visited));
	visited[from] = true;
	q.push({ 0,from });

	while (!q.empty()) {
		int now_count = q.front().first;
		int now = q.front().second;
		q.pop();

		if (now == to)
			return now_count;

		int a = now / 1000;  // 6 5 4 7
		int b = (now / 100) % 10;
		int c = (now / 10) % 10;
		int d = now % 10;

		vector<int>v;
		for (int i = 1; i < 10; i++)
			v.push_back(combine_num(i, b, c, d));
		for (int i = 0; i < 10; i++) {
			v.push_back(combine_num(a, i, c, d));
			v.push_back(combine_num(a, b, i, d));
			v.push_back(combine_num(a, b, c, i));
		}

		for (int i = 0; i < v.size(); i++) {
			int temp = v[i];
			if (visited[temp] || !isprime[temp])
				continue;
			else
			{
				visited[temp] = true;
				q.push({ now_count + 1,temp });
			}
		}
	}
	return -1;
}
int main()
{
	int test_case;
	cin >> test_case;
	set_prime();
	for (int t = 0; t < test_case; t++) {
		cin >> from >> to;
		int res = bfs();
		if (res == -1)
			cout << "Impossible" << endl;
		else
			cout << res << endl;
	}
	return 0;
}