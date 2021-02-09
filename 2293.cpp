#include <iostream>

using namespace std;

int n, k;
int DP[10001];

int main() {

    cin >> n >> k;

    int arr[100];

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    DP[0] = 1;

    for (int i = 0; i < n; i++)
        for (int j = arr[i]; j <= k; j++)
            if (j - arr[i] >= 0)
                DP[j] += DP[j - arr[i]];

    cout << DP[k] << endl;
    return 0;
}