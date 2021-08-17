# 2021 KAKAO BLIND RECRUITMENT 2. 메뉴 리뉴얼

## 작성자 : Hwa-ning

## [문제 링크](https://programmers.co.kr/learn/courses/30/lessons/72411)

<br/>

### <풀이>

    memset을 이용한 초기화가 잘 되지않아 시간이 조금 걸렸다. map을 활용한 조합 문제, 막 어려운 문제는 아니였지만 코드의 효율성이 조금 떨어지는 것 같다. 크게 2가지 함수를 작성해서 풀이했다.

1. insertOrder() 함수
   모든 경우의 조합을 구하는 함수로 현재 string이 map에 이미 존재한다면 value++, 존재하지 않는다면 map에 insert({key,value})

2. findCourse() 함수
   입력으로 받은 course에 해당하는 조합들을 확인하기 위한 함수로 map을 iterator로 순회하는데 argument로 전달받은 course와 일치하는 길이의 key값인 string을 찾아 { key,value } 쌍을 vector v에 저장해두고 순회가 완료된다면 이를 sort하여 return

### <더 공부해야할 점>

    bool* visited 를 new bool[]로 그때 그때 할당해서 사용해주었는데 memset이 어째서인지 visited 배열 전체를 초기화시키지 못하고 마지막 index까지 초기화시키지 못해서 +1로 해주어도 자꾸 초기화를 전부하지 못해서 다음과 같이 +2를 해주었다.
        memset(visited, false, sizeof(visited) + 2);
    이 부분은 memset이나 할당한 배열에 대해서 조금 더 공부해야 알 수 있는 부분인 것 같다.

### <코드>

```C++
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

map<string, int> m;
vector<string> answer;
bool* visited;

void insertOrder(string order, string now, int now_idx) {
    if (now_idx >= order.size())
        return;

    if (now.size() >= 2) {
        if (m.find(now) != m.end())
            m[now]++;
        else
            m.insert({ now,1 });
    }
    for (int i = now_idx; i < order.size(); i++) {
        if (!visited[i]) {
            visited[i] = true;
            insertOrder(order, now + order[i], i);
            visited[i] = false;
        }
    }
}

void findCourse(int course) {
    vector<pair<int, string> >v;
    map<string, int>::iterator it;
    for (it = m.begin(); it != m.end(); it++) {
        if (it->first.size() == course) {
            v.push_back({ it->second, it->first });
        }
    }
    if (v.empty())
        return;
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());

    int v_first = v[0].first;
    if (v_first>=2) {
        answer.push_back(v[0].second);
    }
    else
        return;
    for (int i = 1; i < v.size(); i++) {
        if (v[i].first == v_first)
            answer.push_back(v[i].second);
        else
            return;
    }

}
vector<string> solution(vector<string> orders, vector<int> course) {
    for (int i = 0; i < orders.size(); i++) {
        visited = new bool[orders[i].size()];
        memset(visited, false, sizeof(visited) + 2);
        sort(orders[i].begin(), orders[i].end());
        for (int j = 0; j < orders[i].size(); j++) {
            visited[j] = true;
            insertOrder(orders[i], orders[i].substr(j, 1), j);
            visited[j] = false;
        }
    }
    for (int i = 0; i < course.size(); i++)
        findCourse(course[i]);

    sort(answer.begin(), answer.end());
    return answer;
}
```
