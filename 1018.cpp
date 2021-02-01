#include <iostream>
#include <algorithm>
using namespace std;

char chess[50][50];
char sample_chess[8][8];

int plus_chess(int start_x, int start_y) {

    int num = 0;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (chess[i + start_x][j + start_y] == sample_chess[i][j])
                num++;

    return min(num, 64 - num);
}
int main()
{
    int M, N;
    cin >> M >> N;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            cin >> chess[i][j];
        }

    int now_min = 32;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if ((i + j) % 2 == 0)
                sample_chess[i][j] = 'W';
            else
                sample_chess[i][j] = 'B';

    for (int i = 0; i <= M - 8; i++)
        for (int j = 0; j <= N - 8; j++) {
            int num = plus_chess(i, j);
            now_min = min(now_min, num);
        }

    cout << now_min << endl;
}