# 4577. 소코반

## 작성자 : Hwa-ning

## [문제 링크](https://www.acmicpc.net/problem/4577)

<br/>

### <풀이>

어릴 때 피처폰으로 많이하던 소코반을 구현하는 문제, 처음에 게임이 완료되면 더 이상 움직이지 않고 종료되어야하는데 계속 움직이도록 구현하는 코드를 작성해서 코드가 좀 지저분해졌고 완벽하게 풀이하는데 시간도 오래걸렸다. 늘 문제를 처음부터 잘 읽는 습관을 가지자.

<br/>

1. move() : 캐릭터를 옮기면서 박스의 위치를 옮겨주자.<br>
처음 입력을 받을 때 '#','.','b'으로만 남겨두도록하고 게임이 종료됐을 때 'w','+','W','B'로 바꿔주도록 구현하여 move()는 그렇게 많이 고려할게 없다.<br>
- 캐릭터가 이동하려는 방향이 벽이거나 맵의 범위를 초과하는 경우는 아무런 변화없이 다음 명령으로 넘어간다.
<br>
- 캐릭터가 이동하려는 방향에 박스('b')가 있는 경우
  - 박스가 이동하려는 방향이 빈칸이라면, 박스와 캐릭터를 한칸씩 이동한다.<br>(이때 게임이 종료될 수 있으므로 check()로 게임이 종료되었는지 확인한다.)
  - 박스가 이동하려는 방향이 박스거나 벽이 있는 경우, 움직일 수 없으므로 다음 명령으로 넘어간다.

2. check() : 게임이 종료되었는지 확인하자. <br>
vector에 담아둔 목표점들을 확인하며 해당 좌표들이 빈칸이거나 캐릭터의 현재 좌표라면 게임이 종료되지 않았으므로 return<br>
return 되지 않았다면 모든 박스('b')들이 목표점('+')위에 존재하는 것이므로 output()실행

3. ouput() : 게임의 결과를 출력하자. <br>
게임이 종료되었으므로 현재 게임의 map을 출력하기 위해 vector에 담아둔 목표점들을 각각 'w' -> 'W' / 'b' -> 'B'로 / '.' -> '+'로 바꿔주고 이때, '+'나 'W'로 바꾼 좌표가 있다면 게임이 종료되지 않았으므로 bool형 finish 변수를 false로 바꿔주어 Game incomplete를 출력한다.

### <코드>

```C++
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
```
