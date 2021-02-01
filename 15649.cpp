#include <iostream>
#include <vector>
using namespace std;

int N, M;
bool visited[9];
void dfs(int now_num, vector<int>v)
{
	if (v.size() == M) {
		for (int i = 0; i < v.size(); i++)
			cout << v.at(i) << " ";
		cout << "\n";
		return;
	}
	for (int i = 1; i <= N; i++)
	{
		if (!visited[i]) {
			visited[i] = true;
			vector<int> temp;
			temp = v;
			temp.push_back(i);
			dfs(i, temp);
			visited[i] = false;
		}
	}
}
int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	cin >> N >> M;

	for (int i = 1; i <= N; i++)
	{
		visited[i] = true;
		vector<int> v;
		v.push_back(i);
		dfs(i, v);
		visited[i] = false;
	}
	return 0;

}