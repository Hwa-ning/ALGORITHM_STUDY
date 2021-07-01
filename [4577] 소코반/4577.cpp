#include <iostream>
#include <vector>
using namespace std;

int h, w, nth = 1;
int wX, wY;
char map[50][50];
string com;
bool clear = false;
vector<pair<int, int> >dest;

void output() {
	clear = true;
	bool finish = true;
	map[wY][wX] = 'w';
	for (int i = 0; i < dest.size(); i++) {
		int X = dest[i].first;
		int Y = dest[i].second;
		if (map[Y][X] == 'w') {
			map[Y][X] = 'W';
			finish = false;
		}
		else if (map[Y][X] == 'b')
			map[Y][X] = 'B';
		else {
			map[Y][X] = '+';
			finish = false;
		}
	}
	if (!finish)
		cout << "Game " << nth++ << ": incomplete" << endl;
	else
		cout << "Game " << nth++ << ": complete" << endl;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) 
			cout << map[i][j];
		cout << endl;
	}
}
void check() {
	for (int i = 0; i < dest.size(); i++) {
		int X = dest[i].first;
		int Y = dest[i].second;
		if ((X==wX && Y == wY)|| map[Y][X] == '.')
			return;
	}
	output();
}

void move() {
	check(); // 초기에 게임이 바로 종료되는 경우 확인
	for (int c = 0; c < com.length(); c++) {
		if (clear)
			break;
		int tempX = wX;
		int tempY = wY;
		switch (com[c]) {
		case 'D': tempY++; break;
		case 'U': tempY--; break;
		case 'R': tempX++; break;
		case 'L': tempX--; break;
		}
		if (0 > tempX || tempX >= w || 0 > tempY || tempY >= h)
			continue;
		if (map[tempY][tempX] == '#')
			continue;
		else if (map[tempY][tempX] == '.') {
			wX = tempX;
			wY = tempY;
			continue;
		}
		else if (map[tempY][tempX] == 'b') {
			int tempX2 = tempX;
			int tempY2 = tempY;
			switch (com[c]) {
			case 'D': tempY2++; break;
			case 'U': tempY2--; break;
			case 'R': tempX2++; break;
			case 'L': tempX2--; break;
			}
			if (0 > tempX2 || tempX2 >= w || 0 > tempY2 || tempY2 >= h)
				continue;

			if (map[tempY2][tempX2] == '#' || map[tempY2][tempX2] == 'b')
				continue;
			else {
				map[tempY][tempX] = '.';
				map[tempY2][tempX2] = 'b';
				wX = tempX;
				wY = tempY;
				check();
			}
		}
	}
}
int main()
{
	while (true) {
		clear = false;
		dest.clear();
		cin >> h >> w;
		if (h == 0 && w == 0)
			break;
		string input;
		for (int i = 0; i < h; i++) {
			cin >> input;
			for (int j = 0; j < w; j++) {
				map[i][j] = input[j];
				if (map[i][j] == 'w') {
					map[i][j] = '.';
					wX = j;
					wY = i;
				}
				else if (map[i][j] == 'W') {
					map[i][j] = '.';
					dest.push_back({ j,i });
					wX = j;
					wY = i;
				}
				else if (map[i][j] == '+') {
					map[i][j] = '.';
					dest.push_back({ j,i });
				}
				else if (map[i][j] == 'B') {
					map[i][j] = 'b';
					dest.push_back({ j,i });
				}
			}
		}
		cin >> com;
		move();
		if(!clear)
			output();
	}
}