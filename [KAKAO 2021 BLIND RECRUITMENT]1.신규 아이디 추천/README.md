# 2021 KAKAO BLIND RECRUITMENT 1. 신규 아이디 추천

## 작성자 : Hwa-ning

## [문제 링크](https://programmers.co.kr/learn/courses/30/lessons/72410)

<br/>

### <풀이>

    문자열을 활용한 구현 문제, 코드를 예쁘게 짜려고 하다 시간이 많이 걸렸는데 정작 코드가 예쁘지도 않다. 난이도는 쉬운편이고 단순 문자열 구현 문제, 7가지 단계에 유의하여 풀이해야한다.

- 1단계 : 대문자를 소문자로 치환<br>

```C++
    string answer = "";
    // 1단계
    for (int i = 0; i < new_id.size(); i++)
        if ('A' <= new_id[i] && new_id[i] <= 'Z')
            answer[i] += new_id[i] - 'A' + 'a';
        else
            answer[i] += new_id[i];
```

    'A'와 'Z' 사이라면 -'A' + 'a' 해주어 대문자를 소문자로 변경해주자.

- 2단계 : 알파벳 소문자, 숫자, 빼기(-), 밑줄(\_), 마침표(.)를 제외한 모든 문자를 제거

```C++
    for (int i = 0; i < answer.size(); i++)
        if ('a' <= answer[i] && answer[i] <= 'z' || '0' <= answer[i] && answer[i] <= '9' || answer[i] == '-' || answer[i] == '.' || answer[i] == '_')
            temp += answer[i];
```

    'a'와 'z'사이 or '-' or '.' or '\_'이라면 temp에 추가해주고 아니라면 제거해야하므로 아무런 작업없이 넘어가자.

- 3단계 : 마침표(.)가 2번 이상 연속된 부분을 하나의 마침표(.)로 치환

```C++
    for (int i = 0; i < answer.size(); i++) {
        if (answer[i] == '.') {
            int count = 1;
            while (answer[i+count] == '.')
                count++;
            if (count == 1)
                temp += '.';
            else {
                temp += '.';
                i += count - 1;
            }
        }
        else
            temp += answer[i];
    }
```

    문자열을 처음부터 확인하며 '.'이고 그 index부터 '.'이 아닐때까지 확인하고 '.'을 추가해주고 확인한 다음칸부터 index를 보면되므로 i += count - 1 해준다.

- 4단계 : 마침표(.)가 처음이나 끝에 위치한다면 제거

```C++
    if (answer.front() == '.')
        answer = answer.substr(1);
    if (answer.back() == '.')
        answer.pop_back();
```

    처음이 '.'이라면 substr을 활용하여 index 1부터 끝까지 문자열을 활용
    마지막이 '.'이라면 pop_back을 활용하여 마지막 index를 제거

- 5단계 : 빈 문자열이라면, new_id에 "a"를 대입

```C++
    if (answer.empty())
        answer += "a";
```

    빈 문자열이면 'a'를 추가해주자.

- 6단계 : new_id의 길이가 16자 이상이면, new_id의 첫 15개의 문자를 제외한 나머지 문자들을 모두 제거, 만약 제거 후 마침표(.)가 new_id의 끝에 위치한다면 끝에 위치한 마침표(.) 문자를 제거

```C++
    if (answer.size() >= 16)
        answer = answer.substr(0, 15);
    if (answer.back() == '.')
        answer.pop_back();
```

    substr을 활용하여 15개의 문자만 오도록하고 마지막 문자가 '.'인지 확인

- 7단계 : new_id의 길이가 2자 이하라면, new_id의 마지막 문자를 new_id의 길이가 3이 될 때까지 반복해서 끝에 추가

```C++
    while (answer.size() <= 2)
        answer += answer.back();
```

    while문을 사용하여 끝에 마지막 문자 추가
