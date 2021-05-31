# 1132. 합

## 작성자 : Hwa-ning

## [문제 링크](https://www.acmicpc.net/problem/1132)

<br/>

### <풀이>

Greedy 알고리즘과 문제에 대한 이해가 조금 필요한 문제, 처음엔 0에 대한 알파벳 처리에서 조금 헤맸다...

1. 알파벳의 계수 계산
   AAB/BAB라면 AAB : 100A + 10A +1B / BAB : 100B + 10A + 1B와 같이 모든 등장하는 알파벳에 대하여 계수를 계산해주자.

2. 앞서 계산된 계수가 가장 높은 알파벳부터 9~0 숫자값을 배정해주자.
   \*\*\*주의 : 이 때, 사용된 알파벳이 10개라면 맨 앞 숫자는 0이 될 수 없으므로 0이 되는 알파벳을 정해줘야 한다. 정렬하여 가장 작은 계수를 가진 알파벳부터 확인하며 0이 올 수 있는(첫글자로 등장하지 않은)가장 작은 계수의 알파벳을 골라 0을 배정해준다.

### <코드>

```C++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<long long, char> >arr;
bool first[10];
bool use[10];
int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < 10; i++)
		arr.push_back({ 0,'A' + i, });

	string input;

	for (int i = 0; i < N; i++) {
		cin >> input;
		first[input[0] - 'A'] = true;
		long long mulValue = 1;
		for (int j = input.size() - 1; j >= 0; j--) {
			use[input[j] - 'A'] = true;
			arr[input[j] - 'A'].first += mulValue;
			mulValue *= 10;
		}
	}

	int count_char = 0;
	for (int i = 0; i < 10; i++)
		if (use[i])
			count_char++;

	long long res = 0;
	if (count_char != 10) {
		sort(arr.begin(), arr.end());
		reverse(arr.begin(), arr.end());
		for (long long i = 0; i < count_char; i++)
			res += arr[i].first * (9 - i);
	}
	else {
		sort(arr.begin(), arr.end());
		int idx = 1;
		vector<pair<long long, char> >temp(10);
		for (int i = 0; i < 10; i++) {
			if (first[arr[i].second - 'A']) {
				temp[idx++] = arr[i];
			}
			else {
				temp[0] = arr[i];
				break;
			}
		}
		for (int i = idx; i < 10; i++)
			temp[i] = arr[i];

		for (long long i = 9; i >= 0; i--)
			res += temp[i].first * i;
	}
	cout << res << endl;
}
```
