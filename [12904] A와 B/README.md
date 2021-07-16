# 12904. A와 B

## 작성자 : Hwa-ning

## [문제 링크](https://www.acmicpc.net/problem/12904)

<br/>

### <풀이>

그닥 어렵지 않은 문자열 문제, 문자열에 조금 약한 것 같아 문자열 문제를 풀려고 잡았는데 너무 쉬운 문제를 잡은 것 같다고 생각했는데 맨처음 아무생각없이 BFS를 써서 모든 경우를 돌렸더니 당연하게 메모리초과가 났고 잠시 생각해보니 모든 경우를 할 필요가 없다는걸 깨달았다.<br>
<br>
*** S -> T로가는 경우는 경우의 수가 너무 많다. 재귀를 사용하여 T -> S로 문자열을 점차 줄여나가자.<br>

1. A로 끝나는 경우 substr(0,length-1)의 문자열로 재귀 함수로 넘김
2. B로 끝나는 경우 substr(0,length-1)의 문자열을 reverse로 뒤집어준 다음 재귀 함수로 넘김
3. 1 or 2를 반복하면서 문자열의 길이가 S와 같아진다면 S와 비교하여 일치한다면 1, 다르다면 0을 return

### <코드>

```C++
#include <iostream>
#include <algorithm>

using namespace std;

string origin, dest;
int solve(string str){
	if (str.length() == origin.length()) {
		if (str.compare(origin) == 0)
			return 1;
		else
			return 0;
	}
	int nowLength = str.length();
	string temp = str.substr(0, nowLength - 1);
	if (str[nowLength - 1] == 'A') 
		solve(temp);
	else {
		reverse(temp.begin(), temp.end());
		solve(temp);
	}
}
int main()
{
	cin >> origin >> dest;
	cout << solve(dest) << endl;
}
```
