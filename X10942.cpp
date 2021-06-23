#include <iostream>
#include <algorithm>

using namespace std;

bool ans[2001][2001];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string s_input, s="";
	int N, M, S, E;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> s_input;
		s.append(s_input);
	}
	for (int i = 0; i < N; i++)
		ans[i][i] = true;
	
	for (int i = 0; i < N; i++)
		if (s_input[i] == s_input[i + 1])
			ans[i][i + 1] = true;

	for(int i=0;i<N;i++)
		for(int j=2;j<N-2;j++)
			if(ans[i][j])
				
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> S >> E;
		if (ans[S][E])
			cout << 1 << "\n";
		else
			cout << 0 << "\n";
	}
}