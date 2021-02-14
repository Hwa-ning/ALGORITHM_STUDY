#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

vector<pair<pair<int, int>, int> >v;
int map[102][102];
int w, h;
string s = "";
bool first = true;
int dx[4] = { 1,0,-1,0 }; // ESWN
int dy[4] = { 0,-1,0,1 };

void robot(int nth, char com, int re) {
	int temp;
	for (int r = 0; r < re; r++) {
		switch (com) {
		case 'L':
			temp = v[nth - 1].second;
			temp = (temp + 3) % 4;
			v[nth - 1].second = temp;
			break;
		case 'R':
			temp = v[nth - 1].second;
			temp = (temp + 1) % 4;
			v[nth - 1].second = temp;
			break;
		case 'F':
			int x = v[nth - 1].first.first;
			int y = v[nth - 1].first.second;
			int d = v[nth - 1].second;
			map[y][x] = 0;
			x = x + dx[d];
			y = y + dy[d];
			if ((0 < x || x >= w || 0 < y || y >= h) && first) {
				s += "Robot ";
				s += to_string(nth);
				s += " crashes into the wall";
				first = false;
				v[nth - 1].first.first = x;
				v[nth - 1].first.second = y;
				map[y][x] = nth;
				return;
			}
			if (map[y][x] != 0 && first) {
				s += "Robot ";
				s += to_string(nth);
				s += " crashes into robot ";
				first = false;
				int n = map[y][x];
				s += to_string(n);
				v[nth - 1].first.first = x;
				v[nth - 1].first.second = y;
				map[y][x] = nth;
				return;
			}
			v[nth - 1].first.first = x;
			v[nth - 1].first.second = y;
			map[y][x] = nth;
			break;
		}
	}
}
int main()
{
	int command;
	int robots;
	cin >> w >> h;
	cin >> robots >> command;

	int x, y,pos;
	char dir;
	for (int i = 0; i < robots; i++) {
		cin >> x >> y >> dir;
		switch (dir) {
		case 'E': pos = 0; break;
		case 'S': pos = 1; break;
		case 'W': pos = 2; break;
		case 'N': pos = 3; break;
		}
		v.push_back({ {x,y},pos });
	}
	memset(map, 0, sizeof(map));
	for (int i = 0; i < robots; i++)
		map[v[i].first.second][v[i].first.first] = i + 1;

	for (int i = 0; i < command; i++) {
		cin >> x >> dir >> y;
		robot(x, dir, y);
	}
	if (first)
		cout << "OK" << endl;
	else
		cout << s << endl;
}