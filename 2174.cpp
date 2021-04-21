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
int dx[4] = { 0,1,0,-1 }; // NESW
int dy[4] = { 1,0,-1,0 };

void robot(int nth, char com, int re) {
	if (!first)
		return;
	int temp;
	switch (com) {
	case 'L':
		temp = v[nth - 1].second - (re % 4);
		v[nth - 1].second = temp < 0 ? temp + 4 : temp;
		break;
	case 'R':
		temp = v[nth - 1].second + (re % 4);
		v[nth - 1].second = temp > 3 ? temp - 4 : temp;
		break;
	case 'F':
		for (int r = 0; r < re; r++) {
			int x = v[nth - 1].first.first;
			int y = v[nth - 1].first.second;
			int d = v[nth - 1].second;
			cout << x << " " << y << " " << d << endl;
			int nx = x + dx[d];
			int ny = y + dy[d];
			cout << nth << " " << nx << " " << ny << endl;
			if (1 <= nx && nx <= w && 1 <= ny && ny <= h) {
				if (map[ny][nx] != 0) {
					s += "Robot ";
					s += to_string(nth);
					s += " crashes into robot ";
					first = false;
					int n = map[ny][nx];
					s += to_string(n);
					return;
				}
				v[nth - 1].first.first = nx;
				v[nth - 1].first.second = ny;
				map[y][x] = 0;
				map[ny][nx] = nth;
			}
			else{
				s += "Robot ";
				s += to_string(nth);
				s += " crashes into the wall";
				first = false;
				return;
			}
		}
	}
}
int main()
{
	int command;
	int robots;
	cin >> h >> w;
	cin >> robots >> command;

	memset(map, 0, sizeof(map));

	int x, y, pos;
	char dir;
	for (int i = 0; i < robots; i++) {
		cin >> y >> x >> dir;
		switch (dir) {
		case 'N': pos = 0; break;
		case 'E': pos = 1; break;
		case 'S': pos = 2; break;
		case 'W': pos = 3; break;
		}
		map[y][x] = i + 1;
		v.push_back({ {x,y},pos });
	}

	for (int i = 0; i < command; i++) {
		cin >> x >> dir >> y;
		robot(x, dir, y);
	}
	if (first)
		cout << "OK" << endl;
	else
		cout << s << endl;
}