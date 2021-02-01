#include <iostream>

using namespace std;

int n, k;
int DP[10001];

int main() {

    cin >> n >> k;

    int coins[100];

    for (int i = 0; i < n; i++)
        cin >> coins[i];

    DP[0] = 1;
    for (int i = 0; i < n; i++)
        for (int j = coins[i]; j <= k; j++)
            if (j <= coins[i])
                DP[j] += DP[j - coins[i]];

    cout << DP[k] << endl;

    return 0;
}