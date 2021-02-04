#include <iostream>
#include <cstring>
#include <algorithm>

#define MAX 50
#define PLAYER 9

using namespace std;

int arr[MAX][PLAYER];
int hitter[PLAYER];
int ans = 0;
int res = 0;
int in;
bool player[3];
bool visited[PLAYER];
int cnt = 0;
void turn(int count)
{
	switch (count) {
	case 1:
		for (int i = 2; i >= 0; i--)
			if (player[i]) {
				i == 2 ? res++ : player[i + 1] = true;
				player[i] = false;
			}
		player[0] = true;
		break;
	case 2:
		for (int i = 2; i >= 0; i--)
			if (player[i]) {
				i == 0 ? player[2] = true : res++;
				player[i] = false;
 			}
		player[1] = true;
		break;
	case 3:
		for (int i = 2; i >= 0; i--)
 			if (player[i]) {
				res++;
				player[i] = false;
			}
		player[2] = true;
		break;
	case 4:
		for (int i = 0; i < 3; i++)
			if (player[i])
				res++;
		memset(player, false, sizeof(player));
		res++;
		break;
	}
}
void game_start(int now_in, int start)
{
	if (now_in == in){
		ans = max(res, ans);
		return;
	}

	int out = 0;
	memset(player, false, sizeof(player));
	while (true) {
		switch (arr[now_in][hitter[start]]) {
		case 0: out++; break;
		case 1: turn(1); break;
		case 2: turn(2); break;
		case 3: turn(3); break;
		case 4: turn(4); break;
		}
		start++;
		if (start == 9) start = 0;
		if (out == 3) break;
	}
	game_start(now_in + 1, start);
}
void shuffle_player(int now_num)
{
	if (now_num == 9) {
		game_start(0, 0);
		res = 0;
		return;
	}
	if (now_num == 3)
		now_num++;

	for (int i = 0; i < 9; i++) {
		if (!visited[i]) {
			visited[i] = true;
			hitter[now_num] = i;
			shuffle_player(now_num + 1);
			visited[i] = false;
		}
	}
}
int main()
{
	cin >> in;
	for (int i = 0; i < in; i++)
		for (int j = 0; j < PLAYER; j++)
			cin >> arr[i][j];

	memset(visited, false, sizeof(visited));
	visited[0] = true;
	hitter[3] = 0;
	shuffle_player(0);

	cout << ans << endl;
}