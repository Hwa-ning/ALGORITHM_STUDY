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
    // 모두정상으로
    v[lan][pos][car][food].push_back(score);
    // 1개씩 - 인 경우
    v[0][pos][car][food].push_back(score);
    v[lan][0][car][food].push_back(score);
    v[lan][pos][0][food].push_back(score);
    v[lan][pos][car][0].push_back(score);
    // 2개씩 - 인 경우
    v[0][0][car][food].push_back(score);
    v[0][pos][0][food].push_back(score);
    v[0][pos][car][0].push_back(score);
    v[lan][0][0][food].push_back(score);
    v[lan][0][car][0].push_back(score);
    v[lan][pos][0][0].push_back(score);
    // 3개씩 - 인 경우
    v[0][0][0][food].push_back(score);
    v[0][0][car][0].push_back(score);
    v[0][pos][0][0].push_back(score);
    v[lan][0][0][0].push_back(score);
    // 4개 - 인 경우
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