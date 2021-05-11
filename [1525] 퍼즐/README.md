# 1525. 퍼즐

## [문제 링크](https://www.acmicpc.net/problem/1525)

<br/>

### <풀이>

BFS와 3\*3 배열의 퍼즐판을 string으로 생각하고 접근했다. 처음에는 단순히 visited를 배열로 만들어서 선언하려고 했는데 이는 너무쓸데없는 메모리 낭비가 될 것이다. queue에 값을 넣어 줄 때마다 set에 insert를 해주고 find를 사용하여 visited와 같은 역할을 하도록 설계했다. 퍼즐판에서 0과 움직일 수 있는 칸의 값을 swap하여 queue에 넣어 BFS를 진행하도록 설계했다.

### 배열 index / (x,y)쌍

| [0]/(0,0) | [1]/(1,0) | [2]/(2,0) |
| --------- | --------- | --------- |
| [3]/(0,1) | [4]/(1,1) | [5]/(2,1) |
| [6]/(0,2) | [7]/(1,2) | [8]/(2,2) |

string의 find를 사용하여 0의 index 값을 찾아<br>
x = index % 3 <br>
y = index / 3 <br>
위 연산을 통해 x,y값을 찾아주고 상하좌우를 이동한 next_x와 next_y값을 계산한다. 원래 [0의 index]와 [next_x+next_y\*3 index]을 swap해주고 swap한 값이 visited(set)에 존재하지 않는다면 queue에 insert하여 BFS를 진행한다.

### 예제1

| 1   | 0   | 3   |
| --- | --- | --- |
| 4   | 2   | 5   |
| 7   | 8   | 6   |

위의 예제1 에서는 현재의 퍼즐판을 string으로 표현하면 103425786이 된다. string의 find를 사용하여 0의 index 값을 찾으면 1이 나올 것이고 x=1%3, y=1/3 연산을 통해 <U>x=1, y=0</U>의 값이 나오게 됨. 아래는 첫단계의 퍼즐 이동이다.

</br>

#### 상 (x+0, y-1) => (1,-1)

0<=x<=2 && 0<=y<=2가 만족해야하므로 불가능함

</br>

#### 하 (x+0, y+1) => (1,1)

1+1\*3=4
| 1 | 2 | 3 |
| --- | --- | --- |
| 4 | 0 | 5 |
| 7 | 8 | 6 |

2 [4] , 0 [1] swap / 103425786 -> 123405786

#### 좌 (x-1, y+0) => (0,0)

0+0\*3=0
| 0 | 1 | 3 |
| --- | --- | --- |
| 4 | 2 | 5 |
| 7 | 8 | 6 |

1 [0] , 0 [1] swap / 103425786 -> 013425786

#### 우 (x+1, y+0) => (2,0)

2+0\*3=2
| 1 | 3 | 0 |
| --- | --- | --- |
| 4 | 2 | 5 |
| 7 | 8 | 6 |

3 [2] , 0 [1] swap / 103425786 -> 130425786
<<<<<<< HEAD

```C++
#include <iostream>
#include <queue>
#include <set>
#include <string>

using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int solve(string init)
{
	queue<pair<string,int> >q;
	set<string>visited;

	q.push({ init, 0 });
	visited.insert(init);

	while (!q.empty()) {
		string now = q.front().first;
		int cnt = q.front().second;
		q.pop();

		if (now == "123456780")
			return cnt;

		int idx = now.find('0');
		int x = idx % 3;
		int y = idx / 3;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 > nx || 0 > ny || nx >= 3 || ny >= 3)
				continue;

			string next = now;
			swap(next[idx], next[nx + ny * 3]);
			if (visited.find(next) == visited.end()) {
				visited.insert(next);
				q.push({ next, cnt + 1 });
			}
		}
	}
	return -1;
}
int main()
{
	string init;
	char s;
	for (int i = 0; i < 9; i++){
		cin >> s;
		init += s;
	}
	cout << solve(init) << endl;
	return 0;
}
```
