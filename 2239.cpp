#include <iostream>

using namespace std;

int sudoku[9][9];
bool garo[9][10];		// 가로 row
bool sero[9][10];		// 세로 col
bool area[9][10];		// 3 가로 X 3 세로

void input()
{
	for (int i = 0; i < 9; i++) { // h
		for (int j = 0; j < 9; j++) { // w
			cin >> sudoku[i][j];
			if (!sudoku[i][j])
				continue;
			garo[i][sudoku[i][j]] = true;
			sero[j][sudoku[i][j]] = true;
			area[i/3 * 3 + j / 3][sudoku[i][j]] = true;
		}
	}
}

void solve(int num)
{
	if (num == 81) {
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++) {
				cout << sudoku[i][j] << " ";
			}
			cout << endl;
		}
		exit(0);
	}
	int x = num % 9;
	int y = num / 9;

	if (sudoku[y][x]) // != 0
		solve(num + 1);
	else {
		for (int i = 1; i <= 9; i++) {
			if (!sero[x][i] && !garo[y][i] && !area[y / 3 * 3 + x/3][i])
			{
				sudoku[y][x] = i;
				sero[x][i] = true;
				garo[y][i] = true;
				area[y / 3 * 3 + x/3][i] = true;
				solve(num + 1);
				sudoku[y][x] = 0;
				sero[x][i] = false;
				garo[y][i] = false;
				area[y / 3 * 3 + x/3][i] = false;
			}
		}
	}
}
int main()
{
	input();
	solve(0);
}