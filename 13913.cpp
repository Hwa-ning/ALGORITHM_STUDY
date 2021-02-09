#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int visited[100001];
int s, b;
queue<int>q;

void bfs()
{
	q.push(s);
	visited[s] = 1;

	while (!q.empty())
	{
		int now = q.front();
		q.pop();

		if (now == b) {
			vector<int> v;
			while (true) {
				v.push_back(now);
				now = visited[now];
				if (now == s)
					break;
			}
			cout << v.size() << "\n";
			cout << s << " ";
			for (int i = v.size() - 1; i >= 0; i--)
				cout << v[i] << " ";
			return;
		}
		int next = now - 1;
		if (next >= 0 && visited[next]==-1) {
			visited[next] = now;
			q.push(next);
		}
		next = now + 1;
		if (next <= 100000 && visited[next]==-1) {
			visited[next] = now;
			q.push(next);
		}

		next = now * 2;
		if (next <= 100000 && visited[next]==-1) {
			visited[next] = now;
			q.push(next);
		}
	}
}
int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(visited, -1, sizeof(visited));
	cin >> s >> b;
	if (s == b) {
		cout << 0 << endl;
		cout << s << endl;
		return 0;
	}
	bfs();
}