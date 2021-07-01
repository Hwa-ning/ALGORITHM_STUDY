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