#include <iostream>

using namespace std;

int N, M, input;
bool visited[10];
int res = 0;

void solve(int length,int now)
{
	if (length == N) {
		if (now == M) 
			res++;
		return;
	}

	for (int i = 0; i < 10; i++)
		if (visited[i])
		{
			visited[i] = false;
			solve(length + 1, now + 1);
			visited[i] = true;
		}
		else
			solve(length + 1, now);
}
int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> input;
		visited[input] = true;
	}

	solve(0,0);

	cout << res << endl;
}