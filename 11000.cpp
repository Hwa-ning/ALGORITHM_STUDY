#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

priority_queue<int, vector<int>, greater<> >pq;

pair<int, int> p[200000];

int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) 
		cin >> p[i].first >> p[i].second;
	
	sort(p, p + N);

	pq.push({ p[0].second });
	for (int i = 1; i < N; i++) {
		if (pq.top() <= p[i].first) // i번째 수업이 가장 빨리 끝나는 수업시간보다 늦게 시작한다면
			pq.pop();				// 그 강의실의 강의가 끝나면 수업을 하면되므로 pq.pop

		pq.push(p[i].second);		// 종료시간을 push
	}
	cout << pq.size() << endl;
}