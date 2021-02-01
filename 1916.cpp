#include <iostream>
#include <vector>
#include <queue>

#define MAX 100001
#define INF 987654321
using namespace std;

int dist[1001];
int V, E, start, dest;

vector<pair<int, int> >graph[MAX];

void input()
{
	cin >> V >> E;

	int from, to, dist;
	for (int i = 0; i < E; i++)
	{
		cin >> from >> to >> dist;
		graph[from].push_back({ to,dist });
	}
	cin >> start >> dest;
}
void init()
{
	for (int i = 1; i <= V; i++)
		dist[i] = INF;
}
void dijkstra()
{
	dist[start] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0,start });

	while (!pq.empty())
	{
		int now_dist = pq.top().first;
		int now_node = pq.top().second;
		pq.pop();

		if (dist[now_node] < now_dist)
			continue;

		for (int i = 0; i < graph[now_node].size(); i++)
		{
			int neighbor = graph[now_node][i].first;
			int neighborDist = now_dist + graph[now_node][i].second;
			if (dist[neighbor] > neighborDist)
			{
				dist[neighbor] = neighborDist;
				pq.push({ neighborDist,neighbor });
			}
		}
	}
}
void output()
{
	cout << dist[dest] << endl;
}
int main()
{
	input();
	init();
	dijkstra();
	output();

	return 0;
}