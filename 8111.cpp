#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

bool visited[20001];
pair<int, char> arr[20001];

void printAnswer(int num)
{
	if (num == -1) {
		return;
	}
	printAnswer(arr[num].first);
	cout << arr[num].second;
}
void solve(int num)
{
	memset(visited, false, sizeof(visited));
	queue<int>q;
	q.push(1);
	visited[1] = true;
	arr[1].first = -1;
	arr[1].second = '1';

	while (!q.empty()) {
		int now = q.front();
		q.pop();
		
		int tmp1 = (now * 10) % num; // 뒤에 0이 붙는 경우
		if (!visited[tmp1]) {
			arr[tmp1].first = now;
			arr[tmp1].second = '0';
			if (tmp1 == 0) {
				printAnswer(tmp1);
				return;
			}
			visited[tmp1] = true;
			q.push(tmp1);
		}

		int tmp2 = ((now * 10) + 1 ) % num; // 뒤에 1이 붙는 경우
		if (!visited[tmp2]) {
			arr[tmp2].first = now;
			arr[tmp2].second = '1';
			if (tmp2 == 0) {
				printAnswer(tmp2);
				return;
			}
			visited[tmp2] = true;
			q.push(tmp2);
		}
	}
}
int main()
{
	int test_case;
	cin >> test_case;
	int input;
	for (int i = 0; i < test_case; i++) {
		cin >> input;
		if (input == 1) {
			cout << 1 << endl;
			continue;
		}
		solve(input);
		cout << endl;
	}
	return 0;
}