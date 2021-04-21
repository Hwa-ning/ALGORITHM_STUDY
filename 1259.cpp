#include <iostream>
#include <string>
using namespace std;
int main()
{
	string input;
	cin >> input;
	int alphabet[26] = { 0 };   // input의 출현 빈도를 저장 해당 문자가 몇번 나왔는지 저장
								// A라면 0번째 B라면 1번째...
	
	for(int i=0;i<input.size();i++)		// input.size()만큼 봐서 input 전부를
		input[i] = toupper(input[i]);	// 모든 문자들을 대문자로

	for (int i = 0; i < input.size(); i++)
		alphabet[(input[i] - 'A')]++;	// << input[i]-'A'해서 A면 0번째 B면 1번째에 들어가도록 해서 ++해서 횟수 count

	int max = 0;		// max
	int max_idx = -1;	// max 가 나온 index를 저장

	for (int i = 0; i < 26; i++)
		if (alphabet[i] > max) {
			max = alphabet[i];
			max_idx = i;
		}

	for (int i = 0; i < 26; i++) {
		if (alphabet[i] == max && i != max_idx) {
			cout << "?" << endl;
			return 0;
		}
	}
	cout << (char)(max_idx + 'A') << endl;
}