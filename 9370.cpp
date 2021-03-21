#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int test_case, N, M, T, S, G, H;
int dist_S[2001]; // dist S , dist G, dist H
int dist_G[2001];
int dist_H[2001];
vector<pair<int, int> > V[2001];
vector<int> d;

void dijkstra(int from, int arr[]) {
	priority_queue<pair<int, int> > pq;
	pq.push({ 0,from });
	arr[from] = 0;
	while (!pq.empty()) {
		int _dist = -pq.top().first;
		int now = pq.top().second;
		pq.pop();

		for (int i = 0; i < V[now].size(); i++){
			int next = V[now][i].first;
			int temp_dist = V[now][i].second;

			if (arr[next] > _dist + temp_dist){
				arr[next] = _dist + temp_dist;
				pq.push({ -arr[next], next });
			}
		}
	}
}
int main()
{
	cin >> test_case;
	for (int i = 0; i < test_case; i++)
	{
		int input1, input2, input3;
		// 초기화
		for (int j = 0; j < 2001; j++){
			V[j].clear();
			dist_S[j] = 987654321;
			dist_G[j] = 987654321;
			dist_H[j] = 987654321;
		}
		d.clear();

		// 입력
		cin >> N >> M >> T;
		cin >> S >> G >> H;

		for (int j = 0; j < M; j++){
			cin >> input1 >> input2 >> input3;
			V[input1].push_back({ input2,input3 });
			V[input2].push_back({ input1,input3 });
		}

		for (int j = 0; j < T; j++){
			cin >> input1;
			d.push_back(input1);
		}

		dijkstra(S, dist_S); // S -> G, S -> H
		dijkstra(G, dist_G); // G -> 
		dijkstra(H, dist_H); // H -> 
		std::sort(d.begin(), d.end());
		int temp_dist = dist_G[H];

		for (int j = 0; j < d.size(); j++){
			int now = d[j];
			if (dist_S[now] == dist_S[G] + dist_H[now] + temp_dist) // S -> G -> H -> now
				cout << now << " ";

			if (dist_S[now] == dist_S[H] + dist_G[now] + temp_dist ) // S -> H -> G -> now
				cout << now << " ";
		}
		cout << endl;
	}
}