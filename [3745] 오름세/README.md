# 3745. 오름세

## 작성자 : Hwa-ning

## [문제 링크](https://www.acmicpc.net/problem/3745)

<br/>

### <풀이>

LIS(최장 증가 수열)문젠데 DP 방식도 기억이 가물가물했는데 DP 방식으로는 도저히 해결하지 못할 것 같았고 LIS 알고리즘에 대해 공부를 좀 하게됐다. DP방식 O(N^2)보다 빠른 이분탐색 O(N log N)을 사용하는 방법이 있다는걸 알게됐다. DP 방식도 처음에 배웠을 땐 놀라웠는데 이것도 동작방식이 기발하다...<br>

[링크](https://jason9319.tistory.com/113)를 보고 이분탐색을 사용하는 알고리즘을 이해함<br>

vector를 선언하여 현재 벡터의 가장 끝에 값보다 크다면 push_back하여 맨뒤로 삽입을 해주고 작거나 같은 경우엔 lower_bound()를 사용하여 해당 index의 값 방금 입력한 값으로 바꿔주자.<br>

** lower_bound는 찾고자하는 값과 같거나 그 이상인 값이 처음 나타나는 위치를 return<br>
** 이렇게 lower_bound()하여 해당 index값을 변경하게 되면 해당 위치의 값이 작아지므로 최장 증가 수열 뒤에 붙을 수 있는 값이 더 작아지게 된다!<br>

또, 이 문제는 종료 조건이 없어서 입력을 while()문의 조건에 넣어줘야했다.<br>
문제 조건에 input이 자연수만 나오기 때문에 vector에 -1을 미리 입력(.back()을 사용하여 현재 가장 큰 값을 확인하기 위함)

- 1 2 6 4 5 3을 입력하는 예시
  1. input : 1 / 현재 가장 큰 값 -1 이므로 push_back()
  - 현재 vector의 상태 : -1 1
  2. input : 2 / 현재 가장 큰 값 1이므로 push_back()
  - 현재 vector의 상태 : -1 1 2
  3. input : 6 / 현재 가장 큰 값 2이므로 push_back()
  - 현재 vector의 상태 : -1 1 2 6
  4. input : 4 / 현재 가장 큰 값 6이므로 lower_bound() 위치를 4로 변경
  - 현재 vector의 상태 : -1 1 2 4
  5. input : 5 / 현재 가장 큰 값 4이므로 push_back()
  - 현재 vector의 상태 : -1 1 2 4 5
  6. input : 3 / 현재 가장 큰 값 5이므로 lower_bound() 위치를 3로 변경
  - 현재 vector의 상태 : -1 1 2 3 5

### <코드>

```C++
#include <iostream>
#include <vector>

using namespace std;

vector<int> v_lis;

int main()
{
	int input, N;
	while (cin >> N) {
		int ans = 0;
		v_lis.clear();
		v_lis.push_back(-1);
		for (int i = 0; i < N; i++) {
			cin >> input;
			if (v_lis.back() < input) {
				v_lis.push_back(input);
				++ans;
			}
			else {
				auto it = lower_bound(v_lis.begin(), v_lis.end(), input);
				*it = input;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```
