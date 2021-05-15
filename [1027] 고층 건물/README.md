# 1027. 고층 건물

## 작성자 : Hwa-ning

## [문제 링크](https://www.acmicpc.net/problem/1027)

<br/>

### <풀이>

왼쪽, 오른쪽을 보며 한 건물의 index를 x로 해당 index에 저장된 값(높이)를 y로 잡고 1차 방정식을 구한 후 해당 칸이 방정식에서 나와야 하는 값과 같거나 크다면 그 건물을 볼 수 없는 것을 이용하여 풀이했다.<br>
풀이하고 나서 다른 사람들의 풀이를 보니 단순히 기울기만으로도 계산을 할 수 있다는걸 알게됐다.

1. 현재 건물에서 확인하려는 건물까지의 식을 y=ax+b의 방정식에서 a와 b값을 구한다.<br>
   a : 기울기 (y증가량 / x증가량)<br>
   a = (확인하려는 건물의 높이 - 현재 건물의 높이) / (확인하려는 건물의 index)-(현재 건물의 index)<br>
   b : y - ax <br>
   b = 현재 건물의 높이 - (기울기 a \* 현재 건물의 index)<br>
2. 현재 건물과 확인하려는 건물 사이의 건물들의 높이를 확인하면서 방정식에 대입해서 나온 값보다 그 건물의 높이가 같거나 더 크다면 건물이 가려져서 보이지 않는 것이므로 해당 건물은 볼 수 없다.<br>
   확인하려는 건물까지의 건물들의 높이가 모두 작다면 해당 건물은 볼 수 있는 건물이 된다.
3. 모든 건물들의 왼쪽, 오른쪽을 확인하여 가장 많은 건물을 볼 수 있는 값을 저장해두자.

### <예시>

<img src="https://user-images.githubusercontent.com/69469529/118361191-280c1f80-b5c5-11eb-9618-34957a0d0cf5.JPG" width="700" height = "400"><br>
만약 현재 건물 12에서 건물 6이 보이는지 확인하려고 할 때,<br>
건물 12는 높이가 7이고 (x:12,y:7) 건물 6은 높이가 3이므로 (x:6,y:3)<br>
이를 y = ax + b 의 식으로 바꾸게 된다면 y = 2/3x -1 의 식이 나오게 된다. 이제, 건물 6과 12 사이의 건물들을 이 방정식에 대입을 해보자.<br>
건물 8에서 y = 2/3\*8 - 1 = 4.xxx 의 값이 나오게 되는데 건물 8의 높이는 6으로 y= 2/3x - 1 의 식보다 큰 높이를 가지므로 건물 8에 가려져 건물 6을 볼 수 없다.

### <코드>

```C++
#include <iostream>
#include <algorithm>

using namespace std;

int N;
int building[51];
int result = 0;
void CheckBuilding(int idx)
{
	int count = 0;
	for (int left = idx - 1; left > 0; --left) {
		double a = (double)(building[left] - building[idx]) / (double)(left - idx);
		double b = (double)(building[idx]) - (a * (double)idx);
		int temp_left = idx - 1;
		for(; temp_left > left; --temp_left) {
			if (a * temp_left + b <= building[temp_left])
				break;
		}
		if (temp_left == left)
			count++;
	}

	for (int right = idx + 1; right <= N; right++) {
		double a = (double)(building[right] - building[idx]) / (double)(right - idx);
		double b = (double)(building[idx]) - (a * (double)idx);
		int temp_right = idx+1;
		for (;temp_right < right; ++temp_right) {
			if (a * temp_right + b <= building[temp_right])
				break;
		}
		if (temp_right == right)
			count++;
	}
	result = max(result, count);
}
int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> building[i];

	for (int i = 1; i <= N; i++)
		CheckBuilding(i);

	cout << result << endl;
}
```
