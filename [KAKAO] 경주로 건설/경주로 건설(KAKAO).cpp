#include <string>
#include <vector>
#include <queue>
#include <cstring>
#define MAX 987654321
using namespace std;

struct node {
    int x;
    int y;
    int cost;
    int exDir;
};

int solution(vector<vector<int>> board) {
    int answer = MAX;
    int DP[25][25];
    int N = board[0].size();
    int dx[4] = { 0,1,0,-1 };
    int dy[4] = { 1,0,-1,0 };
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            DP[i][j] = MAX;
    queue<node>q;
    if (!board[1][0]) {
        q.push(node{ 1, 0, 100, 1 });
        DP[1][0] = 100;
    }
    if (!board[0][1]) {
        q.push(node{0, 1, 100, 0});
        DP[0][1] = 100;
    }
    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int cost = q.front().cost;
        int exDir = q.front().exDir;
        q.pop();
        if (cost >= answer)
            continue;

        if (x == N - 1 && y == N - 1) {
            answer = min(answer, cost);
            continue;
        }

        for (int i = 0; i < 4; i++) {
            if ((exDir + 2) % 4 == i)
                continue;
            int nx = x + dx[i];
            int ny = y + dy[i];
            int ncost = (exDir == i ? cost + 100 : cost + 600);

            if (0 > nx || nx >= N || 0 > ny || ny >= N || board[nx][ny] || DP[nx][ny] < ncost)
                continue;

            q.push(node{ nx, ny, ncost, i });
            DP[nx][ny] = ncost;
        }
    }
    return answer;
}

// 처음 생각못한것 1 0, 0 1이 벽인 경우
// 두번째 생각못한것