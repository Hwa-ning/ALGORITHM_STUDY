#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

int p, pt;
bool possible[50];
bool pushed[50];
vector<int> party[50];
queue<int> q;

void spread(int nth)
{
	for (int i = 0; i < party[nth].size(); i++) {
		int temp = party[nth].at(i);
		if (!pushed[temp]) {
			pushed[temp] = true;
			q.push(temp);
		}
	}
}
int solve()
{
	memset(possible, true, sizeof(possible));
	while (!q.empty()) {
		int who = q.front();
		q.pop();

		for (int i = 0; i < pt; i++) {
			if (!possible[i])
				continue;
			for (int j = 0; j < party[i].size(); j++) {
				if (party[i].at(j) == who) {
					spread(i);
					possible[i] = false;
					break;
				}
			}
		}
	}

	int res = 0;
	for (int i = 0; i < pt; i++)
		if (possible[i])
			res++;

	return res;
}
int main()
{
	cin >> p >> pt;
	int temp,truth,who;
	cin >> truth;
	memset(pushed, false, sizeof(pushed));
	for (int i = 0; i < truth; i++) {
		cin >> who;
		q.push(who);
		pushed[who] = true;
	}

	for (int i = 0; i < pt; i++) {
		cin >> temp;
		for (int j = 0; j < temp; j++) {
			cin >> who;
			party[i].push_back(who);
		}
	}
	cout << solve() << endl;
}