# 2020 KAKAO 인턴십 코딩테스트 1. 키패드 누르기

## 작성자 : Hwa-ning

## [문제 링크](https://programmers.co.kr/learn/courses/30/lessons/67256)

<br/>

### <풀이>

문제를 읽고 나는 어떻게 누르는가 고민을 해본 단순하면서 재밌는 구현 문제였다. 풀고 보니 num_loc 함수 자체가 너무 비효율적인 것 같다.
<br>
좌표와 관련된 모든 변수는 pair<int, int>를 활용했다. pair의 first에는 x좌표가 second에는 y좌표의 값을 저장함<br>
 - pair<int, int> num_loc(int num) 함수
   현재 눌러야 하는 숫자(num)에 해당하는 좌표 값을 return 해주는 함수

 - move(int num, string hand) 함수
   현재 눌러야하는 숫자(num)과 어느손잡이인지(hand)에 따라 현재 손의 좌표를 눌러야 하는 숫자로 이동시키고 결과값 저장을 위해 움직인 손에 해당하는 문자("L" or "R") return 해주는 함수

   move 함수는 크게 3가지의 경우로 나뉨.
  1. 1,4,7 인 경우 왼손으로 키패드를 누르므로 현재 왼손의 좌표를 해당 숫자로 이동하고 return "L"
  2. 3,6,9 인 경우 오른손으로 키패드를 누르므로 현재 오른손의 좌표를 해당 숫자로 이동하고 return "R"
  3. 2,5,8,0 인 경우 왼손으로 누를지 오른손으로 누를지 모르므로 해당 숫자에서 왼손과 오른손의 좌표 차이를 계산한다.<br>
    - 어느 한 손이 더 가깝다면 해당 손의 좌표를 해당 숫자로 이동하고 return 해당손("L" or "R")<br>
    - 거리가 같다면 어느 손잡이인지에 따라 결정 해당 손의 좌표를 해당숫자로 이동하고 return 해당손("L" or "R")

### <코드>

```C++
#include <string>
#include <vector>
#include <cmath>

using namespace std;

pair<int, int> left = { 0,3 };
pair<int, int> right = { 2,3 };
pair<int, int> nowNum_loc = { 5,5 };

pair<int, int> num_loc(int num) {
    if (num == 0)
        return { 1,3 };
    else
        return { (num - 1) % 3,(num - 1) / 3 };
}
string solution(vector<int> numbers, string hand) {
    string answer = "";
    for (int i = 0; i < numbers.size(); i++) {
        int num = numbers[i];
        nowNum_loc = num_loc(num);
        if (num % 3 == 1) {
            left = nowNum_loc;
            answer.append("L");
        }
        else if (num != 0 && num % 3 == 0) {
            right = nowNum_loc;
            answer.append("R");
        }
        else {
            int left_dist = abs(left.first - nowNum_loc.first) + abs(left.second - nowNum_loc.second);
            int right_dist = abs(right.first - nowNum_loc.first) + abs(right.second - nowNum_loc.second);
            if (left_dist == right_dist) {
                if (hand == "left") {
                    left = nowNum_loc;
                    answer.append("L");
                }
                else {
                    right = nowNum_loc;
                    answer.append("R");
                }
            }
            else {
                if (left_dist > right_dist) {
                    right = nowNum_loc;
                    answer.append("R");
                }
                else {
                    left = nowNum_loc;
                    answer.append("L");
                }
            }
        }
    }
    return answer;
}
```
