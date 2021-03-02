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
		if (pq.top() <= p[i].first) // i��° ������ ���� ���� ������ �����ð����� �ʰ� �����Ѵٸ�
			pq.pop();				// �� ���ǽ��� ���ǰ� ������ ������ �ϸ�ǹǷ� pq.pop

		pq.push(p[i].second);		// ����ð��� push
	}
	cout << pq.size() << endl;
}