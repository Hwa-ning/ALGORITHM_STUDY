# 2021 KAKAO BLIND RECRUITMENT 3. 메뉴 리뉴얼

## 작성자 : Hwa-ning

## [문제 링크](https://programmers.co.kr/learn/courses/30/lessons/72412)

<br/>

### <풀이>

    DB를 구현하는 듯한 문젠데 지원자 정보가 최대 100,000이고 query문이 최대 50,000인 문제로 정확도와 효율성을 보는 문제다.
    multimap을 사용해서 처음엔 string으로 key, 점수를 value로 저장하여 풀이했다가 효율성에서 실패해서 처음부터 다시 풀이했다.
    4차원 배열의 vector<int>를 만들어 점수를 저장해주고 이때, 저장할때 *16가지의 경우의 수*에 해당하는 vector에 점수를 저장한 후,
    모든 지원자 정보를 저장 후 sort하여 query문에 해당하는 조건을 찾는 방식으로 문제를 풀이했다.

<br>

    <왜 16가지 경우의 수인가?>
    언어 / 직군 / 경력 / 음식으로 총 4가지 종류의 변수가 존재하는데 이 때 query문에서 -이라는 해당 변수의 값을 고려하지 않는 query가 존재하여
    -이 0번 나오는 경우 1가지
    -이 1번 나오는 경우 4가지
    -이 2번 나오는 경우 6가지
    -이 3번 나오는 경우 4가지
    -이 4번 나오는 경우 1가지
    로 총 16가지의 경우의 수가 나오게 된다.

<br>

    <4차원 배열 vector의 구성>
    4차원 배열 vector에서 [language][position][career][food]로
    language(개발 언어)에서 cpp라면 1번지 / java라면 2번지 / python이라면 3번지
    position(직군)에서 backend라면 1번지 / frontend라면 2번지
    career(경력 여부)에서 junior라면 1번지 / senior라면 2번지
    food(소울 푸드)에서 chicken이라면 1번지 / pizza라면 2번지
    에 저장되며 -에 해당하는 고려하지 않는 값들은 각각의 0번지에 해당한다.

    예시로 "java and backend and junior and pizza 100" 라는 정보가 들어온다면
    java / backend / junior / pizza 이므로 [2][1][1][2]에 100이라는 값이 저장된다.
    그리고 나머지 15가지의 경우에 해당하는 vector에 100이라는 값이 저장될 것이다.

    ex) -이 1번나오는 경우들
    [0][1][1][2] ( - / backend / junior / pizza )
    [2][0][1][2] ( java / - / junior / pizza )
    [2][1][0][2] ( java / backend / - / pizza )
    [2][1][1][0] ( java / backend / junior / - )

1. string_int 함수
   위의 <4차원 배열 vector의 구성>에 해당하는 구성을 하기 위해 string을 각각 해당하는 int 값으로 변경하기 위한 함수

2. runQuery 함수
   string_int 함수를 사용하여 입력된 query에 해당하는 4차원 배열의 위치를 찾아 vector에서 입력받은 점수 이상인 사람을 lower_bound를 사용하여 계산하여 return

3. insertInfo 함수
   string_int 함수를 사용하여 지원자 정보에서 16가지의 경우의 수에 해당하는 4차원 배열의 점수를 삽입하는 함수

### <코드>

```C++
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<int>v[4][3][3][3];

vector<int>string_int(vector<string>token) {
    vector<int>res;

    if (token[0] == "cpp")
        res.push_back(1);
    else if (token[0] == "java")
        res.push_back(2);
    else if (token[0] == "python")
        res.push_back(3);
    else
        res.push_back(0);

    if (token[1] == "backend")
        res.push_back(1);
    else if (token[1] == "frontend")
        res.push_back(2);
    else
        res.push_back(0);

    if (token[2] == "junior")
        res.push_back(1);
    else if (token[2] == "senior")
        res.push_back(2);
    else
        res.push_back(0);

    if (token[3] == "chicken")
        res.push_back(1);
    else if (token[3] == "pizza")
        res.push_back(2);
    else
        res.push_back(0);

    return res;
}

void insertInfo(string input) {
    vector<string> str_token;
    string temp = "";
    for (char c : input) {
        if (c == ' ') {
            str_token.push_back(temp);
            temp = "";
        }
        else
            temp += c;
    }
    int score = stoi(temp);

    vector<int>int_token = string_int(str_token);

    int lan = int_token[0];
    int pos = int_token[1];
    int car = int_token[2];
    int food = int_token[3];
    // -이 0개인 경우
    v[lan][pos][car][food].push_back(score);
    // -이 1개인 경우
    v[0][pos][car][food].push_back(score);
    v[lan][0][car][food].push_back(score);
    v[lan][pos][0][food].push_back(score);
    v[lan][pos][car][0].push_back(score);
    // -이 2개인 경우
    v[0][0][car][food].push_back(score);
    v[0][pos][0][food].push_back(score);
    v[0][pos][car][0].push_back(score);
    v[lan][0][0][food].push_back(score);
    v[lan][0][car][0].push_back(score);
    v[lan][pos][0][0].push_back(score);
    // -이 3개인 경우
    v[0][0][0][food].push_back(score);
    v[0][0][car][0].push_back(score);
    v[0][pos][0][0].push_back(score);
    v[lan][0][0][0].push_back(score);
    // -이 4개인 경우
    v[0][0][0][0].push_back(score);
}

int runQuery(string input) {
    vector<string> str_token;
    string temp = "";
    for (char c : input) {
        if (c == ' ') {
            if (temp != "and")
                str_token.push_back(temp);
            temp = "";
        }
        else
            temp += c;
    }
    int score = stoi(temp);

    vector<int>int_token = string_int(str_token);

    int lan = int_token[0];
    int pos = int_token[1];
    int car = int_token[2];
    int food = int_token[3];

    return v[lan][pos][car][food].size() - (lower_bound(v[lan][pos][car][food].begin(), v[lan][pos][car][food].end(), score) - v[lan][pos][car][food].begin());
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;

    for (int i = 0; i < info.size(); i++)
        insertInfo(info[i]);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 3; l++)
                    sort(v[i][j][k][l].begin(), v[i][j][k][l].end());

    for (int i = 0; i < query.size(); i++)
        answer.push_back(runQuery(query[i]));

    return answer;
}
```
