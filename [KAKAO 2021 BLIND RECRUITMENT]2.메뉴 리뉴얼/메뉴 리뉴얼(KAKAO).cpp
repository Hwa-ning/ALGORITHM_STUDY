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
    if (v_first >= 2) {
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