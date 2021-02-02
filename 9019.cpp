#include <iostream>
#include <queue>
#include <cstring>
#define MAX 10000
using namespace std;

bool visited[MAX];

int start, res;
string bfs()
{
	queue<pair<int, string> >q;
	q.push({ start,"" });
	visited[start] = true;
	while (!q.empty())
	{
		int now_num = q.front().first;
		string now_string = q.front().second;
		q.pop();

		if (now_num == res)
			return now_string;

		//D
		int temp = (now_num * 2) % MAX;
		if (!visited[temp]){
			visited[temp] = true;
			q.push({ temp, now_string + "D" });
		}

		//S
		temp = (now_num - 1 < 0 ? 9999 : now_num - 1);
		if (!visited[temp]){
			visited[temp] = true;
			q.push({ temp, now_string + "S" });
		}

		//L
		temp = now_num / 1000 + (now_num % 1000) * 10;
		if (!visited[temp]){
			visited[temp] = true;
			q.push({ temp, now_string + "L" });
		}

		//R
		temp = now_num % 10 * 1000 + now_num / 10;
		if (!visited[temp]){
			visited[temp] = true;
			q.push({ temp, now_string + "R" });
		}
	}
}

int main()
{
	int test_case;
	cin >> test_case;
	for (int i = 0; i < test_case; i++)
	{
		memset(visited, false, sizeof(visited));
		cin >> start >> res;
		cout << bfs() << endl;
	}
	return 0;
}