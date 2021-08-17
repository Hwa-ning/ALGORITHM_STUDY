#include <string>
#include <vector>

using namespace std;

string solution(string new_id) {
    string answer = "";
    // 1�ܰ�
    for (int i = 0; i < new_id.size(); i++)
        if ('A' <= new_id[i] && new_id[i] <= 'Z')
            answer[i] += new_id[i] - 'A' + 'a';
        else
            answer[i] += new_id[i];

    // 2�ܰ�
    string temp = "";
    for (int i = 0; i < answer.size(); i++) 
        if ('a' <= answer[i] && answer[i] <= 'z' || '0' <= answer[i] && answer[i] <= '9' || answer[i] == '-' || answer[i] == '.' || answer[i] == '_')
            temp += answer[i];
    
    answer = temp;
    temp = "";

    // 3�ܰ�
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
    answer = temp;

    // 4�ܰ�
    if (answer.front() == '.')
        answer = answer.substr(1);
    if (answer.back() == '.')
        answer.pop_back();

    // 5�ܰ�
    if (answer.empty())
        answer += "a";

    // 6�ܰ�
    if (answer.size() >= 16) 
        answer = answer.substr(0, 15);
    if (answer.back() == '.')
        answer.pop_back();

    // 7�ܰ�
    while (answer.size() <= 2) 
        answer += answer.back();

    return answer;
}