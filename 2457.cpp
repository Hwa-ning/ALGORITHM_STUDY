#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int> >v;
int main()
{
    int N;
    int input[4];
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++)
            cin >> input[j];

        if (input[0] == 1 || input[0] == 2){
            input[0] = 3;
            input[1] = 1;
        }
        v.push_back({ input[0] * 100 + input[1], input[2] * 100 + input[3]});
    }
    sort(v.begin(), v.end());
    
    /*for (int i = 0; i < N; i++)
        cout << v[i].first << " ~ " << v[i].second << endl;*/

    int nowEnd = 301;
    int today = 301;
    int idx = 0;
    int result = 0;
    while (today < 1201) {
        for (int i = idx; i < N; i++) {
            if (v[i].first > today) break;
            if (v[i].second > nowEnd) {
                nowEnd = v[i].second;
                idx = i + 1;
            }
        }
        if (nowEnd == today) {
            result = 0;
            break;
        } else {
            today = nowEnd;
            result++;
        }
    }
    cout << result << endl;
    return 0;
}