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
int cal_dist(char LorR) {
    if (LorR == 'L')
        return abs(left.first - nowNum_loc.first) + abs(left.second - nowNum_loc.second);
    else
        return abs(right.first - nowNum_loc.first) + abs(right.second - nowNum_loc.second);
}
string move(int num, string hand) {
    nowNum_loc = num_loc(num);
    switch (num) {
    case 1:
    case 4:
    case 7:
        left = nowNum_loc;
        return "L";
    case 3:
    case 6:
    case 9:
        right = nowNum_loc;
        return "R";
    }
    int left_dist = cal_dist('L');
    int right_dist = cal_dist('R');
    if (left_dist == right_dist) {
        if (hand == "left") {
            left = nowNum_loc;
            return "L";
        }
        else {
            right = nowNum_loc;
            return "R";
        }
    }
    else {
        if (left_dist > right_dist) {
            right = nowNum_loc;
            return "R";
        }
        else {
            left = nowNum_loc;
            return "L";
        }
    }
}
string solution(vector<int> numbers, string hand) {
    string answer = "";
    for (int i = 0; i < numbers.size(); i++)
        answer.append(move(numbers[i], hand));
    return answer;
}