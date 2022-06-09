#include <iostream>

using namespace std;

int main()
{
	// LCS

	string str1, str2;
	cin >> str1;
	cin >> str2;
	
	int length_str1 = str1.length();
	int length_str2 = str2.length();

	int** DP = new int* [length_str1 + 1];
	for (int i = 0; i < length_str1 + 1; ++i)
		DP[i] = new int[length_str2 + 1];

	for (int i = 0; i <= length_str1; ++i)
		DP[i][0] = 0;

	for (int i = 0; i < length_str2; ++i)
		DP[0][i] = 0;

	for (int i=1;i<= length_str1;++i)
		for (int j = 1; j <= length_str2; ++j) {
			if (str1[i-1] == str2[j-1])
				DP[i][j] = DP[i - 1][j - 1] + 1;
			else
				DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
		}

	cout << DP[length_str1][length_str2]<< endl;
}