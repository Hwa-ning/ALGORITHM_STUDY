#include <iostream>
#include <queue>
#include <cmath>
#define MAX 50

using namespace std;

int w, h;

int move_x[4] = { 0,1,0,-1 };
int move_y[4] = { 1,0,-1,0 };
string map[MAX];
bool visited[64][MAX][MAX];
queue<pair<pair<int, int >, pair<int, int> > >q;
int start_x, start_y;
void input()
{
	cin >> h >> w;
	for (int i = 0; i < h; ++i){
		cin >> map[i];
		for (int j = 0; j < map[i].length(); ++j)
			if (map[i][j] == '0'){
				start_y = i;
				start_x = j;
			}
	}
}
int solve()
{
	visited[0][start_y][start_x] = true;
	q.push({ { start_x,start_y }, {0,0} });

	while (!q.empty()){
		int now_x = q.front().first.first;
		int now_y = q.front().first.second;
		int now_level = q.front().second.first;
		int key = q.front().second.second;
		if (map[now_y][now_x] == '1')
			return now_level;

		q.pop();
		for (int i = 0; i < 4; ++i){
			int next_x = now_x + move_x[i];
			int next_y = now_y + move_y[i];
			if (0 > next_x || next_x >= w || 0 > next_y || next_y >= h|| visited[key][next_y][next_x] || map[next_y][next_x] =='#')
				continue;

			if ( map[next_y][next_x]=='.' || map[next_y][next_x]=='1' || map[next_y][next_x]=='0'){
				visited[key][next_y][next_x] = true;
				q.push({ {next_x,next_y},{now_level + 1,key} });
			}
			else if ('a' <= map[next_y][next_x] && map[next_y][next_x] <= 'f'){
				int newKey = key | (1 << (int(map[next_y][next_x]) - 97));
				if (!visited[newKey][next_y][next_x]){
					visited[newKey][next_y][next_x] = true;
					visited[key][next_y][next_x] = true;
					q.push({ { next_x,next_y },{now_level + 1,newKey} });
				}
			}

			else if ('A' <= map[next_y][next_x] && map[next_y][next_x] <= 'F'){
				if ( key & 1 << (int(map[next_y][next_x]) - 65)) {
					visited[key][next_y][next_x] = true;
					q.push({ { next_x, next_y }, {now_level + 1,key} });
				}
			}
		}
	}
	return -1;
}
int main()
{
	input();
	cout << solve() << endl;
	return 0;
}