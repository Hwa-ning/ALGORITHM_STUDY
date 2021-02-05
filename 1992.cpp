#include <iostream>

#define MAX 64

using namespace std;

int N;
int arr[MAX][MAX];
void dq(int x, int y, int length)
{
	if (length == 1) {
		cout << arr[x][y];
		return;
	}

	int start = arr[x][y];
	bool is_same = true;
	for (int i = x; i < x+length; i++)
		for (int j = y; j < y+length; j++)
		{
			if (arr[i][j] != start)
			{
				cout << "(";
				is_same = false;
				int temp = length / 2;
				dq(x, y, temp);
				dq(x, y + temp, temp);
				dq(x + temp, y, temp);
				dq(x + temp, y + temp, temp);
				cout << ")";
				return;
			}
		}
	if (is_same)
		cout << start;
}
int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	cin >> N;
	string input;
	for (int i = 0; i < N; i++) {
		cin >> input;
		for (int j = 0; j < input.length(); j++)
			arr[i][j] = input[j] - '0';
	}
	dq(0, 0, N);
	cout << "\n";
	return 0;
}