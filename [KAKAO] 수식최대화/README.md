# 2020 KAKAO 인턴십 코딩테스트 2. 수식최대화

## 작성자 : Hwa-ning

## [문제 링크](https://programmers.co.kr/learn/courses/30/lessons/67257)

<br/>

### <풀이>

문자열을 활용하여 수식 계산을 해야하는 문제, 처음엔 후위표현식(postfix)로 변경하고 스택에 넣는 식으로 풀이를 해야하나 생각했지만 vector를 활용하여 연산자와 수를 잘 이용하여 중위 표기식으로 최대한 사람에 가깝에 풀이해도 해결할 수 있을 것 같다는 생각에 내방식대로 풀이하게 되었다. 글로 표현하려니 다른 사람이 이해하기 어려울 것 같아 노트 필기를 첨부함

1. 문자열을 [0, length) 까지 순회하면서 숫자는 vector\<long long>num, 연산자는 vector\<char>op에 저장해두자. <br>(실행할때 마다 tokenizing하는 불필요한 시간을 줄이기 위해)
2. next_permutation으로 vector\<char>v_perm의 \* / + / - 의 순서를 바꿔준다. 연산자 우선순위를 위해 vector에 저장 (index 0부터 연산 실행)
3. 저장해둔 vector\<long long>num을 v_num, vector\<char>op를 v_op에 각각 복사한다.
4. 이중 for문을 활용하는데 i는 v_perm에서 현재 연산하려는 연산자. i:[0, 3)<br>
   j는 연산자를 저장해두고 있는 v_op의 몇번째 index인지로 사용된다. j:[0, v_op.size() )<br> 현재 v_perm[i]와 v_op[j]가 같다면(현재 우선순위에 해당하는 연산자라면) v_num[j]와 v_num[j+1]을 v_op[j]에 해당하는 연산을 실행하여 v_num[j+1]에 저장한다.
5. 4.에서 선택된 j번째 index는 연산이 끝나 더이상 필요없는 index이므로 vector\<int>deleteV에 index값을 저장해둔 뒤 해당 i번째 연산자에 대한 연산이 끝이 난다면 deleteV에 저장되있던 index 값들을 v_num과 v_op에서 erase해주자 이때 vector에 erase를 하면서 뒤에있던 index들이 1씩 shift되므로 count라는 변수를 사용해서 shift되는 값을 고려하여 erase해주자!<br>
6. 모든 연산이 끝났을때 v_num[0]만이 남게되고 해당 연산의 결과값이 된다.

### <첨부>

100-200*300-500+20일 때 * > + > - 연산을 하는 과정<br>
<span style="background:blue;color:white">파란색</span> : 현재 주목해야하는 값<br>
<span style="background:green;color:white">초록색</span> : 삭제 예정인 값<br>
<img src = "https://user-images.githubusercontent.com/69469529/118237409-447b5f80-b4d2-11eb-9665-3b8c10fe5381.JPG" width="400" height="400">

1. i가 0이므로 현재 v_perm의 index 0이 *이므로 *에 해당하는 연산을 실행할 차례
2. v*op의 index 1이 *이므로 v*num의 index 1과 index 2에 * 연산을 실행한다.
3. 2.에서 연산의 결과를 index 2에 저장해두고 v_num과 v_op의 각 index 1은 연산을 실행한 값이므로 연산이 끝난 후 삭제하기 위해 deleteV에 index값인 1을 push_back하여 저장.
4. 더 이상 _ 연산이 없으므로 _ 연산이 이뤄진 값들의 삭제를 실행하는 과정<br> 1번째 v_num과 v_op에서 index 1을 erase하고 그에 맞게 shift된 모습

<img src = "https://user-images.githubusercontent.com/69469529/118237421-47765000-b4d2-11eb-9f98-f27b8952cf03.JPG" width="400" height="400">

1. i가 1이므로 현재 v_perm의 index 1이 +이므로 +에 해당하는 연산을 실행할 차례
2. v_op의 index 2가 +이므로 v_num의 index 2와 index 3에 + 연산을 실행한다.
3. 2.에서 연산의 결과를 index 3에 저장해두고 v_num과 v_op의 각 index 2는 연산을 실행한 값이므로 연산이 끝난 후 삭제하기 위해 deleteV에 index값인 2를 push_back하여 저장.
4. 더 이상 + 연산이 없으므로 + 연산이 이뤄진 값들의 삭제를 실행하는 과정<br> 2번째 v_num과 v_op에서 index 2를 erase하고 그에 맞게 shift된 모습

<img src = "https://user-images.githubusercontent.com/69469529/118237426-49401380-b4d2-11eb-85dc-02e6c66f75bc.JPG" width="400" height="400">

1. i가 2이므로 현재 v_perm의 index 2이 -이므로 -에 해당하는 연산을 실행할 차례
2. v_op의 index 0이 -이므로 v_num의 index 0과 index 1에 - 연산을 실행한다.
3. (1) 연산의 결과를 index 1에 저장해두고 v_num과 v_op의 각 index 0은 연산을 실행한 값이므로 연산이 끝난 후 삭제하기 위해 deleteV에 index값인 0을 push_back하여 저장.<br>
   (2) v_op의 index 1이 -이므로 v_num의 index 1과 index 2에 - 연산을 실행한다.
4. 3.(2)에서 연산의 결과를 index 2에 저장해두고 v_num과 v_op의 각 index 1은 연산을 실행한 값이므로 연산이 끝난 후 삭제하기 위해 deleteV에 index값인 1을 push_back하여 저장.
5. 더 이상 + 연산이 없으므로 + 연산이 이뤄진 값들의 삭제를 실행하는 과정<br> 2번째 v_num과 v_op에서 index 2를 erase하고 그에 맞게 shift된 모습

### <코드>

```C++
#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

long long calc(long long num1, long long num2, char op)
{
    switch (op){
    case '*':
        return  num1 * num2;
    case '+':
        return  num1 + num2;
    case '-':
        return  num1 - num2;
    }
}

long long solution(string expression) {
    long long answer = 0;
    int count = 0;
    vector<char> v_perm{ '*','+','-' };
    vector<long long>num;
    vector<char>op;
    long long temp = 0;
    for (int idx = 0; idx < expression.length(); idx++) {
        if ('0' <= expression[idx] && expression[idx] <= '9') {
            temp *= 10;
            temp += expression[idx] - '0';
        }
        else {
            num.push_back(temp);
            op.push_back(expression[idx]);
            temp = 0;
        }
    }
    num.push_back(temp);
    do {
        vector<long long>v_num = num;
        vector<char>v_op = op;
        for (int i = 0; i < 3; i++) {
            vector<int>deleteV;
            for (int j = 0; j < v_op.size(); j++) {
                if (v_perm[i] == v_op[j]) {
                    v_num[j+1] = calc(v_num[j], v_num[j + 1], v_perm[i]);
                    deleteV.push_back(j);
                }
            }
            int count = 0;
            for (int j = 0; j < deleteV.size(); j++) {
                v_num.erase(v_num.begin() + (deleteV[j] - count));
                v_op.erase(v_op.begin() + (deleteV[j] - count));
                count++;
            }
        }
        answer = max(answer, abs(v_num[0]));
    } while (next_permutation(v_perm.begin(), v_perm.end()));
    return answer;
}
```
