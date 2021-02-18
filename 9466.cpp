#include <iostream>
#include <cstring>

using namespace std;

int res = 0;
int student[100001];
bool visited[100001];
bool grouped[100001];
void dfs(int num) {

	visited[num] = true;
	int next = student[num];

	if (!visited[next])
		dfs(next);
	else if(!grouped[next]){
		res++;
		for (int i = student[num]; i != num; i = student[i])
			res++;
	}
	grouped[num] = true;
}
int main()
{
	int test_case;
	cin >> test_case;
	for (int t = 0; t < test_case; t++) {
		int people;
		memset(visited, false, sizeof(visited));
		memset(grouped, false, sizeof(visited));
		res = 0;
		cin >> people;
		for (int p = 1; p <= people; p++)
			cin >> student[p];

		for (int i = 1; i <= people; i++)
			if (!visited[i])
				dfs(i);

		cout << people - res << endl;
	}
}