#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<pair<int, int> > > edge;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> >pq;

bool visited[10001];
int V, E, A, B, C;
int res = 0;
void prim(int v) {
	visited[v] = true;

	for (auto u : edge[v]) {
		if (!visited[u.second]) {
			pq.push({ u.first,u.second });
		}
	}

	while (!pq.empty()) {
		auto w = pq.top();
		pq.pop();
		if (!visited[w.second]) {
			res += w.first;
			prim(w.second);
			return;
		}
	}
}
int main()
{
	cin >> V >> E;
	edge.resize(V + 1);
	for (int i = 0; i < E; i++) {
		cin >> A >> B >> C; // first:distance / second : to 
		edge[A].push_back({ C,B });
		edge[B].push_back({ C,A });
	}
	prim(1);
	cout << res << endl;
}