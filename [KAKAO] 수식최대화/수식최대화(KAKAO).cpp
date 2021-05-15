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
int main()
{
    string input;
    cin >> input;
    cout << solution(input) << endl;
}