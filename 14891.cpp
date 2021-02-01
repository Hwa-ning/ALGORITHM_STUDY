#include <iostream>
#include <cmath>
#include <deque>

using namespace std;

deque<int>s[4];

void spin(int n_th, int dir){
	if(dir==1){
		int temp = s[n_th].back();
		s[n_th].pop_back();
		s[n_th].push_front(temp);
	}
	else{
		int temp = s[n_th].front();
		s[n_th].pop_front();
		s[n_th].push_back(temp);
	}
}
void check_left(int n_th, int dir) {
	if (0 <= n_th && n_th <= 3)
		if (s[n_th][2] != s[n_th+1][6]) {
			check_left(n_th - 1, -dir);
			spin(n_th, dir);
		}
	return;
}
void check_right(int n_th, int dir) {
	if (0 <= n_th && n_th <= 3)
		if (s[n_th][6] != s[n_th - 1][2]) {
			check_right(n_th + 1, -dir);
			spin(n_th, dir);
		}
	return;
}
int main()
{
	string input;
	for (int i = 0; i < 4; i++) {
		cin >> input;
		for (int j = 0; j < 8; j++)
			s[i].push_back(input.at(j) - '0');
	}
	int k, to, dir;
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> to >> dir;
		to--;
		check_left(to - 1, -dir);
		check_right(to + 1, -dir);
		spin(to, dir); // 그 톱니바퀴는 무조건 돌아간다.
	}

	int res = 0;
	for (int i = 0; i < 4; i++) {
		if (s[i][0] == 1)
			res += pow(2, i);
	}
	cout << res << endl;
}